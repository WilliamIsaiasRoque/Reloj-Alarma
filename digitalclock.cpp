#include "digitalclock.h" // Incluir el encabezado de la clase DigitalClock
#include "ui_digitalclock.h" // Incluir la interfaz de usuario generada para DigitalClock
#include <QPainter> // Incluir la clase QPainter para dibujar
#include <QTime> // Incluir la clase QTime para manejar el tiempo
#include <QMessageBox> // Incluir la clase QMessageBox para mostrar cuadros de mensaje
#include <QUrl> // Incluir la clase QUrl para manejar URLs
#include <QDebug> // Incluir QDebug para imprimir mensajes de depuración
#include <QSoundEffect> // Incluir la clase QSoundEffect para reproducir sonidos
#include <QVBoxLayout> // Incluir la clase QVBoxLayout para manejar layouts verticales
#include <QLabel> // Incluir la clase QLabel para mostrar texto
#include <QScreen> // Incluir la clase QScreen para manejar la pantalla
#include <QResizeEvent> // Incluir la clase QResizeEvent para manejar eventos de redimensionamiento

DigitalClock::DigitalClock(QWidget *parent) : // Constructor de la clase DigitalClock
    QMainWindow(parent), // Inicializa la clase base QMainWindow
    ui(new Ui::DigitalClock), // Crea una nueva instancia de la interfaz de usuario
    soundEffect(new QSoundEffect(this)), // Crea un nuevo efecto de sonido
    alarmActive(false), // Inicializa el estado de la alarma como inactiva
    elapsedTime(0), // Inicializa el tiempo transcurrido en 0
    stopwatchRunning(false), // Inicializa el estado del cronómetro como detenido
    isAlarmMode(true) // Inicializa el modo como alarma
{
    ui->setupUi(this); // Configura la interfaz de usuario

    setupConnections(); // Llama a la función para establecer conexiones de señales y slots

    timer = new QTimer(this); // Crea un nuevo temporizador
    connect(timer, &QTimer::timeout, this, &DigitalClock::updateTime); // Conecta la señal de tiempo agotado a la función updateTime
    timer->start(1000); // Inicia el temporizador con un intervalo de 1000 ms (1 segundo)

    stopwatchTimer = new QTimer(this); // Crea un nuevo temporizador para el cronómetro
    connect(stopwatchTimer, &QTimer::timeout, this, &DigitalClock::updateStopwatch); // Conecta la señal de tiempo agotado a la función updateStopwatch

    soundEffect->setSource(QUrl("qrc:/sounds/alarm.wav")); // Establece la fuente del sonido de la alarma
    soundEffect->setVolume(1.0f); // Establece el volumen del efecto de sonido al máximo
    soundEffect->setLoopCount(QSoundEffect::Infinite); // Establece el efecto de sonido para que se repita infinitamente

    // Configura el widget central y el layout
    QWidget *centralWidget = new QWidget(this); // Crea un nuevo widget central
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget); // Crea un nuevo layout vertical para el widget central
    mainLayout->addWidget(ui->titleLabel); // Agrega el título al layout
    mainLayout->addWidget(ui->digitalDisplay); // Agrega la pantalla digital al layout

    // Crea un layout horizontal para centrar el reloj analógico
    QHBoxLayout *clockLayout = new QHBoxLayout(); // Crea un nuevo layout horizontal
    clockLayout->addStretch(); // Agrega un espacio flexible a la izquierda
    clockLayout->addWidget(ui->analogClock); // Agrega el reloj analógico al layout
    clockLayout->addStretch(); // Agrega un espacio flexible a la derecha
    mainLayout->addLayout(clockLayout); // Agrega el layout del reloj analógico al layout principal

    mainLayout->addWidget(ui->toggleFunctionButton); // Agrega el botón para alternar funcionalidades al layout
    mainLayout->addWidget(ui->functionalityStack); // Agrega el stack de funcionalidades al layout

    // Ajusta los factores de estiramiento
    mainLayout->setStretchFactor(ui->titleLabel, 0); // No permite que el título se estire
    mainLayout->setStretchFactor(ui->digitalDisplay, 1); // Permite que la pantalla digital se estire
    mainLayout->setStretchFactor(clockLayout, 2); // Permite que el layout del reloj analógico se estire más
    mainLayout->setStretchFactor(ui->toggleFunctionButton, 0); // No permite que el botón se estire
    mainLayout->setStretchFactor(ui->functionalityStack, 1); // Permite que el stack de funcionalidades se estire

    setCentralWidget(centralWidget); // Establece el widget central en la ventana principal

    // Inicializa con el modo de alarma
    ui->functionalityStack->setCurrentIndex(0); // Muestra el primer índice del stack de funcionalidades (modo alarma)

    // Establece el tamaño mínimo para la ventana
    setFixedSize(500, 800); // Fija el tamaño de la ventana a 500x800 píxeles

    // Centra la ventana en la pantalla
    centerWindow(); // Llama a la función para centrar la ventana
}

