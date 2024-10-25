#ifndef TEST_INTERFACE_H
#define TEST_INTERFACE_H
#include <vector>
#include <functional>

class Test {

  public:
    virtual void beforeEach() = 0;
    virtual void afterEach() = 0;
    virtual std::vector<std::function<void (Test*)>> getTests() = 0;
    virtual void beforeAll() = 0;
    virtual void afterAll() = 0;
};

#endif