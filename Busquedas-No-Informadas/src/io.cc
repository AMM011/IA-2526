#include "io.h"
#include "busqueda.h"

#include <iostream>
#include <stdexcept>
#include <vector>

namespace {
/**
 * @brief Lee el siguiente token (palabra) del flujo de entrada.
 * @param in Flujo de entrada.
 * @param token String donde se almacena el token leído.
 * @return true si se leyó un token, false si se llegó al final del flujo
 */
bool SiguienteToken(std::istream& in, std::string& token) {
  token.clear();  
  // Lee el siguiente token (palabra) del flujo
  if(!(in >> token)) return false;    // Usamos el operador >> que ya trocea por espacios
  return true;
}

/**
 * @brief Convierte un string a double, aceptando tanto '.' como ',' como separador decimal.
 * @param s String a convertir.
 * @return Valor double representado por el string.
 * @throws std::invalid_argument Si el string no es un número válido.
 * @throws std::out_of_range Si el número está fuera del rango representable por un double.
 */
double ParseFlexibleDouble(std::string s) {
  for (char& c : s) if (c == ',') c = '.';
  // std::stod sirve para convertir string a double
  return std::stod(s);
}
}   // namespace

io::Problema io::LeerFichero(std::istream& in) {
  
} 