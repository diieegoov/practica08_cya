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
#include <cassert>
#include <fstream>
#include <vector>

#include "Gramatica.h"

Gramatica::Gramatica() {
  Alfabeto alfabeto;
  std::set<NoTerminal> no_terminales;
  alfabeto_ = alfabeto;
  no_terminales_ = no_terminales;
}

/// @brief Constructor de clase
/// @param entrada nombre del archivo de entrada
Gramatica::Gramatica(std::string entrada) {
  ComprobarErrores(entrada);
  std::fstream input(entrada);
  std::string linea;
  int contador = 0;
  Alfabeto alfabeto;
  std::set<char> simbolos;
  int longitud_no_terminales;
  NoTerminal no_terminal;
  std::set<NoTerminal> no_terminales;
  std::vector<std::vector<char>> producciones_con_id;
  std::vector<std::vector<char>> producciones_sin_id;
  int cardinalidad;
  while(getline(input, linea)) {
    // Número de símbolos en el alfabeto
    if(contador == 0) {
      alfabeto.SetCardinalidad(std::stoi(linea));
      cardinalidad = std::stoi(linea);
    }
    // Alfabeto de la gramática
    if((contador <= alfabeto.GetCardinalidad()) && (contador != 0)) {
      char symbol;
      for(auto& caracter : linea) {
        symbol = caracter;
      }
      simbolos.insert(symbol);
    }
    if(contador == alfabeto.GetCardinalidad()) {
      alfabeto.SetSimbolos(simbolos);
    }
    // Número de no terminales de la gramática
    if(contador == (alfabeto.GetCardinalidad() + 1)) {
      longitud_no_terminales = std::stoi(linea);
    }
    // No terminales de la gramática 
    if((contador <= (alfabeto.GetCardinalidad() + 1 + longitud_no_terminales)) && (contador > (alfabeto.GetCardinalidad() + 1))) {
      char identificador;
      for(auto& id : linea) {
        identificador = id;
      }
      no_terminal.SetIdentificador(identificador);
      no_terminales.insert(no_terminal);
    }
    if(contador > (cardinalidad + 2 + longitud_no_terminales)) {
      std::vector<char> cadena;
      std::vector<char> produccion;
      int counter = 0;
      // Metemos el string de producción en produccion cono char's
      for(char& simbolo : linea) {
        if(simbolo == '&') {
          std::cout << "No pueden haber producciones vacías '&' en la gramática.\n";
          std::cout << "Línea: " << contador + 1 << std::endl;
          assert(0);
        }
        if(simbolo != ' ') {  // No se guardan los espacios para hacerlo más simple
          // Produccion es el vector que será el atributo, pero cadena lo usaremos para comprobar
          // errores y localizar el no terminal al que pertenece la producción
          if(counter != 0) {
            produccion.push_back(simbolo);
          }
          cadena.push_back(simbolo);  // Por eso sabemos que las prodm empiezan en cadena[1]
        }
        counter++;
      }
      // Comprobamos que no haya producciones unitarias
      if(produccion.size() == 1) {
        for(auto& nonterminales : no_terminales) {
          if(nonterminales.GetIdentificador() == produccion[0]) {
            std::cout << "No pueden haber producciones unitarias en la gramática.\n";
            assert(0);
          }
        }
      }
      producciones_con_id.push_back(cadena);
      producciones_sin_id.push_back(produccion);
    }
    contador++;
  }
  
  int size = producciones_con_id.size();
  NoTerminal nonterminal;
  NoTerminal nonterminal_segundo;
  nonterminal.SetIdentificador(producciones_con_id[0][0]);
  nonterminal.AgregarProduccion(producciones_sin_id[0]);
  char identificador;
  std::vector<char> produccion;
  std::set<NoTerminal> no_terminales_finales;
  for(int i = 1; i < size; i++) {
    identificador = producciones_con_id[i][0];
    produccion = producciones_sin_id[i];
    if(nonterminal.GetIdentificador() == identificador) {
      nonterminal.AgregarProduccion(produccion);
    }
    else {
      no_terminales_finales.insert(nonterminal);
      NoTerminal nonterminal_segundo;
      nonterminal_segundo.SetIdentificador(identificador);
      nonterminal_segundo.AgregarProduccion(produccion);
      nonterminal = nonterminal_segundo;
    }
    if(i == (size - 1)) {
      no_terminales_finales.insert(nonterminal);
    }
  }
  
  // Comprobar si están los símbolos de las cadenas en el alfabeto o son no terminales
  std::set<char> identificadores;
  for(auto& nont : no_terminales_finales) {
    identificadores.insert(nont.GetIdentificador());
  }
  for(auto& producc : producciones_con_id) {
    for(auto& symbol : producc) {
      if((alfabeto.GetSimbolos().count(symbol) == 0) && (identificadores.count(symbol) == 0)) {
        std::cout << "El símbolo '" << symbol << "' no pertenece ni al alfabeto ni es un no terminal.\n";
        assert(0);
      }
    }
  }

  alfabeto_ = alfabeto;
  no_terminales_ = no_terminales_finales;
}


