#ifndef IO_H
#define IO_H

#include "grafo.h"
#include "trace.h"

#include <iosfwd>


namespace io {

  /**
   * @brief Algoritmo de búsqueda a utilizar.
   *         - kBfs: Búsqueda en amplitud (BFS).
   *         - kDfs: Búsqueda en profundidad (DFS).
   */
   enum class Algoritmo { kBfs, kDfs };

  /**
   * @brief Estructura problema que contiene los datos de lectura
   * - grafo: El grafo donde se realiza la búsqueda.
   * - origen: Nodo de origen (1-based).
   * - destino: Nodo destino (1-based).
   * - algoritmo: Algoritmo de búsqueda a utilizar (BFS o DFS).
   * - opts: Opciones de la búsqueda (criterio de parada, orden de vecinos).
   */
  struct DatosLectura {
    Grafo grafo;
    int origen = 1;
    int destino = 1;
    Algoritmo algoritmo = Algoritmo::kBfs;
    trace::OpcionesBusqueda opts;
  };

  /**
   * @brief Lee una instancia desde un stream en el formato de la práctica.
   * @param in Stream de entrada (por ejemplo, std::cin o un std::ifstream).
   * @return Problema con grafo construido, origen/destino y opciones.
   * @throws std::runtime_error Si hay errores de formato.
   */
  DatosLectura LeerFichero(std::istream& in);

  /**
    * @brief Lee una instancia desde un fichero en el formato de la práctica.
    * @param nombre_fichero Nombre del fichero a leer.
    * @return Problema con grafo construido, origen/destino y opciones.
    * @throws std::runtime_error Si no se puede abrir el fichero o hay errores de formato.
    */
  DatosLectura LeerFichero(const std::string& nombre_fichero);

  // Métodos de escritura 
  // Imprimimos la traza
  
  // Imprime la tabla de traza (delta por iteración o acumulada)
  void ImprimirTraza(std::ostream& out, const trace::ResultadoBusqueda& r, bool acumulada);
  
  // Imprime camino y coste (o mensaje de no encontrado)
  void ImprimirSolucion(const trace::ResultadoBusqueda& respuesta, std::ostream& out);
  
  // Imprime resumen de contadores y métricas
  void ImprimirResumen(const trace::ResultadoBusqueda& respuesta, std::ostream& out);
}   // namespace io

#endif