#include "./include/grafo.h"

#include <stdexcept>
#include <vector>

Grafo::Grafo(int num_vertices) {
  if (num_vertices < 1) throw std::invalid_argument("El número de vertices no puede ser < 1");
  num_vertices_ = num_vertices;
  nodos_.reserve(num_vertices);
  for (int i = 1; i <= num_vertices; ++i) nodos_.emplace_back(i);
  //Inicializamos la matriz adyacente de ponderación con numero de vertices
  pesos_.resize(num_vertices, std::vector<double>(num_vertices, -1.0));
}

void Grafo::VerificarVerticeOExcepcion(int u) const {
  if (u < 1) throw std::out_of_range("La arista no debe ser < 1.");
  if (u > num_vertices_) throw std::out_of_range("La arista no puede ser > num_vertices_.");
}

void Grafo::AnadirAristaNoDirigida(int u, int v, double peso) {
  // Verificación de que los valores sean validos
  VerificarVerticeOExcepcion(u);
  VerificarVerticeOExcepcion(v);
  if (u == v) return;   // Ignorar bucles propios
  if (peso < 0.0) throw std::invalid_argument("El peso no debe ser < 0.0");
  
  // Añadimos los pesos de las aristas a sus respectivos nodos, recordando que es un grafo no dirgido
  // con lo que si se le añado de A a B, también se tiene que hacer de B a A.
  pesos_[u-1][v-1] = peso;
  pesos_[v-1][u-1] = peso;

  // Añadimos los nuevos vecinos
  nodos_[u-1].AnadirVecino(v, peso);
  nodos_[v-1].AnadirVecino(u, peso);
}