// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// Autor: Diego Vegas Acosta
// Correo: alu0101651361@ull.edu.es
// Fecha: 29/10/2024
// Archivo produccion.h: Declaración de la clase producción
// Referencias: 
// Enlaces de interés
// Historial de revisiones
// 29/10/2024 - Creación (primera versión) del código

#include <set>
#include <iostream>
#include <cassert>

#include "Alfabeto.h"

Alfabeto::Alfabeto() {
  cardinalidad_ = 0;
  std::set<char> simbolos;
  simbolos_ = simbolos;
}

Alfabeto::Alfabeto(int cardinalidad, std::set<char> simbolos) {
  for(auto& simbolo : simbolos) {
    if(simbolo == '&') {
      std::cout << "En el alfabeto no puede estar la cadena vacía.\n";
      std::cout << "Pruebe ‘./Grammar2CNF --help’ para más información.\n";
      assert(0);
    }
  }
  cardinalidad_ = cardinalidad;
  simbolos_ = simbolos;
}

void Alfabeto::SetCardinalidad(int cardinalidad) {
  cardinalidad_ = cardinalidad;
}

void Alfabeto::SetSimbolos(std::set<char> simbolos) {
  simbolos_ = simbolos;
}