/// @brief modifica una produccion y cambia un símbolo de ella
/// @param simbolo nuevo a cambiar en la cadena de produccion
/// @param identificador no terminal al que pertenece la produccion
/// @param producciones produccion a la que vamos a cambiar el símbolo
/// @return nueva producion modificada
std::vector<char> ReemplazarSimbolos(char simbolo, char identificador, std::vector<char>  producciones) {
  std::vector<char> nueva_cadena;
  for(auto& symbol : producciones) {
    if(symbol == simbolo) {
      nueva_cadena.push_back(identificador);
    }
    nueva_cadena.push_back(symbol);
  }
  return nueva_cadena;
}

void Gramatica::SetAlfabeto(Alfabeto alfabeto) {
  alfabeto_ = alfabeto;
}

void Gramatica::SetNoTerminales(std::set<NoTerminal> producciones) {
  no_terminales_ = producciones;
}

void Gramatica::AgregarNoTerminal(NoTerminal nonterminal) {
  no_terminales_.insert(nonterminal);
}


/// @brief Estudia la gramática y crea un identificador nuevo que no esté ya en la grámatica
/// @return char con el identificador nuevo para la gramática
char Gramatica::GenerarIdentificador() {
  for(char id = 'A'; id <= 'z'; id++) {
    bool existe = false;
    for(auto& nonterminal : this->GetNoTerminales()) {
      if((nonterminal.GetIdentificador() == id) || (this->GetAlfabeto().GetSimbolos().count(id) == 1)){
        existe = true;
      }
    }
    if(existe == false) {
      return id;
    }
  }
  return '?';
}

/// @brief Reemplaza una produccion por otra en el no terminal recibido
/// @param prod cadena de produccion anterior
/// @param nueva_produccion nueva cadena de produccion que reemplaza a la otra
/// @param identificador_produccion identificador del no terminal
void Gramatica::ReemplazarProduccion(std::vector<char> prod, std::vector<char> nueva_produccion, char identificador_produccion) {
  std::set<NoTerminal> producciones;
  for(auto& nonterminales : this->GetNoTerminales()) {
    NoTerminal no_terminal;
    no_terminal.SetIdentificador(nonterminales.GetIdentificador());
    for(auto& produccion : nonterminales.GetProducciones()) {
      if(identificador_produccion == nonterminales.GetIdentificador()) {
        if(prod == produccion) {
          no_terminal.AgregarProduccion(nueva_produccion);
        }
        else {
          no_terminal.AgregarProduccion(produccion);
        }
      }
      else {
        no_terminal.AgregarProduccion(produccion);
      }
    }
    producciones.insert(no_terminal);
  }
  this->SetNoTerminales(producciones);
}

