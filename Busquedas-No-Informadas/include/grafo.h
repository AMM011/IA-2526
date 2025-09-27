#ifndef GRAFO_H
#define GRAFO_H

#include "nodo.h"

#include <vector>
#include <cstddef>
#include <cstdint>
#include <utility>

class Grafo {
 public:
   /**
    * @brief Construye un grafo con un número dado de vértices.
    * @param num_vertices Número de vértices del grafo (>= 1).
    */
    explicit Grafo(int num_vertices);

    /**
     * @brief Duelve el número de vértices del grafo.
     * @return Número de vértices del grafo.
     */
    int GetNumVertices() const { return num_vertices_; }

    /**
     * @brief Añade una arista entre dos nodos del grafo.
     * @param u Identificador del primer nodo (1-based).
     * @param v Identificador del segundo nodo (1-based).
     * @param peso Peso de la arista (>= 0).
     * 
     * @note Si la arista ya existe, no hace nada.
     * 
     * @throw std::out_of_range Si u o v están fuera del rango [1, num_vertices].
     * @throw std::invalid_argument Si peso < 0.
     * 
     * @note El grafo no es dirigido, por lo que se añade la arista en ambos sentidos.
     */
    void AnadirAristaNoDirigida(int u, int v, double peso);

    /**
     * @brief Verifica si existe una arista entre dos nodos del grafo.
     * @param u Identificador del primer ndodo (1-based).
     * @param v Identificador del segundo nodo (1-based).
     * @return true si existe la arista entre u y v, false en caso contrario.
     */
    bool ExisteArista(int u, int v) const;

    /**
     * @brief Devuelve el peso de la arista entre dos nodos del grafo.
     * @param u Identificador del primer nodo (1-based).
     * @param v Identificador del segundo nodo (1-based).
     * @return Peso de la arista entre u y v, o -1 si no existe la arista.
     */
    double GetPesoArista(int u, int v) const;

    /**
     * @brief Devuelve la lista de vecinos de un nodo.
     * @param id Identificador del nodo (1-based).
     * @return Vector de pares (id, peso(costo)) de los vecinos del nodo.
     */
    std::vector<std::pair<int, double>> GetVecinosPorId(int id) const;

    /**
     * @brief Limpia todas las aristas del grafo.
     */
    void LimpiarAristas();

    /**
     * @brief Devuelve el nodo correspondiente a un identificador dado.
     * @param id Identificador del nodo (1-based).
     * @return Referencia constante al nodo con el identificador dado.
     */
    const Nodo& GetNodoPorId(int id) const;

 private:
  int num_vertices_;    ///< Contiene el número de vertices (1..N)

  std::vector<Nodo> nodos_;   ///< Contiene todos los nodos (cada uno con su id y vecinos)

  std::vector<std::vector<double>> pesos_;  ///< Matriz de presos (NxN): coste de la arista o -1 si no existe.

  void VerificarVerticeOExcepcion(int u) const; ///< Verifica que u está en [1, num_vertices_], si no lanza excepción.
};

#endif  // GRAFO_H