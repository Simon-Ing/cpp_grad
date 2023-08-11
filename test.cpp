
#include <iostream>
#include "src/value.h"

int main() {
  Value Value0 = 2;
  Value Value1 = 3;
  Value Value2 = 4;
  Value Value3 = 5;
  Value Value4 = 6;
  Value Value5 = 7;
  Value Value6 = 8;
  Value Value7 = 9;
  Value Value8 = Value0 + Value1;
  Value Value9 = Value2 + Value3;
  Value Value10 = Value4 + Value5;
  Value Value11 = Value6 + Value7;
  Value Value12 = Value8 * Value9;
  Value Value13 = Value10 + Value11;
  Value Value14 = Value12 * Value13;

  Value14.backward();
  // Value14.printTree();

  std::cout << "Value0: " << Value0.get() << std::endl;
  std::cout << "Value1: " << Value1.get() << std::endl;
  std::cout << "Value2: " << Value2.get() << std::endl;
  std::cout << "Value3: " << Value3.get() << std::endl;
  std::cout << "Value4: " << Value4.get() << std::endl;
  std::cout << "Value5: " << Value5.get() << std::endl;
  std::cout << "Value6: " << Value6.get() << std::endl;
  std::cout << "Value7: " << Value7.get() << std::endl;
  std::cout << "Value8: " << Value8.get() << std::endl;
  std::cout << "Value9: " << Value9.get() << std::endl;
  std::cout << "Value10: " << Value10.get() << std::endl;
  std::cout << "Value11: " << Value11.get() << std::endl;
  std::cout << "Value12: " << Value12.get() << std::endl;
  std::cout << "Value13: " << Value13.get() << std::endl;
  std::cout << "Value14: " << Value14.get() << std::endl;




}