DigitalClock::~DigitalClock() // Destructor de la clase DigitalClock
{
    delete ui; // Libera la memoria del objeto de la interfaz de usuario
}

void DigitalClock::centerWindow() // Función para centrar la ventana en la pantalla
{
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry(); // Obtiene la geometría de la pantalla principal
    int x = (screenGeometry.width() - width()) / 2; // Calcula la posición x para centrar
    int y = ((screenGeometry.height() - height()) / 2) - 30; // Calcula la posición y para centrar (con un ajuste)
    move(x, y); // Mueve la ventana a la posición calculada
}

void DigitalClock::setupConnections() // Función para establecer las conexiones de señales y slots
{
    connect(ui->setAlarmButton, &QPushButton::clicked, this, &DigitalClock::setAlarm); // Conecta el botón de establecer alarma a la función setAlarm
    connect(ui->stopAlarmButton, &QPushButton::clicked, this, &DigitalClock::stopAlarm); // Conecta el botón de detener alarma a la función stopAlarm
    connect(ui->startStopwatchButton, &QPushButton::clicked, this, &DigitalClock::startStopwatch); // Conecta el botón de iniciar cronómetro a la función startStopwatch
    connect(ui->stopStopwatchButton, &QPushButton::clicked, this, &DigitalClock::stopStopwatch); // Conecta el botón de detener cronómetro a la función stopStopwatch
    connect(ui->resetStopwatchButton, &QPushButton::clicked, this, &DigitalClock::resetStopwatch); // Conecta el botón de reiniciar cronómetro a la función resetStopwatch
    connect(ui->toggleFunctionButton, &QPushButton::clicked, this, &DigitalClock::toggleFunctionality); // Conecta el botón de alternar funcionalidades a la función toggleFunctionality
}

void DigitalClock::updateTime() // Función para actualizar el tiempo
{
    currentTime = QTime::currentTime(); // Obtiene la hora actual
    QString timeString = currentTime.toString("hh:mm:ss"); // Convierte la hora actual a formato de cadena "hh:mm:ss"
    ui->digitalDisplay->display(timeString); // Muestra la hora en la pantalla digital

    updateAnalogClock(); // Llama a la función para actualizar el reloj analógico
    checkAlarm(); // Llama a la función para verificar si la alarma debe sonar
}
void DigitalClock::updateAnalogClock() // Método para actualizar el reloj analógico
{
    int size = qMin(ui->analogClock->width(), ui->analogClock->height()); // Determina el tamaño del reloj como el menor de ancho y alto
    QPixmap pixmap(size, size); // Crea un QPixmap de tamaño 'size' x 'size'
    pixmap.fill(Qt::transparent); // Rellena el pixmap con transparencia
    QPainter painter(&pixmap); // Crea un objeto QPainter para dibujar en el pixmap
    painter.setRenderHint(QPainter::Antialiasing); // Activa el suavizado de bordes

    // Dibuja la cara del reloj
    painter.setPen(Qt::NoPen); // No dibuja contornos
    painter.setBrush(QColor(255, 255, 255, 30)); // Establece el color de relleno con transparencia
    painter.drawEllipse(5, 5, size - 10, size - 10); // Dibuja un círculo para la cara del reloj

    painter.translate(size / 2, size / 2); // Mueve el origen al centro del reloj
    painter.setPen(Qt::white); // Establece el color del lápiz en blanco para dibujar las marcas

    // Dibuja las marcas de horas
    for (int i = 0; i < 12; ++i) { // Itera para dibujar 12 marcas de horas
        painter.drawLine(0, -(size / 2 - 10), 0, -(size / 2 - 20)); // Dibuja la línea de la marca
        painter.rotate(30); // Rota el pincel 30 grados para la siguiente marca
    }

    painter.setPen(Qt::NoPen); // No dibuja contornos para las manecillas

    // Dibuja la manecilla de la hora
    painter.save(); // Guarda el estado del pintor
    painter.rotate(30.0 * ((currentTime.hour() + currentTime.minute() / 60.0))); // Rota según la hora
    painter.setBrush(Qt::white); // Establece el color de la manecilla en blanco
    painter.drawRoundedRect(-4, -(size / 3), 8, size / 3, 4, 4); // Dibuja la manecilla de la hora
    painter.restore(); // Restaura el estado del pintor

    // Dibuja la manecilla de los minutos
    painter.save(); // Guarda el estado del pintor
    painter.rotate(6.0 * (currentTime.minute() + currentTime.second() / 60.0)); // Rota según los minutos
    painter.setBrush(Qt::white); // Establece el color de la manecilla en blanco
    painter.drawRoundedRect(-3, -(size / 2.5), 6, size / 2.5, 3, 3); // Dibuja la manecilla de los minutos
    painter.restore(); // Restaura el estado del pintor

    // Dibuja la manecilla de los segundos
    painter.save(); // Guarda el estado del pintor
    painter.rotate(6.0 * currentTime.second()); // Rota según los segundos
    painter.setBrush(QColor("#FFEB3B")); // Establece el color de la manecilla en amarillo
    painter.drawRoundedRect(-1, -(size / 2.1), 2, size / 2.1, 1, 1); // Dibuja la manecilla de los segundos
    painter.restore(); // Restaura el estado del pintor

    // Dibuja el círculo central
    painter.setBrush(QColor("#FFEB3B")); // Establece el color en amarillo para el centro
    painter.drawEllipse(-6, -6, 12, 12); // Dibuja un pequeño círculo en el centro

    ui->analogClock->setPixmap(pixmap); // Establece el pixmap en el reloj analógico en la interfaz de usuario
}

