# Informe del Proyecto: Reloj Digital con Alarma

## Introducción

Este informe presenta el desarrollo de un **Reloj Digital con Alarma** utilizando el framework **Qt** y el lenguaje de programación **C++**. El objetivo de este proyecto es proporcionar una interfaz intuitiva y funcional que permita a los usuarios visualizar la hora actual y configurar alarmas personalizadas.

## Objetivos del Proyecto

- **Desarrollar un reloj digital que muestre la hora actual.**
- **Implementar una alarma con sonido que se activa a una hora específica.**
- **Proporcionar una interfaz de usuario amigable y atractiva.**

## Tecnologías Utilizadas

- **Qt Framework**: Para el desarrollo de la interfaz gráfica y gestión de eventos.
- **C++**: Lenguaje de programación utilizado para la lógica del reloj y la alarma.
- **QSoundEffect**: Para reproducir el sonido de la alarma.

## Estructura del Proyecto

El proyecto está organizado en varios archivos esenciales:

### Archivos Fuente

- `main.cpp`: Punto de entrada de la aplicación.
- `digitalclock.cpp`: Contiene la lógica del reloj digital y la gestión de alarmas.

### Archivos de Encabezado

- `digitalclock.h`: Define la clase `DigitalClock`, que hereda de `QMainWindow`.

### Archivos de Interfaz de Usuario

- `digitalclock.ui`: Archivo de diseño de la interfaz gráfica creado con Qt Designer.

### Recursos

- `resources.qrc`: Contiene recursos como sonidos utilizados en la aplicación.
- `DigitalClock_es_PE.ts`: Archivo de traducción para la localización al español.

## Características Principales

### Reloj Digital

- Muestra la hora actual en formato **hh:mm:ss**.
- Actualización automática cada segundo.

### Alarma

- **Configuración de la alarma**: Permite al usuario establecer una hora específica para la alarma.
- **Activación de la alarma**: Cuando la hora actual coincide con la hora de la alarma, se reproduce un sonido.
- **Detención de la alarma**: Se puede detener manualmente el sonido de la alarma.

### Interfaz de Usuario

- Interfaz intuitiva con botones para configurar y detener la alarma.
- Visualización del estado de la alarma y la hora actual en un reloj analógico.

## Diseño de la Interfaz

La interfaz se diseñó para ser atractiva y funcional. Utiliza un diseño limpio con elementos bien organizados que facilitan la interacción del usuario.

![Interfaz del Reloj Digital](resources/digitalclock_ui.png)

## Código Fuente

A continuación, se presentan extractos del código fuente más relevante para la funcionalidad del reloj y la alarma.

### Código del Constructor

```cpp
DigitalClock::DigitalClock(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DigitalClock),
    soundEffect(new QSoundEffect(this)),
    alarmActive(false)
{
    ui->setupUi(this);
    setupConnections();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DigitalClock::updateTime);
    timer->start(1000);
    
    soundEffect->setSource(QUrl("qrc:/sounds/alarm.wav"));
    soundEffect->setVolume(1.0f);
    soundEffect->setLoopCount(QSoundEffect::Infinite);
    
    centerWindow();
}
