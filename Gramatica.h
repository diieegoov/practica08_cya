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

#ifndef GRAMATICA_H
#define GRAMATICA_H

#include "Alfabeto.h"
#include "NoTerminal.h"


class Gramatica {
 public:
  Gramatica();  // Constructor por defecto
  Gramatica(std::string);  // Constructor de clase
  Alfabeto GetAlfabeto() const { return alfabeto_; }
  std::set<NoTerminal> GetNoTerminales() const { return no_terminales_; }
  void SetAlfabeto(Alfabeto);
  void SetNoTerminales(std::set<NoTerminal>);
  void AgregarNoTerminal(NoTerminal);  // Las nuevas producciones y el identificador
  void Imprimir(std::string);
  char GenerarIdentificador();
  void ReemplazarProduccion(std::vector<char>, std::vector<char>);
  void GuardarProduccionOrdenada(NoTerminal, std::vector<char>);
  std::vector<char> ReemplazarTerminales(std::vector<char>, std::vector<NoTerminal>);
  void PasoDiezCNF(char, std::vector<char>);
  Gramatica CFG2CNF();
 private:
  Alfabeto alfabeto_;
  mutable std::set<NoTerminal> no_terminales_;
};

#endif