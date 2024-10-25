#include "test_interface.hpp"
#include <functional>
#include "get_tests.cpp"

void testExecutor(Test* test) {
  // execute the before each block
  test->beforeAll();

  std::vector<std::function<void (Test*)>> testFunctions = test->getTests();

  for (auto& testFunction : testFunctions){
    test->beforeEach();
    testFunction(test);
    test->afterEach();
  }
  test->afterAll();
}

void executeTests(std::vector<Test*> tests) {
  for (auto& test : tests) {
    testExecutor(test);
  }
}


int main() {
  auto tests = getTests();
  executeTests(tests);
}