// ==========================================
// Nombre: [Jesus Hernan Cortez Rodriguez]
// Fecha: [03/08/2026]
// Proyecto: Bóveda Digital
// ==========================================

#ifndef BOVEDADIGITAL_MANEJADORDB_H
#define BOVEDADIGITAL_MANEJADORDB_H
#include <vector>
#include <string>
#include "Registro.h"


class ManejadorDB {
private:
    std::string nombreArchivo;
    std::string rutaArchivo;
    std::vector<Registro> registros;

    public:
    ManejadorDB();
    ManejadorDB(std::string nombreArchivo, std::string rutaArchivo);
    void insertarRegistro(Registro& nuevo);
    [[nodiscard]]const Registro* buscarPorSitio(const std::string& sitio) const;
    //void buscarRegistro(std::string nombreSitio, std::string fechaIni, std::string fechaFin) const;
    void listarRegistros() const;
    void listarDesdeArchivo(const std::string& nombreArchivo);
    //void editarRegistro(int idRegistro);
    //void borrarRegistro(int idRegistro);
    bool eliminarRegistro(int id);
    bool guardarEnArchivo(const std::string& nombreArchivo) const;
    bool cargarDesdeArchivo(const std::string& nombreArchivo);
    friend std::ostream& operator<<(std::ostream& os, const ManejadorDB& registro);

};


#endif //BOVEDADIGITAL_MANEJADORDB_H
