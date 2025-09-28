#ifndef NODO_H
#define NODO_H

#include <vector>
#include <utility>
#include <stdexcept>

/**
 * #brief Representa un nodo del grafo.
 * 
 * Cada nodo conoce su identificador y la lista de sus vecinos directos,
 * junto con el peso (costo) de la arista que los conecta.
 * 
 * La representación de los vecinos es un vector de pares (id, peso):
 * - id: Identificador del nodo vecino (1-based).
 * - peso: Peso (costo) de la arista.
 * 
 * Nota: El grafo no es dirigido, por lo que si el nodo A tiene como vecino al nodo B,
 * entonces el nodo B también debe tener como vecino al nodo A.
 * 
 * No contemplo en mi clase nodo los nodos padres por:
 * “Los padres son estado de la búsqueda, no del grafo. 
 *  Por eso uso parent[] local en BFS/DFS para reconstruir el camino al parar. 
 *  Así puedo correr múltiples búsquedas sin interferencias y mantener Nodo minimalista.”
 */
class Nodo {
 public:
  /**
   * @brief Construye un nodo con identitificador 1-based.
   * @param id Identificador del nodo (1-based).
   */
  explicit Nodo(int id) : id_(id) {}
  
  /**
   * @brief Devuelve el identificador del nodo.
   * @return Identificador del nodo (1-based).
   */
  int GetId() const { return id_; }

  /**
   * @brief Añade un vecino al nodo.
   * @param vecino_id Identificador del vecino (1-based).
   * @param peso Peso de la arista que conecta este nodo con el vecino (>= 0).
   * 
   * @note No elimina duplicados: si llamas dos veces con el mismo vecino_id,
   *       se insertan dos entradas. Normalmente se gestiona desde Grafo para 
   *       mantener una sola arista por par {u, v}.
   */
  void AnadirVecino(int veciono_id, double peso);

  /**
   * @brief Verifica si el vecino ya existe o no. 
   * @param vecino_id Identificador del vecino a verificar (1-based).
   * @return true si el vecino existe, false en caso contrario
   */
  bool TieneVecino(int vecino_id) const;

  /**
   * @brief Devuelve la lista de vecinos del nodo.
   * @return Vector de pares (id, peso(costo)) de los vecinos del nodo.
   */
  const std::vector<std::pair<int, double>>& GetVecinos() const { return vecinos_; }

  /**
   * @brief Elimina todos los vecinos del nodo.
   */
  void LimpiarVecinos() { vecinos_.clear(); }

  /**
   * 
   */
 private:
  int id_;  ///< Identificador del nodo (1-based).
  std::vector<std::pair<int, double>> vecinos_;  ///< Lista de vecinos del nodo (id, costo).
};

#endif  // NODO_H
