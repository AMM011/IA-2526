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

  // Si existe, actualizamos y salimos
  for (auto& vecino: vecinos_) {
    if (vecino.first == vecino_id) {
      vecino.second = peso;
      return; 
    } 
  }

  // Si no existe, lo añadimos y salimos
  vecinos_.emplace_back(vecino_id, peso);
}

bool Nodo::TieneVecino(int vecino_id) const {
  for (const auto& vecino : vecinos_) {
    if (vecino.first == vecino_id) return true;
  }
  return false;
}