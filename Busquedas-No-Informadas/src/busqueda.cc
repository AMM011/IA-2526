#include "busqueda.h"

#include <queue>
#include <stack>
#include <algorithm>

// Namespace con función helper
namespace {
//Comprueba si v ya aparece en el camino desde la raíz hasta u_idx
bool EstaEnCamino(int v, int index_u, const std::vector<NodoArbol>& arbol) {
  // Recorremos el camino del arbol de un nodo concreto, sustituyendo el valor por el de padre hasta llegar a 
  // -1, donde se encuentra el origen
  for (int x = index_u; x != -1 ; x = arbol[x].padre_idx) {
    if (v == arbol[x].id) return true;
  }
  return false;
} 
}

trace::ResultadoBusqueda busqueda::Bfs(const Grafo& g, int origen, int destino, const trace::OpcionesBusqueda& opts) {
  // Obtenemos el numero de vertices del grafo
  const int n = g.GetNumVertices();

  if (origen < 1 || origen > n || destino < 1 || destino > n) {
    throw std::out_of_range("origen/destino fuera de rango");
  }

  // Creamos un vector donde guardamos todos los nodos del árbol de busqueda
  std::vector<NodoArbol> arbol;
  arbol.push_back({origen, -1, 0.0, 0});  // Nodo raíz

  // Creamos una cola (frontera) donde vamos a ir almacenado los índices a arbol
  std::queue<int> frontera;
  // Almacenamos el primer índice del arbol
  frontera.push(0);

  trace::ResultadoBusqueda resultado;
  int iteracion = 0;

  while (!frontera.empty()) {
    // Creamos una variable registro, donde vamos a ir almacenando que pasa en cada iteración
    trace::RegistroIteracion registro;
    registro.paso = ++iteracion;
    
    const int index_actual = frontera.front();
    frontera.pop();

    const NodoArbol& nodo_actual = arbol[index_actual];

    registro.inspeccionados_delta.push_back(nodo_actual.id);

    resultado.nodos_inspeccionados++;

    if (nodo_actual.id == destino) {

      resultado.found = true;

      // Reconstrucción de camino usando pradre_idx
      std::vector<int> camino_rev;
      for (int x = index_actual; x != -1; x = arbol[x].padre_idx) {
        camino_rev.push_back(arbol[x].id);
      }

      // Invertimos los valores de camino_rev
      std::reverse(camino_rev.begin(),camino_rev.end());

      // Añadimos el camino al resultado
      resultado.camino = camino_rev;

      resultado.coste_total = 0.0;

      // Ahora hallamos el coste total
      for (size_t i = 0; i + 1 < resultado.camino.size(); ++i) {
        resultado.coste_total += g.GetPesoArista(resultado.camino[i], resultado.camino[i + 1]);
      }

      // Comprobamos si quiere que se detenga en la primera iteración
      if (opts.parar_a_primera_solucion) {
        resultado.traza.push_back(registro);
        return resultado;
      } else {
        resultado.traza.push_back(registro);
        continue;
      }
    }

    // Expandimos vecinos
    // Obtenemos los vecinos actuales
    const auto& vecinos_actuales = g.GetVecinosPorId(arbol[index_actual].id);

    // Añadimos los nuevos nodos generados al registro
    // for (size_t i = 0; i < vecinos_actuales.size(); ++i) {
    //   registro.generados_delta.push_back(vecinos_actuales[i].first);
    // }
    for(const auto& vecino : vecinos_actuales) {
      const int vecino_id = vecino.first;
      const double peso = vecino.second;
      
      // Comprobamos que el vecino no este ya en el camino,
      // asi evitamos cicls en el camino actual (tree-search)
      if (EstaEnCamino(vecino_id, index_actual, arbol)) continue;

      // Generamos al hijo (hoja)
      NodoArbol hijo{vecino_id, index_actual, nodo_actual.coste_acumulado + peso, nodo_actual.profundidad + 1};
      arbol.push_back(hijo);
      // Obtenemos el indice del hijo restandole al tamaño del arbol 1, ya que los hijos se van añadiendo
      // entonces su tamaño aumenta
      const int index_hijo = static_cast<int>(arbol.size()) - 1;

      // Añadimos el indice del hijo a la frontera
      frontera.push(index_hijo);
      // Añadimos el nuevo nodo generado
      registro.generados_delta.push_back(vecino_id);
      resultado.nodos_generados++;
    }
    resultado.traza.push_back(registro);
  }
  return resultado;
}

trace::ResultadoBusqueda busqueda::Dfs(const Grafo& g, int origen, int destino, const trace::OpcionesBusqueda& opts) {
  
}