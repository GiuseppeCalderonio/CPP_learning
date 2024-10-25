#include "test_interface.hpp"
#include <functional>
#include <vector>
#include <cassert>
#include <iostream>

class UnitTest : public Test {

public:
    std::vector<std::function<void(Test*)>> getTests() {
        return testFunctions;
    }

    void beforeEach() {
        this->value = 0;
    }

    void afterEach() {
        this->value = 0;
    }

    void beforeAll() {
        this->value = 0;
    }

    void afterAll() {
        this->value = 0;
    }

private:
    int value = 0;

    // Test function implementation
    void test() {
        // Given
        this->value = 1;

        // When
        std::cout << "ciao\n"; 

        // Then
        assert(1 == this->value);
    }

        /** Set of anonymous functions that will contain the tests */
    std::vector<std::function<void(Test*)>> testFunctions = {
        // Use a lambda to capture 'this' and call 'test'
        [this](Test* _) { test(); }
    };
};
