// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// Autor: Diego Vegas Acosta
// Correo: alu0101651361@ull.edu.es
// Fecha: 29/10/2024
// Archivo produccion.cc: Definición de la clase producción
// Referencias: 
// Enlaces de interés
// Historial de revisiones
// 29/10/2024 - Creación (primera versión) del código

#include <vector>

#include "NoTerminal.h"
#include "Alfabeto.h"

NoTerminal::NoTerminal() {
  identificador_ = '?';
  std::set<std::vector<char>> producciones;
  producciones_ = producciones;
}

NoTerminal::NoTerminal(char identificador, std::set<std::vector<char>> producciones) {
  identificador_ = identificador;
  producciones_ = producciones;
}

void NoTerminal::SetIdentificador(char id) {
  identificador_ = id;
}

void NoTerminal::SetProducciones(std::set<std::vector<char>> producciones) {
  producciones_ = producciones;
}

bool NoTerminal::operator<(const NoTerminal& no_terminal) const {
  return this->GetIdentificador() < no_terminal.GetIdentificador();
}

void NoTerminal::AgregarProduccion(std::vector<char> produccion) {
  producciones_.insert(produccion);
}