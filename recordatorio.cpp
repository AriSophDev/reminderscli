#ifndef GESTOR_H
#define GESTOR_H

#include "recordatorio.h"
#include <vector>

using namespace std;

class GestorRecordatorios {
  private:
    vector<Recordatorio> recordatorios;
    string archivoDatos;

    void cargarDesdearchivo();
    void guardarEnArchivo();

  public:
    GestorRecordatorios(const string &rutaArchivo);

    void agregarRecordatorio(const string &texto);
    void listarRecordatorios() const;
    void completarRecordatorio(const string &id);
    void eliminarRecordatorio(const string &id);
};

#endif
