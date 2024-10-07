#include "digitalclock.h" // Incluye el encabezado de la clase DigitalClock
#include "ui_digitalclock.h" // Incluye el encabezado de la interfaz de usuario generada por Qt
#include <QPainter> // Incluye la clase QPainter para realizar gráficos
#include <QTime> // Incluye la clase QTime para trabajar con el tiempo
#include <QMessageBox> // Incluye la clase QMessageBox para mostrar diálogos de mensajes
#include <QUrl> // Incluye la clase QUrl para manejar URLs
#include <QDebug> // Incluye la clase QDebug para imprimir mensajes de depuración
#include <QSoundEffect> // Incluye la clase QSoundEffect para reproducir sonidos
#include <QVBoxLayout> // Incluye la clase QVBoxLayout para gestionar el diseño vertical de widgets
#include <QLabel> // Incluye la clase QLabel para mostrar texto
#include <QScreen> // Incluye la clase QScreen para obtener información sobre la pantalla

// Constructor de la clase DigitalClock
DigitalClock::DigitalClock(QWidget *parent) :
    QMainWindow(parent), // Inicializa la clase base QMainWindow
    ui(new Ui::DigitalClock), // Crea un nuevo objeto de la interfaz de usuario
    soundEffect(new QSoundEffect(this)), // Inicializa el efecto de sonido para la alarma
    alarmActive(false) // Inicializa el estado de la alarma como inactiva
{
    ui->setupUi(this); // Configura la interfaz de usuario

    setupConnections(); // Llama a la función para establecer las conexiones de señal y slot

    timer = new QTimer(this); // Crea un nuevo temporizador
    connect(timer, &QTimer::timeout, this, &DigitalClock::updateTime); // Conecta la señal de timeout del temporizador al slot updateTime
    timer->start(1000); // Inicia el temporizador con un intervalo de 1000 ms (1 segundo)

    // Configurar el sonido de la alarma
    soundEffect->setSource(QUrl("qrc:/sounds/alarm.wav")); // Establece la fuente del sonido de la alarma
    soundEffect->setVolume(1.0f); // Establece el volumen del sonido a máximo
    soundEffect->setLoopCount(QSoundEffect::Infinite); // Establece el sonido para que se reproduzca en bucle indefinido

    // Centrar la ventana en la pantalla
    centerWindow(); // Llama a la función para centrar la ventana
}

// Destructor de la clase DigitalClock
DigitalClock::~DigitalClock()
{
    delete ui; // Libera la memoria utilizada por la interfaz de usuario
}

// Función para centrar la ventana en la pantalla
void DigitalClock::centerWindow()
{
    // Obtener la geometría de la pantalla principal
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry(); // Obtiene las dimensiones de la pantalla
    int x = (screenGeometry.width() - width()) / 2; // Calcula la posición X para centrar
    int y = ((screenGeometry.height() - height()) / 2) - 34; // Calcula la posición Y para centrar, ajustando 34 pixels

    // Mover la ventana al centro
    move(x, y); // Mueve la ventana a las coordenadas (x, y)
}

// Función para establecer conexiones entre señales y slots
void DigitalClock::setupConnections()
{
    connect(ui->setAlarmButton, &QPushButton::clicked, this, &DigitalClock::setAlarm); // Conecta el botón de establecer alarma
    connect(ui->stopAlarmButton, &QPushButton::clicked, this, &DigitalClock::stopAlarm); // Conecta el botón de detener alarma
}

// Función para actualizar la hora cada segundo
void DigitalClock::updateTime()
{
    currentTime = QTime::currentTime(); // Obtiene la hora actual
    QString timeString = currentTime.toString("hh:mm:ss"); // Formatea la hora como cadena
    ui->digitalDisplay->display(timeString); // Muestra la hora en el display digital

    updateAnalogClock(); // Actualiza el reloj analógico
    checkAlarm(); // Verifica si la alarma debe activarse
}

// Función para actualizar el reloj analógico
void DigitalClock::updateAnalogClock()
{
    QPixmap pixmap(300, 300); // Crea un pixmap de 300x300 pixels
    pixmap.fill(Qt::transparent); // Rellena el pixmap con color transparente
    QPainter painter(&pixmap); // Crea un objeto QPainter para dibujar en el pixmap
    painter.setRenderHint(QPainter::Antialiasing); // Habilita la suavización de bordes

    // Dibuja la cara del reloj
    painter.setPen(Qt::NoPen); // No dibuja bordes
    painter.setBrush(QColor(255, 255, 255, 30)); // Establece el color del relleno
    painter.drawEllipse(5, 5, 290, 290); // Dibuja la cara del reloj como un círculo

    painter.translate(150, 150); // Traslada el origen al centro del reloj
    painter.setPen(Qt::white); // Establece el color del pen a blanco

    // Dibujar marcas de horas
    for (int i = 0; i < 12; ++i) {
        painter.drawLine(0, -140, 0, -130); // Dibuja las marcas de horas
        painter.rotate(30); // Rota 30 grados para la siguiente marca
    }

    // Dibujar agujas
    painter.setPen(Qt::NoPen); // No dibuja bordes para las agujas

    // Aguja de la hora
    painter.save(); // Guarda el estado del pintor
    painter.rotate(30.0 * ((currentTime.hour() + currentTime.minute() / 60.0))); // Rota según la hora
    painter.setBrush(Qt::white); // Establece el color de la aguja a blanco
    painter.drawRoundedRect(-4, -70, 8, 70, 4, 4); // Dibuja la aguja de la hora
    painter.restore(); // Restaura el estado del pintor

    // Aguja del minuto
    painter.save(); // Guarda el estado del pintor
    painter.rotate(6.0 * (currentTime.minute() + currentTime.second() / 60.0)); // Rota según el minuto
    painter.setBrush(Qt::white); // Establece el color de la aguja a blanco
    painter.drawRoundedRect(-3, -100, 6, 100, 3, 3); // Dibuja la aguja del minuto
    painter.restore(); // Restaura el estado del pintor

    // Aguja del segundo
    painter.save(); // Guarda el estado del pintor
    painter.rotate(6.0 * currentTime.second()); // Rota según el segundo
    painter.setBrush(QColor("#FFEB3B")); // Establece el color de la aguja a amarillo
    painter.drawRoundedRect(-1, -120, 2, 120, 1, 1); // Dibuja la aguja del segundo
    painter.restore(); // Restaura el estado del pintor

    // Punto central
    painter.setBrush(QColor("#FFEB3B")); // Establece el color del punto central a amarillo
    painter.drawEllipse(-6, -6, 12, 12); // Dibuja el punto central

    ui->analogClock->setPixmap(pixmap); // Establece el pixmap en el reloj analógico
}

