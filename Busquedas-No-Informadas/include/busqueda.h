#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include "grafo.h"
#include "nodo.h"
#include "trace.h"


/**
 * @brief Nodo del árbol de búsqueda.
 *         - id: estado del espacio de estados (1-based).
 *         - padre_idx: índice en un vector 'arbol' (o -1 si es la raíz).
 *         - coste_acumulado: coste acumulado hasta este nodo.
 *         - profundidad: número de niveles desde el estado inicial.
 */
struct NodoArbol {
  int id;           
  int padre_idx; 
  double coste_acumulado; 
  int profundidad;  
};

/**
 * @brief Implementa algoritmos de búsqueda no informada en grafos.
 */
class busqueda {
 public:
  /**
   * @brief Realiza una búsqueda en amplitud (BFS) en el grafo dado.
   * @param g Grafo donde se realiza la búsqueda.
   * @param origen Identificador del nodo de origen (1-based).
   * @param destion Identificador del nodo destion (1-based).
   * @param opts Opciones para la búsqueda (criterio de parada, orden de vecinos).
   * @return Resultado de la búsqueda, incluyendo si se encontró el destino,
   *         el camino desde origen a destino, el coste total, la traza de
   *         la búsqueda, y el total de nodos generados e inspeccionados.
   */
  trace::ResultadoBusqueda Bfs(const Grafo& g, int origen, int destino, const trace::OpcionesBusqueda& opts);

  /**
   * @brief Realiza una búsqueda en profundidad (DFS) en el grafo dado.
   * @param g Grafo donde se realiza la búsqueda.
   * @param origen Identificador del nodo de origen (1-based).
   * @param destion Identificador del nodo destion (1-based).
   * @param opts Opciones para la búsqueda (criterio de parada, orden de vecinos).
   * @return Resultado de la búsqueda, incluyendo si se encontró el destino,
   *         el camino desde origen a destino, el coste total, la traza de
   *         la búsqueda, y el total de nodos generados e inspeccionados.
   */
  trace::ResultadoBusqueda Dfs(const Grafo& g, int origen, int destino, const trace::OpcionesBusqueda& opts);
};
#endif  // BUSQUEDA_H