/// @brief Obtiene un no terminal y una produccion y hace todo el proceso de guardar o crear un no terminal nuevo si no existe
/// @param nonterminales no terminal en el que se quiera guardar la produccion
/// @param producciones produccion a guardar
void Gramatica::GuardarProduccionOrdenada(NoTerminal nonterminales, std::vector<char> producciones) {
  int size = this->GetNoTerminales().size();
  NoTerminal no_terminal;
  std::set<NoTerminal> nonterminales_finales;
  if (size == 0) {
    no_terminal.SetIdentificador(nonterminales.GetIdentificador());
    no_terminal.AgregarProduccion(producciones);
    this->AgregarNoTerminal(no_terminal);
  }
  else {
    bool existe = false;
    for(auto& nonterminal : this->GetNoTerminales()) {
      if(nonterminal.GetIdentificador() == nonterminales.GetIdentificador()) {
        no_terminal = nonterminal;
        no_terminal.AgregarProduccion(producciones);
        nonterminales_finales.insert(no_terminal);
        existe = true;
      }
      else {
        nonterminales_finales.insert(nonterminal);
      }
    }
    // Si existe == false después de haber recorrido todos los nonterminales, es que es un no terminal nuevo
    if(existe == false) {
      no_terminal.SetIdentificador(nonterminales.GetIdentificador());
      no_terminal.AgregarProduccion(producciones);
      nonterminales_finales.insert(no_terminal);
    }
    this->SetNoTerminales(nonterminales_finales);
  }
}
  
/// @brief Reemplaza simbolos terminales
/// @param produccion cadena con terminales
/// @param nuevos_ids identificadores de los no terminales nuevos
/// @return nueva cadena con terminals modificados a no terminales
std::vector<char> Gramatica::ReemplazarTerminales(std::vector<char> produccion, std::vector<NoTerminal> nuevos_ids) {
  std::vector<char> reemplazo;
  for(auto& simbolo : produccion) {
    if(this->GetAlfabeto().GetSimbolos().count(simbolo) == 1) {
      for(auto& nonterminal : nuevos_ids) {
        for(auto& cadenas : nonterminal.GetProducciones()) {
          for(auto& symbol : cadenas) {
            if(symbol == simbolo) {
              reemplazo.push_back(nonterminal.GetIdentificador());
            }
          }
        }
      }
    }
    else {
      reemplazo.push_back(simbolo);
    }
  }
  return reemplazo;
}

/// @brief Sigue desde el paso diez a adelante en el algoritmo de CNF 
/// @param identificador_primero identificador del no terminal: A → B1B2
/// @param produccion la produccion del no terminal: A → B1B2
void Gramatica::PasoDiezCNF(char identificador_primero, std::vector<char> produccion) {
  Gramatica gramatica_auxiliar;
  gramatica_auxiliar.SetAlfabeto(this->GetAlfabeto());
  gramatica_auxiliar.SetNoTerminales(this->GetNoTerminales());
  // Guardamos los siguientes ids de los no terminales que necesitaremos
  std::vector<char> nonterminales_aux;
  int limite = produccion.size() - 2;
  // 10: Add m − 2 non-terminal symbols D1D2 . . . Dm−2;
  for(int i = 0; i < limite; i++) {
    NoTerminal aux;
    aux.SetIdentificador(gramatica_auxiliar.GenerarIdentificador());
    nonterminales_aux.push_back(aux.GetIdentificador());
    gramatica_auxiliar.AgregarNoTerminal(aux);
  }
  int contador = 0;
  int size = produccion.size();
  for(int i = 0; i < size; i++) {
    NoTerminal no_terminal;
    std::vector<char> producciones_nuevas;
    if(i == 0) {
      no_terminal.SetIdentificador(identificador_primero);
      producciones_nuevas.push_back(produccion[i]);
      producciones_nuevas.push_back(nonterminales_aux[contador]);
      no_terminal.AgregarProduccion(producciones_nuevas);
      this->AgregarNoTerminal(no_terminal);
      // 11: Replace the production A → B1B2 . . . Bm with productions:
      this->ReemplazarProduccion(produccion, producciones_nuevas, identificador_primero);
    }
    if((i > 0) && (i < size - 2)) {
      // 12: A → B1D1
      // 13: D1 → B2D2
      // 14: . . .
      // 15: Dm−2 → Bm−1Bm
      no_terminal.SetIdentificador(nonterminales_aux[contador]);
      contador++;
      producciones_nuevas.push_back(produccion[i]);
      producciones_nuevas.push_back(nonterminales_aux[contador]);
      no_terminal.AgregarProduccion(producciones_nuevas);
      this->AgregarNoTerminal(no_terminal);
    }
    if(i == (size - 2)) {
      no_terminal.SetIdentificador(nonterminales_aux[contador]);
      producciones_nuevas.push_back(produccion[i]);
      producciones_nuevas.push_back(produccion[i + 1]);
      no_terminal.AgregarProduccion(producciones_nuevas);
      this->AgregarNoTerminal(no_terminal);
    }
  }
}




