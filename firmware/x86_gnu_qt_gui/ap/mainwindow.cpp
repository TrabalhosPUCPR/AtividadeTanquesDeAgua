#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdint.h>
#include <stdio.h>

extern "C" {
    #include "../../common/defaults.h"
}

uint8_t off = 0;

#define sensor_1_threshold 15
#define sensor_2_threshold 97

#define water_add_rate 2
#define water_vaporation_rate 0.3
#define water_transfer_rate 3

#define temp_increase_rate 30
#define temp_decrease_rate 5

extern uint8_t pin_s11;
extern uint8_t pin_s12;
extern uint8_t pin_v1;

extern uint8_t pin_s21;
extern uint8_t pin_s22;
extern uint8_t pin_p1;

extern uint8_t pin_s31;
extern uint8_t pin_s32;
extern uint8_t pin_v2;
extern uint8_t pin_b1;
extern uint32_t pin_bs1;

MainWindow::Tank tank1 = {
    0,
    water_add_rate,
    100,
    0,
    &pin_p1,
    &pin_s11,
    &pin_s12,
    &pin_v1,
    &off,
    NULL
};
MainWindow::Tank tank2 = {
    0,
    water_transfer_rate,
    100,
    0,
    &off,
    &pin_s21,
    &pin_s22,
    &pin_p1,
    &pin_v2,
    NULL // null pq no c++ n tem como COLOCAR A VARIAVEL LA EM CIMA E INSTANCIA DPS, PQ???? ESSA ESTRUTURA FOI TUDO VISANDO ISSO
};
MainWindow::Tank tank3 = {
    0,
    water_transfer_rate,
    50,
    &pin_bs1,
    &off,
    &pin_s31,
    &pin_s32,
    &off,
    &pin_v2,
    NULL
};

MainWindow::Boiler boiler1 = {
    &pin_b1,
    &tank3
};

int t2_height;
int t3_height;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&timer_ui,
            SIGNAL(timeout()),
            this,
            SLOT(update_ui()));

    connect(&timer_irl,
            SIGNAL(timeout()),
            this,
            SLOT(update_irl_data()));

    connect(ui->pushButton_drainTank1,
            SIGNAL(released()),
            this,
            SLOT(drain_tank1()));

    connect(ui->pushButton_drainTank2,
            SIGNAL(released()),
            this,
            SLOT(drain_tank2()));

    connect(ui->pushButton_drainTank3,
            SIGNAL(released()),
            this,
            SLOT(drain_tank3()));

    tank2.bidirect_connected_tank = &tank3;
    tank3.bidirect_connected_tank = &tank2;

    t2_height = ui->toolButton_tank2->height();
    t3_height = ui->toolButton_tank3->height();

    pin_bs1 = ambientTemp();

    timer_ui.start(40);
    timer_irl.start(10);

    behavior_thread.start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

double get_percentage(double value, double max_value) {
    if(max_value == 100) return value; // nao faz o calculo caso nao for necessario
    return (value*100)/max_value; // TODO mudar maneira de calcular o double
}

double map(double value, double istart, double istop, double ostart, double ostop) {
    return ostart + (ostart - ostop) * ((value - istart) / (istop - istart));
}

void MainWindow::update_ui() {
    ui->s11->setPower(pin_s11);
    ui->s12->setPower(pin_s12);
    ui->s21->setPower(pin_s21);
    ui->s22->setPower(pin_s22);
    ui->s31->setPower(pin_s31);
    ui->s32->setPower(pin_s32);
    ui->bs1->setPower(pin_bs1);
    ui->valvula1->setPower(pin_v1);
    ui->pump1->setPower(pin_p1);
    ui->pump2->setPower(pin_v2);
    ui->b1->setPower(pin_b1);
    ui->toolButton_tank1->setValue(get_percentage(tank1.value, tank1.volume));
    ui->toolButton_tank2->setValue(get_percentage(tank2.value, tank2.volume));

    double t3_value = get_percentage(tank3.value, tank3.volume);

    ui->toolButton_tank3->setValue(t3_value);

    ui->label_waterTemp->setText(QString::number(fromFakeDecimal(*tank3.temperature)).append(" C°"));

    ui->label_tank1_status->setText(QString::number(tank1.value));
    ui->label_tank2_status->setText(QString::number(tank2.value));
    ui->label_tank3_status->setText(QString::number(tank3.value/2));

}

void MainWindow::update_tank(Tank *tank) {
    uint8_t bi = tank->pumped == tank->receiving;

    if(*tank->receiving && !bi){
        tank->value += .1 * tank->water_in_rate;
        if(tank->value > tank->volume)
            tank->value = tank->volume;
    }

    if(tank->bidirect_connected_tank != NULL && *tank->bidirect_valve){
        balance_tanks(tank, tank->bidirect_connected_tank);
    }

    vaporate_water(tank);

    if(*tank->pumped && !bi)
        tank->value -= .1 * water_transfer_rate;

    double p = get_percentage(tank->value, tank->volume);
    *tank->sensor1 = p >= sensor_1_threshold;
    *tank->sensor2 = p >= sensor_2_threshold;
}

void MainWindow::balance_tanks(Tank *tank1, Tank *tank2) {
    if(tank1->value < tank2->value && !*tank1->sensor2){
        tank1->value += .1 * water_transfer_rate;
        tank2->value -= .1 * water_transfer_rate;
    } else if(tank2->value < tank1->value && !*tank2->sensor2){
        tank1->value -= .1 * water_transfer_rate;
        tank2->value += .1 * water_transfer_rate;
    }
}

void MainWindow::update_irl_data() {
    update_tank(&tank1);
    update_tank(&tank2);
    update_tank(&tank3);
    update_boiler(&boiler1);
}

void MainWindow::update_boiler(Boiler *boiler) {
    if(*boiler->on) {
        *boiler->connected_tank->temperature += .1 * temp_increase_rate;
    } else {
        uint32_t to_remove = .1 * temp_increase_rate;
        if(*boiler->connected_tank->temperature - to_remove >= ambientTemp())
            *boiler->connected_tank->temperature -= to_remove;
    }
}

void MainWindow::vaporate_water(Tank* tank) {
    double to_remove = .1 * water_vaporation_rate;
    if(tank->value > to_remove)
        tank->value -= to_remove;
}

void MainWindow::drain_tank1(){
    tank1.value = 0;
}
void MainWindow::drain_tank2(){
    tank2.value = 0;
}
void MainWindow::drain_tank3(){
    tank3.value = 0;
}