// Función para establecer la alarma
void DigitalClock::setAlarm()
{
    alarmTime = ui->alarmTimeEdit->time(); // Obtiene la hora de alarma del editor de tiempo
    alarmActive = true; // Activa la alarma
    ui->setAlarmButton->setEnabled(false); // Deshabilita el botón de establecer alarma
    ui->stopAlarmButton->setEnabled(true); // Habilita el botón de detener alarma
    ui->alarmStatusLabel->setText("ALARMA PROGRAMADA PARA LAS " + alarmTime.toString("hh:mm")); // Muestra el estado de la alarma
}

// Función para verificar si la alarma debe sonar
void DigitalClock::checkAlarm()
{
    // Verifica si la alarma está activa y si la hora actual coincide con la hora de la alarma
    if (alarmActive && currentTime.toString("hh:mm") == alarmTime.toString("hh:mm")) {
        soundEffect->play(); // Reproduce el sonido de la alarma
        showAlarmMessage();  // Muestra el mensaje de alerta
    }
}

// Función para detener la alarma
void DigitalClock::stopAlarm()
{
    // Detener el sonido de la alarma y restablecer el estado de la alarma
    soundEffect->stop(); // Detiene el sonido de la alarma
    alarmActive = false; // Desactiva la alarma
    ui->setAlarmButton->setEnabled(true); // Habilita el botón de establecer alarma
    ui->stopAlarmButton->setEnabled(false); // Deshabilita el botón de detener alarma
    ui->alarmStatusLabel->setText("SIN ALARMA PROGRAMADA"); // Actualiza el estado de la alarma
}

void DigitalClock::showAlarmMessage()
{
    QMessageBox alarmMessageBox; // Crea un cuadro de mensaje para mostrar la alarma
    alarmMessageBox.setWindowTitle("ALARMAAA!"); // Establece el título de la ventana del mensaje

    // Usamos una sola llamada a `setText` para agregar el ícono y el texto principal.
    QString iconText = "<div style='text-align: center;'>"
                       "<h2 style='color:#ECE3A1;'>⏰</h2>" // Agrega un ícono de alarma en color amarillo claro
                       "<h2 style='color:#ECE3A1;'>Alarma Iniciada!</h2>" // Mensaje principal de alarma
                       "</div>";
    alarmMessageBox.setText(iconText); // Establece el texto del cuadro de mensaje, incluyendo el ícono

    // Añadimos el mensaje informativo adicional centrado.
    alarmMessageBox.setInformativeText("<div style='text-align: center; font-size:14px; color:#66FCF1;'>Es hora de levantarse!</div>");
    // Texto adicional con estilo, indicando que es hora de levantarse

    // Aplicamos el estilo general al QMessageBox, etiquetas y botones
    alarmMessageBox.setStyleSheet("QMessageBox { background-color: #1E1E2E; border: 2px solid #66FCF1; } " // Estilo de fondo y borde
                                  "QLabel { color: #ECE3A1; font-family: 'Roboto', sans-serif; text-align: center; } " // Estilo para etiquetas
                                  "QPushButton { background-color: #45A29E; color: #FFFFFF; padding: 10px 20px; border-radius: 15px; } " // Estilo para botones
                                  "QPushButton:hover { background-color: #66FCF1; color: #1E1E2E; }"); // Estilo para botones al pasar el mouse

    // Definimos el tamaño de la ventana del QMessageBox
    alarmMessageBox.setFixedSize(800, 300); // Establece el tamaño fijo del cuadro de mensaje

    // Añadimos el botón OK en la parte inferior (gestión interna de QMessageBox)
    alarmMessageBox.setStandardButtons(QMessageBox::Ok); // Establece el botón estándar a "Ok"
    alarmMessageBox.setDefaultButton(QMessageBox::Ok); // Establece el botón "Ok" como el botón predeterminado

    // Mostrar el mensaje y gestionar la respuesta
    int ret = alarmMessageBox.exec(); // Muestra el cuadro de mensaje y espera a que el usuario responda
    if (ret == QMessageBox::Ok) { // Si el usuario presiona "Ok"
        stopAlarm();  // Detener la alarma cuando se presiona OK
    }
}


