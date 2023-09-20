#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdint.h>
#include <stdio.h>

uint8_t off = 0;

#define sensor_1_threshold 15
#define sensor_2_threshold 97

#define water_add_rate 2
#define water_vaporation_rate .2
#define water_pump_rate 3

#define temp_increase_rate 1
#define temp_decrease_rate .1
#define max_temp 60

double ambient_temp = 25;

extern uint8_t pin_s11;
extern uint8_t pin_s12;
extern uint8_t pin_v1;

extern uint8_t pin_s21;
extern uint8_t pin_s22;
extern uint8_t pin_p1;

extern uint8_t pin_s31;
extern uint8_t pin_s32;
extern uint8_t pin_v2;

MainWindow::Tank tank1 = {
    0,
    water_add_rate,
    100,
    ambient_temp,
    &pin_p1,
    &pin_s11,
    &pin_s12,
    &pin_v1
};

MainWindow::Tank tank2 = {
    0,
    water_pump_rate,
    100,
    ambient_temp,
    &pin_v2,
    &pin_s21,
    &pin_s22,
    &pin_p1
};

MainWindow::Tank tank3 = {
    0,
    water_add_rate,
    25,
    ambient_temp,
    &off,
    &pin_s31,
    &pin_s32,
    &pin_v2
};

MainWindow::Boiler boiler1 = {
    temp_decrease_rate,
    temp_increase_rate,
    &tank3
};

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

    connect(ui->pushButton_valve,
            SIGNAL(pressed()),
            this,
            SLOT(valve_click()));

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

void MainWindow::update_ui() {
    ui->s11->setPower(pin_s11);
    ui->s12->setPower(pin_s12);
    ui->s21->setPower(pin_s21);
    ui->s22->setPower(pin_s22);
    ui->s31->setPower(pin_s31);
    ui->s32->setPower(pin_s32);
    ui->valvula1->setPower(pin_v1);
    ui->pump1->setPower(pin_p1);
    ui->pump2->setPower(pin_v2);
    ui->toolButton_tank1->setValue(get_percentage(tank1.value, tank1.volume));
    ui->toolButton_tank2->setValue(get_percentage(tank2.value, tank2.volume));
    ui->toolButton_tank3->setValue(get_percentage(tank3.value, tank3.volume));

    ui->label_waterTemp->setText(QString::number(tank3.temperature).append(" C°"));

    ui->label_tank1_status->setText(QString::number(tank1.value));
    ui->label_tank2_status->setText(QString::number(tank2.value));
    ui->label_tank3_status->setText(QString::number(tank3.value));

}

void MainWindow::update_tank(Tank *tank) {
    if(*tank->receiving){
        tank->value += .1 * tank->water_in_rate;
        if(tank->value > tank->volume)
            tank->value = tank->volume;
    }

    if(tank->value > 0){
        tank->value -= .1 * water_vaporation_rate;
    }

    if(*tank->pumped)
        tank->value -= .1 * water_pump_rate;

    double p = get_percentage(tank->value, tank->volume);
    *tank->sensor1 = p >= sensor_1_threshold;
    *tank->sensor2 = p >= sensor_2_threshold;
}

void MainWindow::update_irl_data() {
    update_tank(&tank1);
    update_tank(&tank2);
    update_tank(&tank3);
    update_boiler(&boiler1);
}

void MainWindow::update_boiler(Boiler *boiler) {

}

void MainWindow::valve_click() {
    //QApplication::exit(0);
    printf("bomdia");
    if(pin_v1)
        pin_v1 = 0;
    else
        pin_v1 = 1;
}

