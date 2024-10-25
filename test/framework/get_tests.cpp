#include "test_class.cpp"
// #include "../logger.cpp"

/**
 * This function gets the tests that have to be executed.
 * All the tests need to be declared here.
 * @return the test classes that will be executed
 */
std::vector<Test*> getTests() {
    std::vector<Test*> tests;
    tests.push_back(new UnitTest());
    // tests.push_back(new LoggerTest());
    return tests;
}