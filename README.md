# reminderscli

Una aplicación de recordatorios interactiva para la terminal, construida con C++ y [FTXUI](https://github.com/ArthurSonzogni/FTXUI).

---

## Características

- Interfaz TUI (Text User Interface) a pantalla completa
- Añadir, completar y eliminar recordatorios desde el teclado
- Los recordatorios se persisten automáticamente en un archivo local (`recordatorios.txt`)
- Navegación completamente por teclado, sin ratón

---

## Controles

| Tecla | Acción |
|---|---|
| `↑` / `↓` | Navegar entre recordatorios |
| `Space` o `Enter` | Marcar/desmarcar como completado |
| `Shift+R` | Eliminar el recordatorio seleccionado |
| `Shift+G` | Agregar el recordatorio escrito |
| `Shift+S` o `Q` | Salir de la aplicación |

---

## Requisitos

- **CMake** ≥ 3.11
- **g++** o **clang++** con soporte para C++17
- **git**
- Conexión a internet (para descargar FTXUI automáticamente en el primer build)

---

## Instalación rápida

Puedes usar el script de instalación automática:

```bash
bash install_reminderscli.sh
```

Esto instala el binario en `/usr/local/bin/reminders_app`.

---

## Compilación manual

```bash
git clone https://github.com/AriSophDev/reminderscli.git
cmake -S reminderscli -B reminderscli/build -DCMAKE_BUILD_TYPE=Release
cmake --build reminderscli/build --parallel
```

El binario queda en `reminderscli/build/reminders_app`.

---

## Uso

```bash
reminders_app
```

Los recordatorios se guardan automáticamente en `recordatorios.txt` en el directorio desde donde ejecutes la app.

---

## Estructura del proyecto

```
reminderscli/
├── main.cpp           # Punto de entrada y UI (FTXUI)
├── gestor.cpp/.h      # Lógica de gestión de recordatorios
├── recordatorio.cpp/.h # Modelo de datos
└── CMakeLists.txt     # Build system (descarga FTXUI automáticamente)
```

---

## Licencia

MIT © [AriSophDev](https://github.com/AriSophDev)
