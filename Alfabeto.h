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

#ifndef ALFABETO_H
#define ALFABETO_H

#include <set>

class Alfabeto {
 public:
  Alfabeto();  // Constructor por defecto
  Alfabeto(int, std::set<char>);  // Constructor de clase
  int GetCardinalidad() const { return cardinalidad_; }
  std::set<char> GetSimbolos() const { return simbolos_; }
  void SetCardinalidad(int);
  void SetSimbolos(std::set<char>);
 private:
  int cardinalidad_;
  mutable std::set<char> simbolos_;
};

#endif