#include <string> 
#include <iostream>
#include <vector>
#include "Dictionnary.hpp"
using namespace std;


int main (){
  HashMap<std::string, int> dictionnary;
  // set some values (from 1 to 10)
  for (int i=1; i<=5; i++) dictionnary.insert(std::to_string(i), i);
  dictionnary.insert("x2",20);
  dictionnary.insert("x3",30);

std::cout << "Display key values after insertion:" << std::endl;
dictionnary.dictionnary_diplay_key_value();
dictionnary.delete_key("1");
dictionnary.delete_key("x3");
std::cout << "Display key values after deletion of key '1':" << std::endl;
dictionnary.dictionnary_diplay_key_value();
}