#include "io.h"
#include "busqueda.h"

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
  if (argc < 5) {
    std::cerr << "Uso: " << argv[0]
              << " <fichero_grafo> <origen> <destino> <algoritmo: bfs|dfs> [--acumulada] [--parar] [--out <fichero_salida>]\n";
    return 1;
  }

  std::string fichero_grafo = argv[1];
  int origen = std::stoi(argv[2]);
  int destino = std::stoi(argv[3]);
  std::string alg_str = argv[4];
  std::string fichero_salida = "salida.txt";

  bool acumulada = false;
  bool parar = false;

  for (int i = 5; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "--acumulada") acumulada = true;
    else if (arg == "--parar") parar = true;
    else if (arg == "--out" && i + 1 < argc) {
      fichero_salida = argv[i + 1];
      ++i;
    }
  }

  std::ofstream fout(fichero_salida);
  if (!fout) {
    std::cerr << "No se pudo abrir fichero de salida: " << fichero_salida << "\n";
    return 1;
  }

  busqueda busq;

  try {
    io::DatosLectura datos = io::LeerFichero(fichero_grafo);
    datos.origen = origen;
    datos.destino = destino;
    datos.opts.parar_a_primera_solucion = parar;

    if (alg_str == "bfs") datos.algoritmo = io::Algoritmo::kBfs;
    else if (alg_str == "dfs") datos.algoritmo = io::Algoritmo::kDfs;
    else throw std::runtime_error("Algoritmo desconocido: " + alg_str);

    trace::ResultadoBusqueda resultado;
    if (datos.algoritmo == io::Algoritmo::kBfs) {
      resultado = busq.Bfs(datos.grafo, datos.origen, datos.destino, datos.opts);
    } else {
      resultado = busq.Dfs(datos.grafo, datos.origen, datos.destino, datos.opts);
    }

    // Impresión
    // Obtenemos n que es el número de nodos del grafo
    const int n = datos.grafo.GetNumVertices();
    // Obtenemos m que es el número de aristas del grafo
    // Para ello, sumamos el número de vecinos de cada nodo y dividimos entre 2
    // (porque el grafo es no dirigido y cada arista aparece dos veces).
    size_t m = 0;
    for (int i = 1; i <= n; ++i) m += datos.grafo.GetVecinosPorId(i).size();
    m /= 2;  // cada arista aparece dos veces en vecinos (grafo no dirigido)

    fout << "-----------------------------------------\n";
    fout << "Número de nodos del grafo: " << n << "\n";
    fout << "Número de aristas del grafo: " << m << "\n";
    fout << "Vértice origen: " << origen << "\n";
    fout << "Vértice destino: " << destino << "\n";
    // io::ImprimirTraza(fout, resultado, acumulada);
    io::ImprimirTrazaEstiloGuion(fout, resultado, origen);
    io::ImprimirSolucion(fout, resultado);
    io::ImprimirResumen(fout, resultado);

  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}