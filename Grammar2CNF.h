// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: Gramáticas en Forma Normal de Chomsky
// Autor: Diego Vegas Acosta
// Correo: alu0101651361@ull.edu.es
// Fecha: 29/10/2024
// Archivo Grammar2CNF.h: Declaración y definición 
// Referencias: 
// Enlaces de interés
// Historial de revisiones
// 29/10/2024 - Creación (primera versión) del código

#ifndef GRAMMAR2CNF_H
#define GRAMMAR2CNF_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>



bool CheckCorrectParameters(const int argc, char* argv[], int kCorrectNumber) {
  if((argc == 2) && (std::strcmp(argv[1], "--help") == 0)) {
    std::ifstream ayuda("help.txt");
    std::string linea;
    while(getline(ayuda, linea)) {
      std::cout << linea << std::endl;
    }
    return 0;
  }
  if(argc != kCorrectNumber) {
    std::cout << "Modo de empleo: ./Grammar2CNF input.gra output.gra\n";
    std::cout << "Pruebe ‘Grammar2CNF --help’ para más información.\n";
    return 0;
  }
  else {
    return 1;
  }
}

std::string LeerEntrada(char* argv[]) {
  return argv[1];
}

std::string LeerSalida(char* argv[]) {
  return argv[2];
}

#endif