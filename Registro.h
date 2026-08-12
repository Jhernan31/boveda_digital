// ==========================================
// Nombre: [Jesus Hernan Cortez Rodriguez]
// Fecha: [03/08/2026]
// Proyecto: Bóveda Digital
// ==========================================

#ifndef BOVEDADIGITAL_REGISTRO_H
#define BOVEDADIGITAL_REGISTRO_H
#include <ostream>
#include <string>

// Estructura auxiliar requerida por la rúbrica
struct Vigencia {
    std::string fechaRegistro;
    std::string fechaCaducidad;
};

class Registro {

private:
    int id;
    std::string sitioPassword;
    std::string userPassword;
    std::string password;
    std::string comentario;
    Vigencia fechas;

public:
    Registro()= default;
    //Constructor parametrizado
    //Registro(int id, std::string sitioPassword, std::string userPassword, std::string password, std::string comentario, Vigencia fechas);
    friend class ManejadorDB;
    //int getId() const;
    //std::string getSitioPassword() const;
    std::string getUserPassword();
    std::string getPassword();
    std::string getComentario();
    Vigencia getFecha();
    void setSitioPassword(const std::string& sitioPassword);
    void setUserPassword(const std::string& userPassword);
    void setPassword(const std::string& password);
    void setComentario(const std::string& comentario);
    void setFechas(const std::string& fecReg, const std::string& fecCad);
    [[nodiscard]]std::string getSitioPassword() const {
        return sitioPassword;
    };


    friend std::ostream& operator<<(std::ostream& os, const Registro& r) {
        os << "ID: " << r.id
           << " | Sitio: " << r.sitioPassword
           << " | Usuario: " << r.userPassword
           << " | Password: " << r.password
           << " | Fecha Registro: " << r.fechas.fechaRegistro
           << " | Fecha Caducidad: " << r.fechas.fechaCaducidad
           << " | Comentarios: " << r.comentario;
        return os;
    }
    /*
    friend std::ostream& operator<<(std::ostream& os, const Vigencia& f) {
        os << f.fechaRegistro << " (Caduca: " << f.fechaCaducidad << ")";
        return os;

    }
     */


};


#endif //BOVEDADIGITAL_REGISTRO_H
