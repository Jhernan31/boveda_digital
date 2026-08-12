// ==========================================
// Nombre: [Jesus Hernan Cortez Rodriguez]
// Fecha: [03/08/2026]
// Proyecto: Bóveda Digital
// ==========================================
#include "ManejadorDB.h"
#include "Registro.h"
#include <iostream>
#include <iomanip>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

void mostrarMenuPrincipal() {
    std::cout << "=== === === === === === === === === === === === === === === === === === === ===" << std::endl;
    std::cout << "                       [ ADMINISTRADOR DE CONTRASEÑAS ]                        " << std::endl;
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
    std::cout << "                                MENU PRINCIPAL                                 " << std::endl;
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
    std::cout << "-                               1) ➕ INSERTAR                                -" << std::endl;
    std::cout << "-                               2) 🔍 BUSCAR                                  -" << std::endl;
    std::cout << "-                               3) 📋 LISTAR                                  -" << std::endl;
    std::cout << "-                               4) ✏️ EDITAR                                  -" << std::endl;
    std::cout << "-                               5) 🗑️ BORRAR                                  -" << std::endl;
    std::cout << "-                               6) 🚪 SALIR                                   -" << std::endl;
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    std::string opcion;
    bool continuar = true;
    int seleccion;
    std::string countChars;

    ManejadorDB db;
    std::string archivoDatos = "contrasenas.txt";

    while (continuar) {
        mostrarMenuPrincipal();
        while (true) {
            std::cout << "OPCION : "; std::getline(std::cin, opcion);
            bool esNumeroValido = true;
            if (opcion.empty()) {
                esNumeroValido = false;
            } else {
                for (char &c : opcion) {
                    if (!isdigit(c)) {
                        esNumeroValido = false;
                        break;
                    }
                }
            }
            if (esNumeroValido) {
                seleccion = std::stoi(opcion);
                if (seleccion >= 1 && seleccion <= 6) {
                    break;
                }
            }
            std::cout << "\n[ERROR]: Debe ingresar una opcion valida.\n" << std::endl;
        }
        //std::cin.ignore();
        switch (seleccion) {
            case 1: {
                Registro nuevo;
                std::string tempTexto, tempReg, tempCad;

                std::cout << "\n === === === === === === REGISTRO NUEVO === === === === === ===\n";
                std::cout << "Sitio Web (ej. google.com): ";
                std::getline(std::cin, tempTexto);
                nuevo.setSitioPassword(tempTexto);

                std::cout << "Usuario / Correo: ";
                std::getline(std::cin, tempTexto);
                nuevo.setUserPassword(tempTexto);

                std::cout << "Contrasena: ";
                std::getline(std::cin, tempTexto);
                nuevo.setPassword(tempTexto);

                std::cout << "Fecha de Registro (DD/MM/AAAA): ";
                std::getline(std::cin, tempReg);

                std::cout << "Fecha de Caducidad (DD/MM/AAAA): ";
                std::getline(std::cin, tempCad);

                nuevo.setFechas(tempReg, tempCad);

                std::cout << "Comentarios adicionales: ";
                std::getline(std::cin, tempTexto);
                nuevo.setComentario(tempTexto);

                db.insertarRegistro(nuevo); // Aquí adentro se le asignará el ID correlativo automáticamente
                std::cout << "[Exito] Registro agregado con ID automatico.\n";
                break;
            }
            case 2: {
                std::string sitio;
                std::cout << "\nIngrese el nombre del sitio a buscar: ";
                std::getline(std::cin, sitio);

                const Registro* encontrado = db.buscarPorSitio(sitio);
                if (encontrado != nullptr) {
                    std::cout << "\n[Resultado] Registro encontrado:\n";
                    std::cout << *encontrado << std::endl; // Usa tu operador << corregido
                } else {
                    std::cout << "[Aviso] No se encontro ningun registro para: " << sitio << "\n";
                }
                break;
            }
            case 3: {
                db.listarDesdeArchivo(archivoDatos);
                break;
            }
            case 4: {
                if (db.guardarEnArchivo(archivoDatos)) {
                    std::cout << "[Exito] Datos guardados correctamente en " << archivoDatos << "\n";
                } else {
                    std::cout << "[Error] No se pudo escribir en el archivo.\n";
                }
                break;
            }
            case 5: {
                if (db.cargarDesdeArchivo(archivoDatos)) {
                    std::cout << "[Exito] Datos recargados desde " << archivoDatos << "\n";
                } else {
                    std::cout << "[Error] No se pudo abrir el archivo para lectura.\n";
                }
                break;
            }
            case 6: {
                // Guardar automáticamente al salir para evitar pérdida de datos
                db.guardarEnArchivo(archivoDatos);
                std::cout << "\n[Info] Datos guardados automáticamente. ¡Hasta luego!\n";
                continuar = false;
                break;
            }
        }
    }
    return 0;
}