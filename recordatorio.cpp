#include "recordatorio.h"
#include <sstream>

using namespace std;

Recordatorio::Recordatorio(const string &id, const string &texto,
                           bool completado)
    : id(id), texto(texto), completado(completado) {}

string Recordatorio::getID() const { return id; }
string Recordatorio::getTexto() const { return texto; }
bool Recordatorio::isCompletado() const { return completado; }

void Recordatorio::marcarComoCompletado() { completado = true; }

void Recordatorio::conmutarEstado() { completado = !completado; }

string Recordatorio::serializar() const {
    return id + ";" + texto + ";" + (completado ? "1" : "0");
}

Recordatorio Recordatorio::deserializar(const std::string &linea) {
    stringstream ss(linea);
    string id, texto, comp_str;

    getline(ss, id, ';');
    getline(ss, texto, ';');
    getline(ss, comp_str, ';');

    bool completado = (comp_str == "1");
    return Recordatorio(id, texto, completado);
}
