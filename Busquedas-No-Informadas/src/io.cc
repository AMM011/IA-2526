#include "io.h"
#include "busqueda.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <iomanip>

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

/**
 * @brief Convierte un vector de enteros a string en formato [a, b, c].
 * @param vec Vector de enteros.
 * @return String representando el vector.
 */
std::string VecAString(const std::vector<int>& vec) {
  if (vec.empty()) return "-";
  std::string resultado = "[";
  for(size_t i = 0; i < vec.size(); ++i) {
    resultado += std::to_string(vec[i]);
    if (i + 1 < vec.size()) resultado += ", ";
  }
  resultado += "]";
  return resultado;
}
}   // namespace

io::DatosLectura io::LeerFichero(const std::string& ruta) {
  std::ifstream fichero(ruta);
  if (!fichero.is_open()) {
    throw std::runtime_error("No se pudo abrir el fichero: " + ruta);
  }
  return LeerFichero(fichero);
} 

io::DatosLectura io::LeerFichero(std::istream& in) {
  std::string token;

  // Leemos el número de vértices
  if (!SiguienteToken(in, token)) {
    throw std::runtime_error("Error leyendo número de vértices");
  }
  // Convertimos a int el número de vértices
  int num_vertices = static_cast<int>(ParseFlexibleDouble(token));
  if (num_vertices < 1) throw std::runtime_error("Número de vértices debe ser >= 1");

  Grafo grafo(num_vertices);

  // Creamos una variable que determina cuantas aristas esperamos leer
  int esperados = num_vertices * (num_vertices - 1) / 2; // Máximo número de aristas en grafo no dirigido sin bucles
  int leidos = 0;

  // Leemos las aristas
  // Funciona asi:
  // i = 1             | i = 2             | i = 3             | ... | i = N-1
  // j = 2, 3, ..., N. | j = 3, 4, ..., N. | j = 4, 5, ..., N. | ... | j = N
  // Entonces, para cada i, j comienza en i+1 y termina en N
  for (int i = 1; i <= num_vertices - 1; ++i) {
    for (int j = i + 1; j <= num_vertices; ++j) {
      if (!SiguienteToken(in, token)) {
        throw std::runtime_error("Error leyendo peso para (" + std::to_string(i) +
                                 "," + std::to_string(j) + ")");
      }
      double peso = ParseFlexibleDouble(token);

      if (peso < -1.0) throw std::runtime_error("Peso inválido (< -1) en (" + std::to_string(i) + "," + std::to_string(j) + ")");
      if (peso >= 0.0) grafo.AnadirAristaNoDirigida(i, j, peso);

      leidos++;
    }
  }


  // Si no hemos leido el número esperado de pesos, lanzamos error
  if (leidos != esperados) {
    throw std::runtime_error("Conteo de pesos incorrecto (leídos " + std::to_string(leidos) +
                             ", esperados " + std::to_string(esperados) + ")");
  }

  // Construimos el Problema: el resto (origen, destino, etc.) los fijarás fuera
  io::DatosLectura problema{std::move(grafo)};

  return problema;
}


void io::ImprimirTraza(std::ostream& out, const trace::ResultadoBusqueda& r, bool acumulada) {
  size_t acc_inspected = 0, acc_generated = 0;

  out << "Traza (" << r.traza.size() << " iteraciones)\n";
  out << "-----------------------------------------\n";
  for (const auto& it : r.traza) {
    out << "Iteración " << it.paso << "\n";
    out << "  Nodos generados     (Δ): " << VecAString(it.generados_delta) << "\n";
    out << "  Nodos inspeccionados (Δ): " << VecAString(it.inspeccionados_delta) << "\n";
    
    if (acumulada) {
      acc_inspected += it.inspeccionados_delta.size();
      acc_generated += it.generados_delta.size();
      out << "  Inspeccionados (acum): " << acc_inspected << "\n";
      out << "  Generados     (acum): " << acc_generated << "\n";
    }
    out << "\n";
  }
}

void io::ImprimirSolucion(std::ostream& out, const trace::ResultadoBusqueda& r) {
  if (!r.found) {
    out << "No se encontró solución.\n";
    return;
  }

  // Si se encontró solución, imprimimos el camino
  out << "Camino: "; 
  for (size_t i = 0; i < r.camino.size(); ++i) {
    // Si es distinto del primero, imprimimos la flecha
    if (i) out << " -> ";
    out << r.camino[i];
  }
  out << "\n";

  // Imprimimos el coste total
  // .setf e unsetf sirven para formatear la salida
  // std::ios::fixed fuerza a que siempre haya dos decimales
  out.setf(std::ios::fixed);
  out << "Coste total: ";
  out << std::setprecision(2) << r.coste_total << "\n";
  out.unsetf(std::ios::fixed);
}

void io::ImprimirResumen(std::ostream& out, const trace::ResultadoBusqueda& r) {
  out << "Resumen\n";
  out << "-------\n";
  out << "Iteraciones:        " << r.traza.size() << "\n";
  out << "Nodos inspeccionados: " << r.nodos_inspeccionados << "\n";
  out << "Nodos generados:      " << r.nodos_generados << "\n";
}
