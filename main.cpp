#include <iostream>
#include <string>
#include <vector>

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

#include "gestor.h"

using namespace std;

int main() {
    using namespace ftxui;

    auto pantalla = ScreenInteractive::Fullscreen();

    // --- 1. ESTADO DE LA APLICACIÓN ---
    GestorRecordatorios gestor("recordatorios.txt");
    auto lista_tareas = gestor.getListaFormateada();
    int seleccionado = 0;
    string nuevo_recordatorio = "";

    auto actualizar_lista = [&]() {
        lista_tareas = gestor.getListaFormateada();
    };

    // --- 2. COMPONENTES INTERACTIVOS ---
    auto menu_tareas = Menu(&lista_tareas, &seleccionado);

    auto menu_con_teclas = CatchEvent(menu_tareas, [&](Event event) {
        if ((event == Event::Character(' ') || event == Event::Return) &&
            !lista_tareas.empty()) {
            gestor.conmutar(seleccionado);
            actualizar_lista();
            return true;
        }
        return false;
    });

    Component input_tarea =
        Input(&nuevo_recordatorio, "Escribe un nuevo recordatorio...");

    auto boton_agregar = Button("Agregar", [&]() {
        if (!nuevo_recordatorio.empty()) {
            gestor.agregar(nuevo_recordatorio);
            actualizar_lista();
            nuevo_recordatorio = "";
        }
    });

    // --- 3. CONTENEDOR Y LAYOUT ---
    auto contenedor_derecho = Container::Vertical({input_tarea, boton_agregar});

    auto contenedor_principal =
        Container::Horizontal({menu_con_teclas, contenedor_derecho});

    // atajos globales: Shift+S/q salir, Shift+G agregar
    contenedor_principal = CatchEvent(contenedor_principal, [&](Event event) {
        if (event == Event::Character('R') && !lista_tareas.empty()) {
            gestor.eliminar(seleccionado);
            actualizar_lista();
            if (seleccionado >= (int)lista_tareas.size())
                seleccionado = max(0, (int)lista_tareas.size() - 1);
            return true;
        }
        if (event == Event::Character('G')) {
            boton_agregar->OnEvent(Event::Return);
            return true;
        }
        if (event == Event::Character('S') || event == Event::Character('q')) {
            pantalla.Exit();
            return true;
        }
        return false;
    });

    // --- 4. RENDERIZADO ---
    auto renderer = Renderer(contenedor_principal, [&]() {
        return vbox({
            hbox(window(text(" RECORDATORIOS PENDIENTES "),
                        menu_tareas->Render() | vscroll_indicator | frame) |
                     flex,

                 window(text(" ACCIONES "),
                        vbox({
                            text("Añadir Nueva:"),
                            input_tarea->Render() | border | color(Color::Blue),
                            vbox({boton_agregar->Render() | center}) |
                                size(HEIGHT, EQUAL, 3),
                        })) |
                     size(WIDTH, EQUAL, 40)) |
                flex,
            separator(),
            text(" [Space] Pausa  [Enter] Completar  [Shift+R] Remover  [Shift+G] Agregar  [Shift+S/Q] Salir ") |
                dim | center,
        });
    });

    // --- 5. EJECUCIÓN ---
    pantalla.Loop(renderer);

    return 0;
}