/// @brief Transforma una gramática CFG (Context Free Grammar) en su forma CNF
/// @return La gramática en la forma normal de Chomsky (CNF) 
Gramatica Gramatica::CFG2CNF() {
  Gramatica gramatica_nueva;
  gramatica_nueva.SetAlfabeto(this->GetAlfabeto());
  char identificador;
  std::vector<NoTerminal> nuevos_ids;
  std::set<char> viejos_ids;
  // ALGORITMO DE CFG --> CNF
  // 1: for all (A → X1X2 . . . Xn (con n ≥ 2, Xi ∈ (Σ ∪ V )) do
  for(auto& nonterminales : this->GetNoTerminales()) {
    NoTerminal no_terminal;
    for(auto& producciones : nonterminales.GetProducciones()) {
      // Se guardan las producciones que no cumplan con ese n ≥ 2 en otra gramática
      if(producciones.size() < 2) {
        gramatica_nueva.GuardarProduccionOrdenada(nonterminales, producciones);
      }
      if(producciones.size() >= 2) {
        // 2: for all (Xi) do
        for(auto& simbolo : producciones) {
          // 3: if (Xi = a ∈ Σ) then
          if(this->GetAlfabeto().GetSimbolos().count(simbolo) == 1) {
            // 4: Add the production Ca → a;
            // Si no lo hemos almacenado aún, hacemos todo el proceso
            if(viejos_ids.count(simbolo) == 0) {
              NoTerminal no_terminal;
              identificador = this->GenerarIdentificador();
              viejos_ids.insert(simbolo);
              no_terminal.SetIdentificador(identificador);
              this->AgregarNoTerminal(no_terminal);
              std::vector<char> produccion;
              produccion.push_back(simbolo);
              no_terminal.AgregarProduccion(produccion);
              gramatica_nueva.AgregarNoTerminal(no_terminal);
              nuevos_ids.push_back(no_terminal);
            }
            // 5: Replace Xi with Ca in A → X1X2 . . . Xn;
          }
          // 6: end if 
        }
        std::vector<char> produccion_reemplazo = gramatica_nueva.ReemplazarTerminales(producciones, nuevos_ids);
        gramatica_nueva.GuardarProduccionOrdenada(nonterminales, produccion_reemplazo);
        // 7: end for
      }
    }
    // 8: end for
  }
  // 9: for all (A → B1B2 . . . Bm (con m ≥ 3, Bi ∈ V ) do
  for(auto& nonterminales : gramatica_nueva.GetNoTerminales()) {
    for(auto& producciones : nonterminales.GetProducciones()) {
      int contador_no_terminales = 0;
      if(producciones.size() >= 3) {  
        std::set<char> nonterm;
        for(auto& symbol : producciones) {
          if(gramatica_nueva.GetAlfabeto().GetSimbolos().count(symbol) == 0) {
            if(nonterm.count(symbol) == 0) {
              contador_no_terminales++;
            }
            nonterm.insert(symbol);
          }
        }
        // 10: Add m − 2 non-terminal symbols D1D2 . . . Dm−2;
        // 11: Replace the production A → B1B2 . . . Bm with productions:
        // 12: A → B1D1
        // 13: D1 → B2D2
        // 14: . . .
        // 15: Dm−2 → Bm−1Bm
        gramatica_nueva.PasoDiezCNF(nonterminales.GetIdentificador(), producciones);
      }
    }
  }
  // 16: end for
  return gramatica_nueva;
}