void DigitalClock::setAlarm() // Método para establecer una alarma
{
    alarmTime = ui->alarmTimeEdit->time(); // Obtiene la hora de alarma del widget de edición
    alarmActive = true; // Activa la alarma
    ui->setAlarmButton->setEnabled(false); // Desactiva el botón de establecer alarma
    ui->stopAlarmButton->setEnabled(true); // Activa el botón para detener la alarma
    ui->alarmStatusLabel->setText("ALARMA PROGRAMADA PARA LAS " + alarmTime.toString("hh:mm")); // Muestra el estado de la alarma
}

void DigitalClock::checkAlarm() // Método para verificar si la alarma debe sonar
{
    if (alarmActive && currentTime.toString("hh:mm") == alarmTime.toString("hh:mm")) { // Verifica si la alarma está activa y es la hora
        soundEffect->play(); // Reproduce el sonido de la alarma
        showAlarmMessage(); // Muestra el mensaje de alarma
    }
}

void DigitalClock::stopAlarm() // Método para detener la alarma
{
    soundEffect->stop(); // Detiene el sonido de la alarma
    alarmActive = false; // Desactiva la alarma
    ui->setAlarmButton->setEnabled(true); // Activa el botón de establecer alarma
    ui->stopAlarmButton->setEnabled(false); // Desactiva el botón para detener la alarma
    ui->alarmStatusLabel->setText("SIN ALARMA PROGRAMADA"); // Actualiza el estado de la alarma
}

void DigitalClock::showAlarmMessage() // Método para mostrar un mensaje cuando la alarma suena
{
    QMessageBox alarmMessageBox; // Crea un cuadro de mensaje
    alarmMessageBox.setWindowTitle("ALARMAAA!"); // Establece el título del cuadro de mensaje

    // Crea un texto HTML para mostrar un ícono y un mensaje
    QString iconText = "<div style='text-align: center;'>"
                       "<h2 style='color:#ECE3A1;'>⏰</h2>"
                       "<h2 style='color:#ECE3A1;'>Alarma Iniciada!</h2>"
                       "</div>";
    alarmMessageBox.setText(iconText); // Establece el texto del cuadro de mensaje

    alarmMessageBox.setInformativeText("<div style='text-align: center; font-size:14px; color:#66FCF1;'>Es hora de levantarse!</div>"); // Establece el texto informativo

    // Establece el estilo del cuadro de mensaje
    alarmMessageBox.setStyleSheet("QMessageBox { background-color: #1E1E2E; border: 2px solid #66FCF1; } "
                                  "QLabel { color: #ECE3A1; font-family: 'Roboto', sans-serif; text-align: center; } "
                                  "QPushButton { background-color: #45A29E; color: #FFFFFF; padding: 10px 20px; border-radius: 15px; } "
                                  "QPushButton:hover { background-color: #66FCF1; color: #1E1E2E; }");

    alarmMessageBox.setFixedSize(800, 300); // Establece el tamaño del cuadro de mensaje

    alarmMessageBox.setStandardButtons(QMessageBox::Ok); // Establece los botones estándar
    alarmMessageBox.setDefaultButton(QMessageBox::Ok); // Establece el botón predeterminado

    int ret = alarmMessageBox.exec(); // Ejecuta el cuadro de mensaje y espera la interacción del usuario
    if (ret == QMessageBox::Ok) { // Si el usuario presiona OK
        stopAlarm(); // Detiene la alarma
    }
}

