#include <QApplication> // Aquí se importa la clase QApplication, que gestiona la aplicación Qt
#include "digitalclock.h" // Aquí se importa el encabezado de la clase DigitalClock, que define el reloj digital

int main(int argc, char *argv[]) // Aquí comienza la función principal de la aplicación
{
    QApplication a(argc, argv); // Aquí se crea una instancia de QApplication, pasando argumentos de línea de comandos
    DigitalClock w; // Aquí se crea un objeto de la clase DigitalClock, que representa la ventana principal del reloj
    w.show(); // Aquí se muestra la ventana del reloj digital en pantalla
    return a.exec(); // Aquí se inicia el bucle de eventos de la aplicación, gestionando eventos hasta que se cierra la aplicación
}
