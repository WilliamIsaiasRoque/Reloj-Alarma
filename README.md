
# Informe del Proyecto: Reloj Digital con Alarma y Cronómetro

---

## Integrantes del Proyecto
1. Chambi Velasquez, Rommel Abraham
2. Garcia Apaza, Alan Jorge
3. Ower Frank Lopez Arela
4. Roque Quispe, William Isaias

---

## Resumen
Este informe presenta el desarrollo de un reloj digital interactivo que incluye funcionalidades de alarma y cronómetro. Nuestro proyecto se realizó utilizando la biblioteca Qt para C++, ofreciendo una interfaz gráfica intuitiva y fácil de usar. Este reloj digital no solo muestra la hora actual, sino que también permite a los usuarios establecer alarmas y utilizar un cronómetro para diversas actividades.

---

## Tabla de Contenidos
1. [Introducción](#introducción)
2. [Objetivos del Proyecto](#objetivos-del-proyecto)
3. [Tecnologías Utilizadas](#tecnologías-utilizadas)
4. [Características del Proyecto](#características-del-proyecto)
5. [Arquitectura del Proyecto](#arquitectura-del-proyecto)
6. [Interfaz de Usuario](#interfaz-de-usuario)
7. [Conclusiones y Recomendaciones](#conclusiones-y-recomendaciones)

---

## Introducción
El proyecto del reloj digital surge de la necesidad de crear una herramienta que combine funcionalidad y diseño en la visualización de la hora, junto con la capacidad de programar alarmas y realizar cronometraje. Con el auge de la tecnología y el uso cotidiano de dispositivos inteligentes, la creación de una aplicación de este tipo es relevante y útil.

---

## Objetivos del Proyecto
- **Desarrollar una aplicación de reloj digital** que muestre la hora actual en un formato atractivo.
- **Implementar funcionalidades de alarma** que permitan a los usuarios establecer alertas personalizadas.
- **Incorporar un cronómetro** que facilite la medición de intervalos de tiempo.

---

## Tecnologías Utilizadas
- **Qt Framework**: Para el desarrollo de la interfaz gráfica y la lógica del programa.
- **C++**: Como lenguaje de programación principal.
- **QSoundEffect**: Para la implementación de efectos de sonido en las alarmas.
- **QTimer** y **QElapsedTimer**: Para la gestión del tiempo y el cronometraje.

---

## Características del Proyecto
- **Visualización Digital**: La hora se muestra en un formato digital claro y legible.
- **Alarmas Programables**: Los usuarios pueden establecer múltiples alarmas con sonidos personalizados.
- **Cronómetro Funcional**: Permite iniciar, detener y reiniciar un cronómetro con facilidad.
- **Interfaz Intuitiva**: Diseño amigable que facilita la navegación entre las diferentes funcionalidades.

---

## Arquitectura del Proyecto
El proyecto se organiza en varias clases, cada una de las cuales gestiona diferentes aspectos del reloj digital:

- **`DigitalClock`**: Clase principal que hereda de `QMainWindow`. Contiene la lógica del reloj, la gestión de alarmas y el cronómetro.
- **Interfaz de Usuario (`digitalclock.ui`)**: Archivo que define la disposición visual de la aplicación, incluyendo botones y displays.
- **Módulos de Recursos**: Archivos de sonido y otros recursos que complementan la funcionalidad del reloj.

```cpp
class DigitalClock : public QMainWindow {
    Q_OBJECT
public:
    explicit DigitalClock(QWidget *parent = nullptr);
    ~DigitalClock();
    // Métodos para gestión de alarma y cronómetro
private:
    void setupConnections();
    void updateTime();
    void checkAlarm();
};
```

---

## Interfaz de Usuario
La interfaz se ha diseñado para ser visualmente atractiva y fácil de navegar. Incluye:
- Un **display digital** que muestra la hora en tiempo real.
- **Botones** claramente etiquetados para establecer alarmas y controlar el cronómetro.
- Un **reloj analógico** que complementa la visualización digital.

### Ejemplo de Interfaz

<div style="display: flex; justify-content: space-between;">

<div style="width: 45%;">
    <h4>Funcionamiento de la Alarma</h4>
    <img src="/img/alarma.png" alt="Funcionamiento de la Alarma" style="width: 50%;">
</div>

<div style="width: 45%;">
    <h4>Funcionamiento del Cronómetro</h4>
    <img src="/img/cronometro.png" alt="Funcionamiento del Cronómetro" style="width: 50%;">
</div>

</div>

---

## Conclusiones y Recomendaciones
El desarrollo del reloj digital con alarma y cronómetro ha sido un éxito, logrando cumplir con los objetivos establecidos. La aplicación es funcional y ofrece una experiencia de usuario satisfactoria. Para futuras mejoras, se recomienda:
- **Agregar más funcionalidades** como temporizadores o cronómetros múltiples.
- **Mejorar la personalización** de las alarmas con opciones de sonido y vibración.
- **Optimizar el rendimiento** para dispositivos con menos recursos.

---

## Referencias
- Documentación oficial de [Qt](https://doc.qt.io/qt-5/qtwidgets-index.html)
- Tutoriales de C++ y Qt en [Qt Tutorials](https://www.qt.io/learn)
```
