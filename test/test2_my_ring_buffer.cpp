#include "catch.hpp"

#include <my_ring_buffer.hpp>

#include <string>
#include <thread>
#include <unordered_set>
#include <vector>
#include <iostream>

using namespace acmtse;

constexpr int TRIALS = 250; 

TEST_CASE("Two producers, filling buffer to maximum") {
    for (size_t trial = 0; trial < TRIALS; trial++) {
        my_ring_buffer<int, 100> buf;
        std::thread prod1([&buf]() {
            for (int i = 0; i < 50; i++) {
                REQUIRE(buf.size() < buf.capacity());
                buf.push_back(i); 
            }
        });
        std::thread prod2([&buf]() {
            for (int i = 0; i < 50; i++) {
                REQUIRE(buf.size() < buf.capacity());
                buf.push_back(i); 
            }
        });
        prod1.join();
        prod2.join();
        REQUIRE(buf.size() == buf.capacity());
        std::vector<int> counts(50, 0);
        while (buf.size() > 0) {
            counts[buf.front()]++;
            buf.pop_front();
        }
        for (int i = 0; i < 50; i++) {
            REQUIRE(counts[i] == 2);
        }
    }
}

TEST_CASE("Two producers, filling buffer with overflow") {
    for (size_t trial = 0; trial < TRIALS; trial++) {
        my_ring_buffer<int, 100> buf;
        std::thread prod1([&buf]() {
            for (int i = 0; i < 100; i++) {
                try {
                    buf.push_back(i); 
                } catch (std::out_of_range& _) {
                    break;
                }
            }
        });
        std::thread prod2([&buf]() {
            for (int i = 0; i < 100; i++) {
                try {
                    buf.push_back(i); 
                } catch (std::out_of_range& _) {
                    break;
                }
            }
        });
        prod1.join();
        prod2.join();
        REQUIRE(buf.size() == buf.capacity());
    }
}

TEST_CASE("Two consumers, emptying buffer completely") {
    for (size_t trial = 0; trial < TRIALS; trial++) {
        my_ring_buffer<int, 100> buf;
        for (size_t i = 0; i < 100; i++) {
            buf.push_back(i);
        }
        std::thread cmsr1([&buf]() {
            for (int i = 0; i < 50; i++) {
                REQUIRE(buf.size() > 0);
                buf.pop_front(); 
            }
        });
        std::thread cmsr2([&buf]() {
            for (int i = 0; i < 50; i++) {
                REQUIRE(buf.size() > 0);
                buf.pop_front(); 
            }
        });
        cmsr1.join();
        cmsr2.join();
        REQUIRE(buf.size() == 0);
        try {
            buf.pop_front();
            REQUIRE(false);
        } catch (std::out_of_range& _) {
            REQUIRE(true);
        }
    }
}

TEST_CASE("Two consumers, emptying buffer with overflow") {
    for (size_t trial = 0; trial < TRIALS; trial++) {
        my_ring_buffer<int, 100> buf;
        for (size_t i = 0; i < 100; i++) {
            buf.push_back(i);
        }
        std::thread cmsr1([&buf]() {
            for (int i = 0; i < 100; i++) {
                try {
                    buf.pop_front(); 
                } catch (std::out_of_range& _) {
                    break;
                }
            }
        });
        std::thread cmsr2([&buf]() {
            for (int i = 0; i < 100; i++) {
                try {
                    buf.pop_front(); 
                } catch (std::out_of_range& _) {
                    break;
                }
            }
        });
        cmsr1.join();
        cmsr2.join();
        REQUIRE(buf.size() == 0);
    }
}

TEST_CASE("One consumer, one producer") {
    for (size_t trial = 0; trial < TRIALS; trial++) {
        my_ring_buffer<int, 100> buf;
        std::unordered_set<int> unused;
        for (size_t i = 0; i < 200; i++) {
            unused.insert(i);
        }
        std::thread prod([&buf]() {
            for (size_t i = 0; i < 200; i++) {
                try {
                    buf.push_back(i);
                } catch (std::out_of_range& _) {
                    i--;
                }
            }
        });
        std::thread cmsr([&buf, &unused]() {
            size_t popped = 0;
            while (popped < 100) {
                try {
                    int frnt = buf.pop_front();
                    REQUIRE(unused.find(frnt) != unused.end());
                    unused.erase(frnt);
                    popped++;
                } catch (std::out_of_range& _) {
                }
            }
        });
        prod.join();
        cmsr.join();
        REQUIRE(buf.size() == buf.capacity());
        REQUIRE(buf.size() == unused.size());
        while (buf.size() > 0) {
            REQUIRE(unused.find(buf.front()) != unused.end());
            unused.erase(buf.front());
            buf.pop_front();
        }
    }
}
