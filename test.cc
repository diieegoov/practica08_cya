#include <iostream>
#include <fstream>
#include <set>
#include <string>


void Test(std::string entrada) {
  std::fstream input(entrada);
  std::string linea;
  int contador = 0;
  std::set<char> simbolos;
  int longitud_no_terminales;
  while(getline(input, linea)) {
    if(contador == 1) {
      char sym;
      for(auto& c : linea) {
        sym = c;
      }
      std::cout << sym << "\n";
    }
    contador++;
  }
}

std::string LeerEntrada(char* argv[]) {
  return argv[1];
}

int main(const int argc, char* argv[]) {
  std::string entrada = LeerEntrada(argv);
  Test(entrada);
} 