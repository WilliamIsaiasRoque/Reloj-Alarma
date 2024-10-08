#ifndef DIGITALCLOCK_H  // Comprueba si DIGITALCLOCK_H no ha sido definido
#define DIGITALCLOCK_H  // Define DIGITALCLOCK_H

#include <QMainWindow>  // Incluye la clase QMainWindow
#include <QTimer>  // Incluye la clase QTimer
#include <QTime>  // Incluye la clase QTime
#include <QSoundEffect>  // Incluye la clase QSoundEffect
#include <QElapsedTimer>  // Incluye la clase QElapsedTimer
#include <QStackedWidget>  // Incluye la clase QStackedWidget

namespace Ui {  // Declaración del espacio de nombres Ui
class DigitalClock;  // Declaración de la clase DigitalClock
}

class DigitalClock : public QMainWindow  // La clase DigitalClock hereda de QMainWindow
{
    Q_OBJECT  // Macro que habilita el uso de señales y ranuras en Qt

public:
    explicit DigitalClock(QWidget *parent = nullptr);  // Constructor que toma un puntero QWidget como parámetro
    ~DigitalClock();  // Destructor

private slots:  // Sección para las ranuras (slots) de la clase
    void updateTime();  // Ranura para actualizar la hora
    void setAlarm();  // Ranura para establecer una alarma
    void checkAlarm();  // Ranura para comprobar la alarma
    void stopAlarm();  // Ranura para detener la alarma

    void startStopwatch();  // Ranura para iniciar el cronómetro
    void stopStopwatch();  // Ranura para detener el cronómetro
    void resetStopwatch();  // Ranura para reiniciar el cronómetro
    void updateStopwatch();  // Ranura para actualizar el cronómetro

    void toggleFunctionality();  // Ranura para alternar entre funcionalidades

private:
    void setupConnections();  // Método para configurar conexiones de señales y ranuras
    void showAlarmMessage();  // Método para mostrar un mensaje de alarma
    void updateAnalogClock();  // Método para actualizar el reloj analógico
    void centerWindow();  // Método para centrar la ventana

    Ui::DigitalClock *ui;  // Puntero a la interfaz de usuario
    QTimer *timer;  // Puntero a un objeto QTimer para el reloj
    QTime currentTime;  // Variable para almacenar la hora actual
    QTime alarmTime;  // Variable para almacenar la hora de la alarma
    QSoundEffect *soundEffect;  // Puntero a un objeto QSoundEffect para los sonidos de la alarma
    bool alarmActive;  // Bandera para verificar si la alarma está activa

    QTimer *stopwatchTimer;  // Puntero a un objeto QTimer para el cronómetro
    QElapsedTimer elapsedTimer;  // Objeto QElapsedTimer para medir el tiempo transcurrido
    qint64 elapsedTime;  // Variable para almacenar el tiempo transcurrido en el cronómetro
    bool stopwatchRunning;  // Bandera para verificar si el cronómetro está en funcionamiento

    bool isAlarmMode;  // Bandera para verificar si está en modo alarma
protected:
    void resizeEvent(QResizeEvent *event) override;  // Declarar la función resizeEvent para manejar el cambio de tamaño de la ventana

};

#endif // DIGITALCLOCK_H  // Fin de la declaración de inclusión para DIGITALCLOCK_H
