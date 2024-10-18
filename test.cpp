#include <iostream>

int main()
{

  std::string test = "Hello";
  std::string test1 = test.c_str();
  printf("%s\n", test1.c_str());
}