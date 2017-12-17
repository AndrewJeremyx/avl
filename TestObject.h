#ifndef SECOND_LABA_TESTOBJECT_H
#define SECOND_LABA_TESTOBJECT_H
#include <string>
#include <iostream>
#include <vector>
class TestObject {
private:
    unsigned int countOfTests_;
    unsigned int countOfTrueTests_;
public:
    TestObject() : countOfTrueTests_(0), countOfTests_(0) {}
    template <class R, class L>
    void Compare(L l, std::string cmp, R r, std::string str) {
        ++countOfTests_;
        std::cout << "    ---SUBTEST" << countOfTests_ << "---" << std::endl;
        std::cout << "    " << str << std::endl;
        bool condition;
        if (cmp == "eq"){
            condition = (l == r);
        }
        else if (cmp == "ne") {
            condition = (l != r);
        }
        else {
            throw std::invalid_argument("bad compare op");
        }
        if (condition) {
            ++countOfTrueTests_;
            std::cout << "    ---OK---" << std::endl;
            std::cout << std::endl;
        } else {
            std::cout << "    ---NOT OK---" << std::endl;
            std::cout << std::endl;
        }
    }
    void Print(std::string str) {
        std::cout <<"---" << str << "---" << std::endl;
        std::cout << std::endl;
    }
    bool Result() {
        std::cout <<"---RESULT OF SUBTESTS---" << std::endl;
        std::cout << countOfTrueTests_ << " / " << countOfTests_ << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        return (countOfTests_ == countOfTrueTests_) ? 1 : 0;
    }
};

void test_starter(std::vector< bool (*)() > vec ) {
    auto count = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it ) {
        count += (*it)();
    }
    std::cout <<"---RESULT OF TESTS---" << std::endl;
    std::cout << count << " / " << vec.size() << std::endl;
};
#endif
