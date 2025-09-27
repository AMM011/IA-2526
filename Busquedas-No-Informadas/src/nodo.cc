#include "./include/nodo.h"

#include <stdexcept>
#include <utility>

// Utilizamos emplace_back porque como estoy creando el pair desde cero
// con los arguemntos vecino_id y peso, emplace_bacl() es la opcion más eficiente.
void Nodo::AnadirVecino(int veciono_id, double peso) {
  if (veciono_id < 1) {
    throw std::invalid_argument("El id del vecino no puede ser < 1, sino >= 1");
  } 
  if (peso < 0.0) {
    throw std::invalid_argument ("El peso de la arista no puede ser negativo");
  }
  vecinos_.emplace_back(veciono_id, peso);
}