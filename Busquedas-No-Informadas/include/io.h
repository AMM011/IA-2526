#ifndef IO_H
#define IO_H

#include "grafo.h"
#include "trace.h"

#include <iosfwd>
#include <string>


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
  
  /**
   * @brief Imprime la traza de la búsqueda en formato tabla.
   * @param out Stream de salida (por ejemplo, std::cout o un std::ofstream).
   * @param r Resultado de la búsqueda, incluyendo la traza.
   * @param acumulada Si es true, imprime los totales acumulados; si es false, imprime los deltas por iteración.
   */
  void ImprimirTraza(std::ostream& out, const trace::ResultadoBusqueda& r, bool acumulada = false);
  
  /**
   * @brief Imprime el camino solución y su coste total.
   * @param out Stream de salida (por ejemplo, std::cout o un std::ofstream).
   * @param r Resultado de la búsqueda, incluyendo el camino y coste.
   */
  void ImprimirSolucion(std::ostream& out, const trace::ResultadoBusqueda& r);
  
    /**
     * @brief Imprime un resumen final de la búsqueda.
     * @param out Stream de salida (por ejemplo, std::cout o un std::ofstream).
     * @param r Resultado de la búsqueda, incluyendo totales de nodos generados e inspeccionados.
     */
  void ImprimirResumen(std::ostream& out, const trace::ResultadoBusqueda& r);
}   // namespace io

#endif