// ==========================================
// Nombre: [Jesus Hernan Cortez Rodriguez]
// Fecha: [03/08/2026]
// Proyecto: Bóveda Digital
// ==========================================

#include "Registro.h"


void Registro::setSitioPassword(const std::string& sitio) { sitioPassword = sitio; }
void Registro::setUserPassword(const std::string& user)   { userPassword = user; }
void Registro::setPassword(const std::string& pass)       { password = pass; }
void Registro::setComentario(const std::string& comento) { comentario = comento; }
void Registro::setFechas(const std::string& fecReg, const std::string& fecCad) { fechas.fechaRegistro = fecReg; fechas.fechaCaducidad = fecCad;}


