#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "behaviorthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer timer_ui;
    QTimer timer_irl;
    BehaviorThread behavior_thread;

    struct Tank;

    struct Tank {
        double value;
        double water_in_rate;
        double volume;
        uint32_t *temperature;
        uint8_t *pumped;
        uint8_t *sensor1;
        uint8_t *sensor2;
        uint8_t *receiving;
        uint8_t *bidirect_valve;
        Tank* bidirect_connected_tank;
    };

    typedef struct {
        uint8_t *on;
        Tank *connected_tank;
    } Boiler;

private:
    Ui::MainWindow *ui;
    void update_tank(Tank *tank);
    void update_boiler(Boiler *boiler);
    void balance_tanks(Tank *tank1, Tank *tank2);
    void add_to_tank(Tank *tank, double value);

public slots:
    void update_ui();
    void update_irl_data();
    void vaporate_water(Tank* tank);
    void drain_tank1();
    void drain_tank2();
    void drain_tank3();
};
#endif // MAINWINDOW_H
