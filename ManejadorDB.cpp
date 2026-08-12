// ==========================================
// Nombre: [Jesus Hernan Cortez Rodríguez]
// Fecha: [03/08/2026]
// Proyecto: Bóveda Digital
// ==========================================

#include "ManejadorDB.h"
#include "Registro.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


ManejadorDB::ManejadorDB()= default;
ManejadorDB::ManejadorDB(std::string _nombreArchivo, std::string _rutaArchivo) : nombreArchivo(_nombreArchivo), rutaArchivo(_rutaArchivo) {}

void ManejadorDB::insertarRegistro(Registro &nuevo) {
    int siguienteId = 1;
    if (!registros.empty()) {
        siguienteId = registros.back().id + 1;
    }
    nuevo.id = siguienteId;
    registros.push_back(nuevo);
}

void ManejadorDB::listarRegistros() const {
    for (const Registro& r : registros) {
        std::cout << r << std::endl;
    }
}
void ManejadorDB::listarDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo o el archivo no existe.\n";
        return;
    }

    std::string linea;
    std::cout << "--- LISTA DE REGISTROS ---\n";

    // Leemos el archivo línea por línea
    while (std::getline(archivo, linea)) {
        // Ignorar líneas vacías si las hay
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string id, sitio, usuario, password, fRegistro, fCaducidad, comentario;

        // Separamos cada campo usando el delimitador ';'
        std::getline(ss, id, ';');
        std::getline(ss, sitio, ';');
        std::getline(ss, usuario, ';');
        std::getline(ss, password, ';');
        std::getline(ss, fRegistro, ';');
        std::getline(ss, fCaducidad, ';');
        std::getline(ss, comentario, '\n'); // El último campo termina en salto de línea

        // Imprimimos los datos en un formato legible
        std::cout << "ID: " << id
                  << " | Sitio: " << sitio
                  << " | Usuario: " << usuario
                  << " | Pass: " << password
                  << " | Creado: " << fRegistro
                  << " | Expira: " << fCaducidad
                  << " | Comentario: " << comentario << "\n";
        std::cout << "-------------------------------------------\n";
    }

    archivo.close();
}

const Registro* ManejadorDB::buscarPorSitio(const std::string& sitio) const {
    for (const Registro& r : registros) {
        if (r.getSitioPassword() == sitio) {
            return &r; // Retorna la dirección del registro encontrado
        }
    }
    return nullptr; // No se encontró
}

bool ManejadorDB::eliminarRegistro(int id) {
    auto it = std::remove_if(registros.begin(), registros.end(), [id](const Registro& r) {
        return r.id == id;
    });

    if (it != registros.end()) {
        registros.erase(it, registros.end());
        return true; // Registro eliminado con éxito
    }
    return false; // El ID no existía
}

bool ManejadorDB::guardarEnArchivo(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo, std::ios::app);
    if (!archivo.is_open()) return false;
    for (const Registro& r : registros) {
        archivo << r.id << ";"
                << r.sitioPassword << ";"
                << r.userPassword << ";"
                << r.password << ";"
                << r.fechas.fechaRegistro << ";"
                << r.fechas.fechaCaducidad << ";"
                << r.comentario << "\n";
    }
    archivo.close();
    return true;
}

bool ManejadorDB::cargarDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) return false;

    registros.clear(); // Limpiamos los registros actuales para no duplicar
    std::string linea;

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string tempId, sitio, user, pass, fReg, fCad, coment;

        // Leemos cada campo separado por punto y coma
        std::getline(ss, tempId, ';');
        std::getline(ss, sitio, ';');
        std::getline(ss, user, ';');
        std::getline(ss, pass, ';');
        std::getline(ss, fReg, ';');
        std::getline(ss, fCad, ';');
        std::getline(ss, coment, ';'); // El último campo lee hasta el final del stringstream

        // Creamos el objeto Registro temporal
        Registro r;
        r.id = std::stoi(tempId); // Convertimos el ID de texto a entero
        r.sitioPassword = sitio;
        r.userPassword = user;
        r.password = pass;
        r.fechas.fechaRegistro = fReg;
        r.fechas.fechaCaducidad = fCad;
        r.comentario = coment;

        // Lo insertamos en nuestro vector
        registros.push_back(r);
    }

    archivo.close();
    return true;
}

