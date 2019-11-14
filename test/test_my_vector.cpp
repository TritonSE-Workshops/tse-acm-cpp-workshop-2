#include "catch.hpp"

#include <my_vector.hpp>

using namespace acmtse;

TEST_CASE("Size constructor returns uninitialized vector") {
    my_vector<int> vec(100);
    REQUIRE(vec.size() == 0);
    REQUIRE(vec.capacity() == 100);
}

TEST_CASE("Copy constructor copies uninitialized vector") {
    my_vector<int> vec(100);
    my_vector<int> cpy(vec);
    REQUIRE(cpy.size() == 0);
    REQUIRE(cpy.capacity() == 100);
}

TEST_CASE("Push back works for pre-allocated vector") {
    my_vector<int> vec(100);
    for (int i = 0; i < 50; i++) {
        vec.push_back(i * 2);
    }
    REQUIRE(vec.size() == 50);
    REQUIRE(vec.capacity() == 100);
    for (int i = 0; i < 50; i++) {
        REQUIRE(vec[i] == i * 2);
    }
}

TEST_CASE("Push back works for vector with small initial capacity") {
    my_vector<int> vec(1);
    for (int i = 0; i < 50; i++) {
        vec.push_back(i * 2);
    }
    REQUIRE(vec.size() == 50);
    REQUIRE(vec.capacity() >= 50);
    for (int i = 0; i < 50; i++) {
        REQUIRE(vec[i] == i * 2);
    }
}

TEST_CASE("Swap works correctly") {
    my_vector<int> vec1(10);
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);
    my_vector<int> vec2(20);
    vec2.push_back(5);
    vec2.push_back(1);
    vec1.swap(vec2);
    REQUIRE(vec1.size() == 2);
    REQUIRE(vec2.size() == 3);
    REQUIRE(vec1.capacity() == 20);
    REQUIRE(vec2.capacity() == 10);
    REQUIRE(vec1[0] == 5);
    REQUIRE(vec1[1] == 1);
    REQUIRE(vec2[0] == 1);
    REQUIRE(vec2[1] == 2);
    REQUIRE(vec2[2] == 3);
}

TEST_CASE("Assignment works correctly") {
    my_vector<int> vec(20);
    for (int i = 0; i < 10; i++) {
        vec.push_back(i * 3);
    }
    auto assigned = vec;
    for (int i = 0; i < 10; i++) {
        REQUIRE(assigned[i] == i * 3);
        REQUIRE(vec[i] == i * 3);
    }
}

TEST_CASE("Trivially empty vector results in no errors") {
    my_vector<int> _(0);
}

TEST_CASE("Stress testing additions and lookups") {
    my_vector<int> vec(0);
    for (int i = 0; i < 10000000; i++) {
        vec.push_back(rand());
    }
    for (int i = 0; i < 3283923; i += 2) {
        vec[i] = vec[i + 1] + vec[i];
    }
    for (int i = 1; i < 3283923; i += 2) {
        vec[i] = vec[i - 1] + vec[i];
    }
}
