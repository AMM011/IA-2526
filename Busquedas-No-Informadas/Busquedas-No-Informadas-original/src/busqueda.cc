#include "busqueda.h"

#include <queue>
#include <stack>
#include <stdexcept>
#include <algorithm>
// para rng
#include <random>

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

  // Iteración 1: origen generado, aun no inspeccionado
  
  trace::RegistroIteracion registro0;
  registro0.paso = ++iteracion;        // paso = 1
  registro0.generados_delta.push_back(origen);
  resultado.nodos_generados++;        // contamos el origen como generado
  resultado.traza.push_back(registro0);
  

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
  // Obtenemos el numero de vertices del grafo
  const int n = g.GetNumVertices();

  if (origen < 1 || origen > n || destino < 1 || destino > n) {
    throw std::out_of_range("origen/destino fuera de rango");
  }

  // Creamos el arbol
  std::vector<NodoArbol> arbol;
  arbol.push_back({origen, -1, 0.0, 0});

  // Creamos la frontera, podemos usar una stack, pero yo prefiero usar un vector
  std::vector<int> stack;
  stack.push_back(0);

  // next_pos será un vector paralelo a arbol y stack que nos dice
  // añun no he explorado ningun vecino de este nodo.
  std::vector<int> next_pos;
  next_pos.push_back(0);

  trace::ResultadoBusqueda resultado;
  int iteracion = 0;

  // Iteración 1: origen generado, aun no inspeccionado
  trace::RegistroIteracion registro0;
  registro0.paso = ++iteracion;        // paso = 1
  registro0.generados_delta.push_back(origen);
  resultado.nodos_generados++;        // contamos el origen como generado
  resultado.traza.push_back(registro0);

  
  while (!stack.empty()) {
    trace::RegistroIteracion registro;

    while (!stack.empty()) {
      int index_actual = stack.back();
      const NodoArbol& nodo_actual = arbol[index_actual];

      // Inspeccionamos al entrar por primera vez
      if (next_pos[index_actual] == 0) {
        registro.inspeccionados_delta.push_back(nodo_actual.id);
        resultado.nodos_inspeccionados++;

        // ¿Objetivo?
        if (nodo_actual.id == destino) {
          resultado.found = true;

          // Camino + coste
          std::vector<int> camino_rev;
          for (int x = index_actual; x != -1; x = arbol[x].padre_idx) camino_rev.push_back(arbol[x].id);
          std::reverse(camino_rev.begin(), camino_rev.end());
          resultado.camino = camino_rev;

          resultado.coste_total = 0.0;
          for (size_t i = 0; i + 1 < resultado.camino.size(); ++i) {
            resultado.coste_total += g.GetPesoArista(resultado.camino[i], resultado.camino[i + 1]);
          }

          registro.paso = ++iteracion;
          resultado.traza.push_back(std::move(registro));
          if (opts.parar_a_primera_solucion) return resultado;
          // Si no paramos, seguimos intentando expandir (como cualquier nodo)
        }
      }

      // Intentamos generar exactamente un hijo desde este nodo
      const auto& vecinos = g.GetVecinosPorId(nodo_actual.id);
      int& pos = next_pos[index_actual];

      bool genero_hijo = false;
      // Este while avanza pos hasta encontrar un vecino válido o agotar
      while (pos < static_cast<int>(vecinos.size())) {
        int vecino_id = vecinos[pos].first;
        double peso   = vecinos[pos].second;
        ++pos; // avanza el cursor

        if (EstaEnCamino(vecino_id, index_actual, arbol)) continue;

        // Generar hijo y descender
        NodoArbol hijo{vecino_id, index_actual,
                       nodo_actual.coste_acumulado + peso,
                       nodo_actual.profundidad + 1};
        arbol.push_back(hijo);
        int index_hijo = static_cast<int>(arbol.size()) - 1;

        // Se añade el hijo a next_pos y stack
        next_pos.push_back(0);
        stack.push_back(index_hijo);

        registro.generados_delta.push_back(vecino_id);
        resultado.nodos_generados++;

        genero_hijo = true;
        break; // solo un hijo por iteración
      }

      if (genero_hijo) {
        break; // cerramos la iteración con este generado
      }

      // Si este nodo no puede generar más hijos, retrocedemos y seguimos en la misma iteración
      if (pos >= static_cast<int>(vecinos.size())) {
        stack.pop_back();
        continue; // intentará el padre en este mismo paso
      }

      // Si llegamos aquí, significa que aún quedan vecinos por probar, pero no se generó hijo
      // (por ejemplo, todos eran ciclos). Volverá a intentar en la próxima vuelta del bucle interno.
      }

    // Registramos esta iteración solo si hubo inspecciones o generados
    // Con esto logramos compactar las iteraciones de backtracking sin eventos
    if (!registro.inspeccionados_delta.empty() || !registro.generados_delta.empty()) {
      registro.paso = ++iteracion;
      resultado.traza.push_back(std::move(registro));
    } else {
      // No hubo nada que registrar (pila vacía sin nuevos eventos)
      break;
    }
  }
  return resultado;
}

trace::ResultadoBusqueda busqueda::