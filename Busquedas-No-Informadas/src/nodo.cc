#include "nodo.h"

// Utilizamos emplace_back porque como estoy creando el pair desde cero
// con los arguemntos vecino_id y peso, emplace_bacl() es la opcion más eficiente.
void Nodo::AnadirVecino(int vecino_id, double peso) {
  if (vecino_id < 1) {
    throw std::invalid_argument("El id del vecino no puede ser < 1, sino >= 1");
  } 
  if (peso < 0.0) {
    throw std::invalid_argument ("El peso de la arista no puede ser negativo");
  }

  // En caso de querer realizar una modificación en alguna arista existe, es decir, actualizar el peso y no añadir el nodo
  //for (auto& vecino: vecinos_) {
  //  if (vecino.first == vecino_id) vecino.second = peso;
  //}

  // Verificamos si el vecino existe o no
  if (!TieneVecino(vecino_id)) vecinos_.emplace_back(vecino_id, peso);
}

bool Nodo::TieneVecino(int vecino_id) const {
  for (const auto& vecino : vecinos_) {
    if (vecino.first == vecino_id) return true;
  }
  return false;
}