void DigitalClock::startStopwatch() // Método para iniciar o pausar el cronómetro
{
    if (!stopwatchRunning) { // Si el cronómetro no está corriendo
        elapsedTimer.start(); // Inicia el temporizador
        stopwatchTimer->start(10); // Inicia el temporizador del cronómetro con un intervalo de 10 ms
        stopwatchRunning = true; // Marca que el cronómetro está corriendo
        ui->startStopwatchButton->setText("Pausar"); // Cambia el texto del botón a "Pausar"
    } else { // Si el cronómetro está corriendo
        stopwatchTimer->stop(); // Detiene el temporizador del cronómetro
        elapsedTime += elapsedTimer.elapsed(); // Agrega el tiempo transcurrido al tiempo total
        stopwatchRunning = false; // Marca que el cronómetro no está corriendo
        ui->startStopwatchButton->setText("Reanudar"); // Cambia el texto del botón a "Reanudar"
    }
}

void DigitalClock::stopStopwatch() // Definición de la función para detener el cronómetro
{
    if (stopwatchRunning) { // Verifica si el cronómetro está en funcionamiento
        stopwatchTimer->stop(); // Detiene el temporizador del cronómetro
        elapsedTime += elapsedTimer.elapsed(); // Suma el tiempo transcurrido al tiempo total
        stopwatchRunning = false; // Cambia el estado del cronómetro a no en funcionamiento
        ui->startStopwatchButton->setText("Iniciar"); // Cambia el texto del botón a "Iniciar"
    }
}

void DigitalClock::resetStopwatch() // Definición de la función para reiniciar el cronómetro
{
    stopwatchTimer->stop(); // Detiene el temporizador del cronómetro
    elapsedTime = 0; // Reinicia el tiempo total a 0
    stopwatchRunning = false; // Cambia el estado del cronómetro a no en funcionamiento
    ui->startStopwatchButton->setText("Start"); // Cambia el texto del botón a "Start"
    updateStopwatch(); // Actualiza la visualización del cronómetro
}

void DigitalClock::updateStopwatch() // Definición de la función para actualizar la visualización del cronómetro
{
    qint64 totalElapsed = elapsedTime; // Almacena el tiempo total acumulado
    if (stopwatchRunning) { // Verifica si el cronómetro está en funcionamiento
        totalElapsed += elapsedTimer.elapsed(); // Agrega el tiempo transcurrido al tiempo total
    }

    int hours = totalElapsed / 3600000; // Calcula las horas a partir del tiempo total en milisegundos
    int minutes = (totalElapsed % 3600000) / 60000; // Calcula los minutos restantes
    int seconds = (totalElapsed % 60000) / 1000; // Calcula los segundos restantes
    int milliseconds = totalElapsed % 1000; // Obtiene los milisegundos restantes

    // Formatea el tiempo como una cadena en el formato HH:MM:SS.mmm
    QString timeString = QString("%1:%2:%3.%4")
                             .arg(hours, 2, 10, QChar('0')) // Formatea las horas con 2 dígitos
                             .arg(minutes, 2, 10, QChar('0')) // Formatea los minutos con 2 dígitos
                             .arg(seconds, 2, 10, QChar('0')) // Formatea los segundos con 2 dígitos
                             .arg(milliseconds, 3, 10, QChar('0')); // Formatea los milisegundos con 3 dígitos

    ui->stopwatchDisplay->setText(timeString); // Establece el texto del cronómetro en la interfaz de usuario
}

void DigitalClock::resizeEvent(QResizeEvent *event) // Definición de la función para manejar eventos de redimensionamiento
{
    QMainWindow::resizeEvent(event); // Llama al evento de redimensionamiento de la clase base
    updateAnalogClock(); // Actualiza el reloj analógico después de redimensionar
}

void DigitalClock::toggleFunctionality() // Definición de la función para alternar entre los modos de alarma y cronómetro
{
    isAlarmMode = !isAlarmMode; // Cambia el estado del modo de alarma
    if (isAlarmMode) { // Si está en modo de alarma
        ui->functionalityStack->setCurrentIndex(0); // Cambia a la interfaz de usuario del modo de alarma
        ui->toggleFunctionButton->setText("Cambiar a Cronómetro"); // Cambia el texto del botón
    } else { // Si está en modo de cronómetro
        ui->functionalityStack->setCurrentIndex(1); // Cambia a la interfaz de usuario del modo de cronómetro
        ui->toggleFunctionButton->setText("Cambiar a Alarma"); // Cambia el texto del botón
    }
}
