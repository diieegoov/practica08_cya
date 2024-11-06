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

#include <iostream>

#include "Grammar2CNF.h"
#include "Gramatica.h"

int main(const int argc, char* argv[]) {
  if(!CheckCorrectParameters(argc, argv, 3)) {
    return 0;
  }
  std::string entrada = LeerEntrada(argv);
  Gramatica gramatica{entrada};
  gramatica.IsRightLinear();
  std::string salida = LeerSalida(argv);
  Gramatica gramatica_cnf = gramatica.CFG2CNF();
  gramatica_cnf.Imprimir(salida);
}