void Gramatica::Imprimir(std::string archivo_salida) {
  std::ofstream salida(archivo_salida);
  // Salida alfabeto
  salida << "Alfabeto:\n";
  for(auto& simbolo : this->GetAlfabeto().GetSimbolos()) {
    salida << simbolo << " ";
  }
  salida << "\n";
  // Salida No terminales
  salida << "\nNo terminales:\n";
  for(auto& no_terminales : this->GetNoTerminales()) {
    salida << no_terminales.GetIdentificador() << " ";
  }
  salida << "\n";
  // Salida producciones
  salida << "\nProducciones:\n";
  for(auto& no_terminales : this->GetNoTerminales()) {
    for(auto& cadena : no_terminales.GetProducciones()) {
      salida << no_terminales.GetIdentificador() << " --> ";
      for(auto& simbolo : cadena) {
        salida << simbolo;
      }
      salida << "\n";
    }
  }
  salida << "\n";
}

void ComprobarErrores(std::string entrada) {
  std::fstream archivo(entrada);
  std::string linea;
  int contador = 0;
  int cardinalidad;
  int cantidad_nonterminales;
  std::set<std::string> alfabeto;
  std::set<std::string> nonterminales;
  int cantidad_producciones;
  std::vector<std::string> producciones;
  std::vector<std::string> identificadores_producciones;
  while(getline(archivo, linea)) {
    if(contador == 0) {
      cardinalidad = stoi(linea);
    }
    if((contador > 0) && (contador <= cardinalidad)) {
      if(linea.size() != 1) {
        std::cout << "No se permiten terminales de más de un símbolo --> " << linea << "\n";
        std::cout << "Línea: " << contador + 1 << std::endl;
        assert(0);
      }
      alfabeto.insert(linea);
    }
    if(contador == (cardinalidad + 1)) {
      cantidad_nonterminales = stoi(linea);
    }
    if((contador > (cardinalidad + 1)) && (contador < (cardinalidad + 2 + cantidad_nonterminales))) {
      if(linea.size() != 1) {
        std::cout << "No se permiten no terminales de más de un símbolo --> " << linea << "\n";
        std::cout << "Línea: " << contador + 1 << std::endl; 
        assert(0);
      }
      nonterminales.insert(linea);
      for(auto& simbolo : alfabeto) {
        if(simbolo == linea) {
          std::cout << "No se permiten usar el mismo símbolo para terminal y no terminal --> " << linea << "\n";
          std::cout << "Línea: " << contador + 1 << std::endl;
          assert(0);
        }
      }
    }
    if(contador == (cardinalidad + 2 + cantidad_nonterminales)) {
      cantidad_producciones = stoi(linea);
    }
    if(contador > (cardinalidad + 2 + cantidad_nonterminales)) {
      producciones.push_back(linea);
      int counter = 0;
      for(auto& id : linea) {
        if(counter == 0) {
          std::string identifier(1, id);
          identificadores_producciones.push_back(identifier);
        }
        counter++;
      }
    }
    contador++;
  }

  int size = producciones.size();
  if(size != cantidad_producciones) {
    std::cout << "El número indicado de producciones no concuerda con el recibido.\n";
    std::cout << "Número indicado de líneas: " << cantidad_producciones << std::endl;
    std::cout << "Número recibido de líneas: " << size << std::endl;
    assert(0);
  }
  for(auto& ids : identificadores_producciones) {
    if(nonterminales.count(ids) == 0) {
      std::cout << "El no terminal '" << ids << "' no se encuentra en la lista de no terminales.\n";
      assert(0);
    }
  }
}

/// @brief 
void Gramatica::IsRightLinear() {
  bool lineal_derecha = true;
  for(auto& nonterminales : this->GetNoTerminales()) {
    for(auto& producciones : nonterminales.GetProducciones()) {
      if(this->GetAlfabeto().GetSimbolos().count(producciones[0]) == 1) {
        if(this->GetAlfabeto().GetSimbolos().count(producciones[producciones.size()]) == 0) {
        }
        else {
          lineal_derecha = false;
        }
      }
      else {
        lineal_derecha = false;
      }
    }
  }
  if(lineal_derecha) {
    std::cout << "This grammar is right-linear.\n";
  }
  else {
    std::cout << "This grammar is not right-linear.\n";
  }
}