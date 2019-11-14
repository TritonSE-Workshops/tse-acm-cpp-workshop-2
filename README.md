# C++ Joint Workshop 2 

**A joint collaboration between ACM and TSE.**

In this workshop, we will cover how a thread-safe 
unique pointer might be implemented using modern
C++ techniques.

## Setup

Clone this repository and `cd` into the top level directory.

Perform an out-of-source cmake build by running
```
mkdir build && cd build
cmake ..
make
```

Now try running the vector tests by using

```
./tests
```

from inside the build directory. Everything should fail at first.

## Your Task

The unique pointer implementation can be found in the file **include/my_unique_ptr.hpp**.
It is header-only. Function implementations are found at the bottom. Your job
is to fill in the TODOs found in the incomplete vector functions. At
the end, running `./tests` from the build directory should result in
everything passing.

---

The TODOs represent everything that you should be doing! 
There is no need to change anything that is not tagged with a TODO!

---

The `solution` branch contains a working implementation. Ideally, you
should first implement as much as possible on your own and then
refer to the solution if you get stuck or if you wish to compare answers.
