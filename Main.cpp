#include <string> 
#include <iostream>
#include <vector>
#include "dual_ascent.hpp"
using namespace std;


int main (){
  
    Dual_ascent dual_ascent("data.txt", 100);
    dual_ascent.readData("data.txt");
    dual_ascent.display_equations();
    dual_ascent.display_the_program();
    dual_ascent.solve_dual_ascent();
}