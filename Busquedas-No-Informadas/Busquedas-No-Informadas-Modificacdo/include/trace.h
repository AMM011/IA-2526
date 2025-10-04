#ifndef TRACE_H
#define TRACE_H

#include <vector>

/**
 * @brief Trace sirve para registrar lo que pasa en cada iteración (qué inspeccionamos y que generamos)
 *        y empaquetar el resultado fina (camino y coste) de forma clara. Así, BFS/DFS solo emiten eventos
 *        y leugo io.cc sabe exactamente qué imprimir.
 * 
 * Puntos claves:
 *        - Logramos mostrar por iteración los nodods inspeccionados (sacados y expandidos) y los nodos generadores (añadidos a la frontera).
 *        - Separación de responsabilidades:
 *              - search.cc: se centra en la lógica (cola/pila, visitados, padres...).
 *              - io.cc: se centra en formateear la salida (tabla, acumulados, camino, coste).
 *        - Flexibilidad: En caso de cambio, como el criterio de parada o el formatio de la tabla (delta/acumulado), no tocamos la lógica de BFS/DFS, 
 *                        solo cómo presentamos la traza.
 */
namespace trace {

/**
 * @brief Registro de una iteración del algoritmo de búsqueda.
 *         - Contiene el paso (número de iteración).
 *         - Los nodos inspeccionados en esta iteración (sacados de la frontera y expandidos).  
 *         - Los nodos generados en esta iteración (vecinos descubriertos, añadidos a la frontera). 
 *        Delta = solo lo nuevo de esa iteración.
 */
struct RegistroIteracion {
  int paso = 0;
  std::vector<int> inspeccionados_delta;
  std::vector<int> generados_delta;
};

/**
 * @brief Resultado final de la búsqueda.
 *         - Indica si se encontró el nodo objetivo.
 *         - El camino desde el nodo origen al destino (si se encontró)(1-based).
 *         - El coste total del camino (si se encontró).
 *         - La traza completa de la búsqueda (registro por iteración).
 *         - Suma de todos los generados_delta.size() = nodos generados totales.
 *         - Suma de todos los inspeccionados_delta.size() = nodos inspeccion
 */
struct ResultadoBusqueda {
  bool found = false;
  std::vector<int> camino;
  double coste_total = 0.0;
  std::vector<RegistroIteracion> traza;
  size_t nodos_generados = 0;
  size_t nodos_inspeccionados = 0;
};

/**
 * @brief Opciones de busquedas.
 *         - parar_a_primera_solución:
 *             - true = paramos al inspeccionar el destino.
 *             - false = continuamos.
 *         - vecinos_ascendientes:
 *             - true = expandir vecinos en orden creciente (determinismo).
 *             - false = no ascendientes.
 */
struct OpcionesBusqueda {
  bool parar_a_primera_solucion = true;
  bool vecinos_ascendientes = true;
};
}

#endif