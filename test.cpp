
#include <iostream>
#include "src/value.h"

int main() {
  Value Value1 = 1;
  Value Value2 = 2;
  Value Value3 = Value1 + Value2;

  Value3.backward();
  // Value14.printTree();

  std::cout << "Value1: " << Value1.get() << std::endl;
  std::cout << "Value2: " << Value2.get() << std::endl;
  std::cout << "Value3: " << Value3.get() << std::endl;

  // std::cout << "Value8: " << Value8.get() << std::endl;

}
