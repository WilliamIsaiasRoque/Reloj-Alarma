#ifndef DIGITALCLOCK_H // Evita múltiples inclusiones del encabezado
#define DIGITALCLOCK_H

#include <QMainWindow> // Permite crear ventanas en aplicaciones Qt
#include <QTimer> // Para realizar acciones a intervalos de tiempo
#include <QTime> // Para trabajar con tiempos
#include <QSoundEffect> // Para reproducir sonidos en la aplicación

namespace Ui {
class DigitalClock; // Clase de interfaz de usuario para el reloj digital
}

class DigitalClock : public QMainWindow // Clase DigitalClock que hereda de QMainWindow
{
    Q_OBJECT // Habilita señales y ranuras

public:
    explicit DigitalClock(QWidget *parent = nullptr); // Constructor que inicializa la ventana
    ~DigitalClock(); // Destructor que libera recursos

private slots:
    void updateTime(); // Actualiza la hora mostrada en el reloj
    void setAlarm(); // Establece la hora de la alarma
    void checkAlarm(); // Verifica si la alarma debe sonar
    void stopAlarm(); // Detiene la alarma

private:
    void setupConnections(); // Establece conexiones entre señales y ranuras
    void showAlarmMessage(); // Muestra un mensaje cuando la alarma suena
    void updateAnalogClock(); // Actualiza la representación del reloj analógico

    Ui::DigitalClock *ui; // Puntero a la clase de interfaz de usuario
    QTimer *timer; // Puntero a QTimer para actualizar el tiempo
    QTime currentTime; // Almacena la hora actual
    QTime alarmTime; // Almacena la hora de la alarma
    QSoundEffect *soundEffect; // Puntero a QSoundEffect para el sonido de la alarma
    bool alarmActive; // Indica si la alarma está activa

private:
    void centerWindow(); // Centra la ventana en la pantalla
};

#endif // DIGITALCLOCK_H // Fin de la guardia de inclusión
