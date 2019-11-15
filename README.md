# C++ Joint Workshop 2 

**A joint collaboration between ACM and TSE.**

In this workshop, we will cover how a
unique pointer might be implemented using modern
C++ techniques. We will also go over threading
and thread-safety in C++ via a circular buffer example.

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

## Part 1

The unique pointer implementation can be found in the file **include/my_unique_ptr.hpp**.
It is header-only. Function implementations are found at the bottom. Your job
is to fill in the TODOs found in the incomplete vector functions. At
the end, running `./tests` from the build directory should result in
everything passing.

---

The TODOs represent everything that you should be doing! 
There is no need to change anything that is not tagged with a TODO!

---

## Part 2

A ring buffer is a data structure that treats a sequential array
as if its last slot were connected to its first. We can
use it to implement a fixed-size queue (e.g a FIFO queue that
holds maximally N elements), using two integer pointers to track 
the head and tail elements of the queue.

We already provide a working implementation of this data structure.
It will be your job to make it thread-safe using the appropriate
mutex and locking calls.

You can find the buffer implementation in the file **include/my_ring_buffer.hpp**.
There are no TODOs this time. You will implement locking for each
function in such a way that it passes all the tests.

## Solution

The `solution` branch contains a working implementation. Ideally, you
should first implement as much as possible on your own and then
refer to the solution if you get stuck or if you wish to compare answers.
