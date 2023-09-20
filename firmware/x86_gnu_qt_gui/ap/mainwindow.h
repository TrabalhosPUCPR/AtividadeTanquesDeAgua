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

    typedef struct {
        double value;
        double water_in_rate;
        double volume;
        double temperature;
        uint8_t *pumped;
        uint8_t *sensor1;
        uint8_t *sensor2;
        uint8_t *receiving;
    } Tank;

    typedef struct {
        double temp_decrease_rate;
        double temp_increase_rate;
        Tank *connected_tank;
    } Boiler;

private:
    Ui::MainWindow *ui;
    void update_tank(Tank *tank);
    void update_boiler(Boiler *boiler);

public slots:
    void update_ui();
    void update_irl_data();
    void valve_click();
};
#endif // MAINWINDOW_H
