#include "grafo.h"

Grafo::Grafo(int num_vertices) {
  if (num_vertices < 1) throw std::invalid_argument("El número de vertices no puede ser < 1");
  num_vertices_ = num_vertices;
  nodos_.reserve(num_vertices);
  for (int i = 1; i <= num_vertices; ++i) nodos_.emplace_back(i);
  //Inicializamos la matriz adyacente de ponderación con numero de vertices
  // Además, inicializamos las aristas en -1.0, porque aun no existe arista entre los nodos
  // El guión dice: d(i,j) = -1 si no hay una arista que conecte al vertice i con el vertice j.
  pesos_.assign(num_vertices, std::vector<double>(num_vertices, -1.0));
  for (int i = 0; i < num_vertices_; ++i) {
    pesos_[i][i] = 0;   // d(i,i) = 0
  }
}

void Grafo::VerificarVerticeOExcepcion(int u) const {
  if (u < 1) throw std::out_of_range("El vértice no debe ser < 1.");
  if (u > num_vertices_) throw std::out_of_range("El vértice no puede ser > num_vertices_.");
}

void Grafo::AnadirAristaNoDirigida(int u, int v, double peso) {
  // Verificación de que los valores sean validos
  VerificarVerticeOExcepcion(u);
  VerificarVerticeOExcepcion(v);
  if (u == v) throw std::invalid_argument("Self-loop no permitido.");   // Ignorar bucles propios
  if (peso < 0.0) throw std::invalid_argument("El peso no debe ser < 0.0");

  if (ExisteArista(u,v)) return;
  
  // Añadimos los pesos de las aristas a sus respectivos nodos, recordando que es un grafo no dirgido
  // con lo que si se le añado de A a B, también se tiene que hacer de B a A.
  pesos_[u-1][v-1] = peso;
  pesos_[v-1][u-1] = peso;

  // Añadimos los nuevos vecinos
  nodos_[u-1].AnadirVecino(v, peso);
  nodos_[v-1].AnadirVecino(u, peso);
}

bool Grafo::ExisteArista(int u, int v) const {
  // Comprobamos que los valores sean validos.
  VerificarVerticeOExcepcion(u);
  VerificarVerticeOExcepcion(v);
  // Verificamos si ya existe una arista entre el nodo u y v,
  // porque si existiera, quiere decir que ya estan agregados como vecinos,
  // con lo que si en pesos_[u-1][v-1] != -1.0 quiere decir que ya hay un peso en la arista
  // entonces según d(i,j) = -1 cuando no hay arista que conecte los vertices, en caso contrario si la hay
  if (pesos_[u-1][v-1] != -1.0) return true;
  return false;
}

double Grafo::GetPesoArista(int u, int v) const {
  if (ExisteArista(u,v)) return pesos_[u-1][v-1];   // Acedemos a la matriz adyacente de ponderación, la cual contiene los pesos de las aristas.
  return -1.0;
}

const std::vector<std::pair<int, double>>& Grafo::GetVecinosPorId(int id) const {
  VerificarVerticeOExcepcion(id);   // Validamos que el id este dentro de los parametros posibles.
  return nodos_[id-1].GetVecinos(); // Accedemos al vector de nodos (0-based) mediante el id, devolviendonos un nodo para poder llamar al método.
}

void Grafo::LimpiarAristas() {
  // Eliminamos todas las pesos de las aristas y las inicialimos a -1.0 d(i,j) = -1 si no hay una arista que conecte al vértice i con el vértice j. 
  // Con assign reemplazamos el contenido, mantenemos la estructura correcta
  pesos_.assign(num_vertices_, std::vector<double>(num_vertices_, -1.0));
  // Recordemos que d(i,i) = 0
  for (int i = 0; i < num_vertices_; ++i) pesos_[i][i] = 0.0;
  // Ahora eliminamos los vecinos de todos los nodos
  for (auto& nodo : nodos_) {
    nodo.LimpiarVecinos();
  }
}

const Nodo& Grafo::GetNodoPorId(int id) const {
  VerificarVerticeOExcepcion(id);
  return nodos_[id - 1];
}