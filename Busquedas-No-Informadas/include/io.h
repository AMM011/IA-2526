#include "grafo.h"
#include "trace.h"

#include <fstream>

namespace io {
  /**
   * @brief Estructura problema que contiene los datos de lectura
   * - grafo: El grafo donde se realiza la búsqueda.
   * - origen: Nodo de origen (1-based).
   * - destino: Nodo destino (1-based).
   * - usar_bfs: true = BFS, false = DFS.
   * - opts: Opciones de la búsqueda (criterio de parada, orden de vecinos).
   */
  struct Problema {
    Grafo grafo;
    int origen;
    int destino;
    bool usar_bfs;
    trace::OpcionesBusqueda opts;
  };

  // Lee desde un istream (sirve para fichero o stdin)
  Problema LeerFichero(std::istream& in);

  // Metodos de escritura 
  void ImprimirTraza(const trace::ResultadoBusqueda& respuesta, )
  
}