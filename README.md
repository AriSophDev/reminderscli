Reminderscli

Una aplicación de recordatorios interactiva para la terminal, construida con C++ y FTXUI.


Características


Interfaz TUI (Text User Interface) a pantalla completa
Añadir, completar y eliminar recordatorios desde el teclado
Los recordatorios se persisten automáticamente en un archivo local (recordatorios.txt)
Navegación completamente por teclado, sin ratón



Controles

TeclaAcción↑ / ↓Navegar entre recordatoriosSpace o EnterMarcar/desmarcar como completadoShift+REliminar el recordatorio seleccionadoShift+GAgregar el recordatorio escritoShift+S o QSalir de la aplicación


Requisitos


CMake ≥ 3.11
g++ o clang++ con soporte para C++17
git
Conexión a internet (para descargar FTXUI automáticamente en el primer build)



Instalación rápida

Puedes usar el script de instalación automática:

bashbash install_reminderscli.sh

Esto instala el binario en /usr/local/bin/reminders_app.


Compilación manual

bashgit clone https://github.com/AriSophDev/reminderscli.git
cmake -S reminderscli -B reminderscli/build -DCMAKE_BUILD_TYPE=Release
cmake --build reminderscli/build --parallel

El binario queda en reminderscli/build/reminders_app.


Uso

bashreminders_app

Los recordatorios se guardan automáticamente en recordatorios.txt en el directorio desde donde ejecutes la app.


Estructura del proyecto

reminderscli/
├── main.cpp           # Punto de entrada y UI (FTXUI)
├── gestor.cpp/.h      # Lógica de gestión de recordatorios
├── recordatorio.cpp/.h # Modelo de datos
└── CMakeLists.txt     # Build system (descarga FTXUI automáticamente)


Licencia

MIT © AriSophDev
