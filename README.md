# C++ Joint Workshop 1 

**A joint collaboration between ACM and TSE.**

In this workshop, we will cover how a vector (aka
a dynamically resizeable array) might be implemented. 
Concepts such as the Rule of 3/5 will be integrated
into the implementation. 

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

The vector implementation can be found in the file **include/my_vector.hpp**.
It is header-only (there are no corresponding source files). Your job
is to fill in the TODOs found in the incomplete vector functions. At
the end, running `./tests` from the build directory should result in
everything passing.

The `solution` branch contains a working implementation. Ideally, you
should first implement as much as possible on your own and then
refer to the solution if you get stuck or if you wish to compare answers.
