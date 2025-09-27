#include "./include/grafo.h"

Grafo::Grafo(int num_vertices) {
  if (num_vertices < 1) throw std::invalid_argument("El número de vertices no puede ser < 1");
  num_vertices_ = num_vertices;
  nodos_.reserve(num_vertices);
  for (int i = 1; i <= num_vertices; ++i) nodos_.emplace_back(i);

  
}

void Grafo::AnadirAristaNoDirigida(int u, int v, double peso) {
  
}