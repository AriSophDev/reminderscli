#ifndef RECORDATORIO_H
#define RECORDATORIO_H

#include <string>

using namespace std;

class Recordatorio {
  private:
    string id;
    string texto;
    bool completado;

  public:
    Recordatorio(const string &id, const string &texto,
                 bool completado = false);

    // getters and getters

    string getID() const;
    string getTexto() const;
    bool isCompletado() const;
    void marcarComoCompletado();

    void conmutarEstado(); // Cambia entre completado y pendiente

    // serializacion

    string serializar() const;
    static Recordatorio deserializar(const string &linea);
};

#endif
