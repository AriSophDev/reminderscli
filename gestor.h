#ifndef GESTOR_H
#define GESTOR_H

#include "recordatorio.h"
#include <string>
#include <vector>

class GestorRecordatorios {
  private:
    std::vector<Recordatorio> recordatorios;
    std::string rutaArchivo;

    void cargarDesdeArchivo();
    void guardarEnArchivo();
    std::string generarId() const;

  public:
    GestorRecordatorios(const std::string &archivo);

    void agregar(const std::string &texto);
    void conmutar(int indice);
    void eliminar(int indice);

    const std::vector<Recordatorio> &getRecordatorios() const;
    std::vector<std::string> getListaFormateada() const;
};

#endif
