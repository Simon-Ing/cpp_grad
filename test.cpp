
#include <iostream>
#include "src/value.h"

int main() {
  Value x(2);
  x.set_tag("x");
  Value w1(3);
  w1.set_tag("w1");
  Value b1(4);
  b1.set_tag("b1");
  Value z = x * w1 + b1;
  z.set_tag("z");
  Value y = z * z;
  y.set_tag("y");

  y.backward();
  std::cout << "x = 2 = " << x.get() << std::endl;
  std::cout << "w1 = 3 = " << w1.get() << std::endl;
  std::cout << "b1 = 4 = " << b1.get() << std::endl;
  std::cout << "z = x * w1 + b1 = 10 = " << z.get() << std::endl;
  std::cout << "y = z * z = 100 = " << y.get() << std::endl;
  return 0;
}
