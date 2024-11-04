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

#ifndef NOTERMINAL_H
#define NOTERMINAL_H

#include <string>
#include <vector>
#include <set>

class NoTerminal {
 public:
  NoTerminal();  // Constructor por defecto
  NoTerminal(char, std::set<std::vector<char>>);  // Constructor de clase
  char GetIdentificador() const { return identificador_; }
  std::set<std::vector<char>> GetProducciones() const { return producciones_; }
  void SetIdentificador(char);
  void SetProducciones(std::set<std::vector<char>>);
  bool operator<(const NoTerminal& no_terminal) const;
  void AgregarProduccion(std::vector<char>);
 private:
  char identificador_;  // Nombre del no terminal
  mutable std::set<std::vector<char>> producciones_;
};

#endif