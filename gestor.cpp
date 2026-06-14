#include "gestor.h"
#include <fstream>
#include <sstream>

using namespace std;

GestorRecordatorios::GestorRecordatorios(const string &archivo)
    : rutaArchivo(archivo) {
    cargarDesdeArchivo();
}

void GestorRecordatorios::agregar(const string &texto) {
    recordatorios.push_back(
        Recordatorio(generarId(), texto, false));
    guardarEnArchivo();
}

void GestorRecordatorios::conmutar(int indice) {
    if (indice >= 0 && indice < (int)recordatorios.size()) {
        recordatorios[indice].conmutarEstado();
        guardarEnArchivo();
    }
}

void GestorRecordatorios::eliminar(int indice) {
    if (indice >= 0 && indice < (int)recordatorios.size()) {
        recordatorios.erase(recordatorios.begin() + indice);
        guardarEnArchivo();
    }
}

const vector<Recordatorio> &GestorRecordatorios::getRecordatorios() const {
    return recordatorios;
}

vector<string> GestorRecordatorios::getListaFormateada() const {
    vector<string> lista;
    for (const auto &r : recordatorios) {
        string estado = r.isCompletado() ? "[x]" : "[ ]";
        lista.push_back(estado + " " + r.getTexto());
    }
    return lista;
}

void GestorRecordatorios::cargarDesdeArchivo() {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            recordatorios.push_back(Recordatorio::deserializar(linea));
        }
    }
}

void GestorRecordatorios::guardarEnArchivo() {
    ofstream archivo(rutaArchivo);
    for (const auto &r : recordatorios) {
        archivo << r.serializar() << "\n";
    }
}

string GestorRecordatorios::generarId() const {
    static int contador = 0;
    return "R" + to_string(contador++);
}
