QT += core gui multimedia                  # Añade los módulos 'core', 'gui' y 'multimedia' al proyecto Qt.
QT += multimedia                           # Añade el módulo 'multimedia' al proyecto Qt (esto puede parecer redundante).

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets # Si la versión mayor de Qt es mayor que 4, añade el módulo 'widgets'.

CONFIG += c++17                           # Configura el proyecto para usar la versión C++17 del compilador.

SOURCES += \                               # Inicia la lista de archivos fuente del proyecto.
    main.cpp \                            # Añade el archivo 'main.cpp' a la lista de fuentes.
    digitalclock.cpp                      # Añade el archivo 'digitalclock.cpp' a la lista de fuentes.

HEADERS += \                               # Inicia la lista de archivos de encabezado del proyecto.
    digitalclock.h                        # Añade el archivo 'digitalclock.h' a la lista de encabezados.

FORMS += \                                 # Inicia la lista de archivos de formulario del proyecto.
    digitalclock.ui                       # Añade el archivo de interfaz de usuario 'digitalclock.ui'.

TRANSLATIONS += \                          # Inicia la lista de archivos de traducción del proyecto.
    DigitalClock_es_PE.ts                 # Añade el archivo de traducción 'DigitalClock_es_PE.ts'.

CONFIG += lrelease                        # Añade la configuración para usar el comando 'lrelease', que genera archivos de traducción.
CONFIG += embed_translations               # Añade la configuración para incrustar las traducciones en el ejecutable.

# Reglas por defecto para el despliegue.     # Comentario que indica que las siguientes líneas son reglas por defecto para el despliegue.
qnx: target.path = /tmp/$${TARGET}/bin      # Establece la ruta de destino para la plataforma QNX.
else: unix:!android: target.path = /opt/$${TARGET}/bin # Para plataformas UNIX (excluyendo Android), establece la ruta de destino en '/opt/'.
!isEmpty(target.path): INSTALLS += target   # Si 'target.path' no está vacío, añade 'target' a la lista de instalaciones.

RESOURCES += \                             # Inicia la lista de recursos del proyecto.
    resources.qrc                          # Añade el archivo de recursos 'resources.qrc' a la lista de recursos
