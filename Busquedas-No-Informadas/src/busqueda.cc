#include "busqueda.h"

#include <queue>
#include <stack>
#include <algorithm>

trace::ResultadoBusqueda busqueda::Bfs(const Grafo& g, int origen, int destino, const trace::OpcionesBusqueda& opts) {
  // Obtenemos el numero de vertices del grafo
  int n = g.GetNumVertices();

  if (origen < 1 || origen > n || destino < 1 || destino > n) {
    throw std::out_of_range("origen/destino fuera de rango");
  }

  // Comenzamos creando la cola, aqui se van los nodos por visitar
  std::queue<int> fronteras;
  // Creamos un vector donde vamos almacenar los nodos visitados
  std::vector<bool> visitados(n, false);
  // Creamos un vector padre, para construir un camino al final
  std::vector<int> padre(n, 0);
  // Creamos una estructura ResultadoBusqueda, donde vamos almacenar el resultado
  trace::ResultadoBusqueda resultado;

  int origen_idx = origen - 1;

  // Comenzamos metiendo el origen a la frontera, ya que es el primer nodo
  fronteras.push(origen);
  // Marcamos el origen como visitado visitado
  visitados[origen_idx] = true;
  // Añadimos el origen como sin padre
  padre[origen_idx] = 0;
  // Inicializamos el contador de iteraciones en 0
  int iteracion = 0;

  // Comenzamos el bucle, mientras la cola no este vacia 
  while (!fronteras.empty()) {
    ++iteracion;
    // Creamos la estructura del registo, para ir almacenado los datos
    trace::RegistroIteracion registro;
    registro.paso = iteracion;
    
    // Extraemos el nodo actual de la frontera (la cola)
    int id_nodo_actual = fronteras.front();
    fronteras.pop();

    // Añadimos el nodo actual al registro
    registro.inspeccionados_delta.push_back(id_nodo_actual);

    // Aumentamos el valor de nodos inspenccionados del resultado
    resultado.nodos_inspeccionados++;

    // Ahora comprobamos si es el objetivo y si la opción de detenerse cuando se encuentra
    // esta activada
    if (id_nodo_actual == destino) {
      resultado.found = true;
      
      // Reconstruir camino usando el vector padre
      std::vector<int> camino_temp;
      int actual = destino;
      while (actual != 0) { // 0 significa sin padre
        camino_temp.push_back(actual);
        actual = padre[actual - 1]; // Convertimos a base-0
      }

      // Invertimos para tener camino origen -> destino
      std::reverse(camino_temp.begin(), camino_temp.end());
      resultado.camino = camino_temp;

      // Calcumos el coste total
      for (size_t i = 0; i < resultado.camino.size() - 1; ++i) {
        resultado.coste_total += g.GetPesoArista(resultado.camino[i], resultado.camino[i+1]);
      }

      // Guardamos registro 
    //   resultado.traza.push_back(registro);

      if (opts.parar_a_primera_solucion) {
        resultado.traza.push_back(registro);
        return resultado;
      }
    }

    // Expansión de vecinos
    const auto& vecinos_actual_del_id = g.GetVecinosPorId(id_nodo_actual);
    
    // Recorremos la lista g.
    for (const auto& vecino : vecinos_actual_del_id) {
      int vecino_id = vecino.first;
      int vecino_idx = vecino_id - 1;   // Conversión explícita a base-0

      // Si el nodo actual no esta visitado, entramos dentro
      if (!visitados[vecino_idx]) {
        // Lo marcamos como visitado
        visitados[vecino_idx] = true;

        // Colocamos el id del nodo actual dentro del vector de los padres
        padre[vecino_idx] = id_nodo_actual;

        // Lo añadimos en la cola
        fronteras.push(vecino_id);

        // Lo añadimos a registro.generados_delta
        registro.generados_delta.push_back(vecino_id);

        // Aumentamos el contador de nodos_generados
        resultado.nodos_generados++;
      }
    }
    // Guardamos el resultado en el registro
    resultado.traza.push_back(registro);
  }

  return resultado;
}

trace::ResultadoBusqueda busqueda::Dfs(const Grafo& g, int origen, int destino, const trace::OpcionesBusqueda& opts) {
  
}