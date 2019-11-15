#include "catch.hpp"

#include <my_unique_ptr.hpp>

#include <string>
#include <thread>

using namespace acmtse;

TEST_CASE("Constructor stores pointer correctly") {
    int* data = new int(5);
    my_unique_ptr<int> ptr(data);  
    REQUIRE(data == ptr.get());
}

TEST_CASE("Deferencing returns correct value") {
    my_unique_ptr<int> ptr(new int(5));  
    REQUIRE(*ptr == 5);
    REQUIRE(*ptr == *ptr.get());
}

TEST_CASE("Arrow operator works correctly") {
    my_unique_ptr<std::string> ptr(new std::string("acmtse"));  
    REQUIRE(*ptr == "acmtse");
    REQUIRE(ptr->length() == 6);
}

TEST_CASE("Modifications through arrow operator work correctly") {
    my_unique_ptr<std::string> ptr(new std::string("acmtse"));  
    ptr->push_back('1');
    REQUIRE(*ptr == "acmtse1");
    REQUIRE(ptr->length() == 7);
}

TEST_CASE("Assignment through rvalue works correctly") {
    my_unique_ptr<std::string> ptr1;
    my_unique_ptr<std::string> ptr2;
    ptr1 = my_unique_ptr<std::string>(new std::string("acmtse"));
    ptr1->push_back('1');
    ptr2 = std::move(ptr1);
    ptr2->push_back('2');
    REQUIRE(*ptr2 == "acmtse12");
    REQUIRE(ptr2->length() == 8);
}

TEST_CASE("Release gives up raw pointer ownership") {
    int* data = new int(5);
    my_unique_ptr<int> ptr(data);  
    REQUIRE(data == ptr.release());
    REQUIRE(ptr.get() == nullptr);
    delete data;
}

TEST_CASE("No race conditions in unique pointer") {
    const size_t trials = 1000;
    const size_t amax = 100;
    const size_t bmax = 100;
    for (size_t trial = 0; trial < trials; trial++) {
        my_unique_ptr<std::string> miracle(new std::string());
        std::thread frst([&miracle]() {
            for (int i = 0; i < amax; i++) {
                miracle->push_back('a');
            }
        });
        std::thread snd([&miracle]() {
            for (int i = 0; i < bmax; i++) {
                miracle->push_back('b');
            }
        });
        frst.join();
        snd.join();
        REQUIRE(miracle->size() == amax + bmax);
        size_t acnt = 0;
        size_t bcnt = 0;
        for (auto & c : *miracle) {
            if (c == 'a') {
                acnt++;
            }
            else if (c == 'b') {
                bcnt++;
            }
            else {
                REQUIRE(false);
            }
        }
        REQUIRE(acnt == amax);
        REQUIRE(bcnt == bmax);
    }
}
