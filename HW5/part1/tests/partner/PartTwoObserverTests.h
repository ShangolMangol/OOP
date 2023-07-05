#ifndef OOP5_PARTTWOOBSERVERTESTS_H
#define OOP5_PARTTWOOBSERVERTESTS_H

#include <string>
#include "../../Observer.h"
#include "BaseTestFile.h"

class PartTwoObserverTests {
private:

    class ObsTestInt : public Observer<int> {
    private:
        int test;
    public:
        ObsTestInt() : Observer(), test(0) {

        }

        int getTest() { return test; }

        void handleEvent(const int &msg) override {
            test = msg;
        }
    };

    class ObsTestString : Observer<std::string> {
    private:
        std::string test;
    public:
        ObsTestString() : Observer(), test() {}

        std::string getTest() { return test; }

        void handleEvent(const std::string &msg) override {
            test = msg;
        }
    };

    bool testBasicObserverCreationINT() {
        PRINT_TEST_RUN("testBasicObserverCreationINT");

        ObsTestInt obi;
        obi.handleEvent(4);

        bool result = getEqualTestResult(4, obi.getTest());

        obi.handleEvent(-2);

        result = result && getEqualTestResult(-2, obi.getTest());

        return result;
    }

public:
    void partTwoObserverTests() {
        std::cout << "Running PartTwoObserverTests" << std::endl;
        TestClass *t = new TestClass();

        t->runTest((testBasicObserverCreationINT()));

        std::cout << *t;
        delete t;
    }

};

#endif //OOP5_PARTTWOOBSERVERTESTS_H
