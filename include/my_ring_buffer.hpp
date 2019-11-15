#ifndef ACMTSE_MY_UNIQUE_PTR_HPP
#define ACMTSE_MY_UNIQUE_PTR_HPP

#include <cstddef>
#include <algorithm>
#include <mutex> // Note: this will come in handy!

namespace acmtse {

    // TODO: This class is not thread-safe. Look over what it does and make it thread safe.
    // HINT: All you need are 5 lines in total with 4 of them being identical.
    template<class T, int N>
    class my_ring_buffer {
        private:
            T d_ring_p[N];
            size_t d_head;
            size_t d_tail;
            size_t d_sz;
        public:
            /*
             * Default constructor
             */
            my_ring_buffer();

            /*
             * Assume buffer is non-copyable and non-assignable.
             */
            my_ring_buffer(const my_ring_buffer&) = delete; 
            my_ring_buffer& operator=(const my_ring_buffer&) = delete;

            /*
             * Get the head of queue but do not pop it.
             *
             * Throws out-of-range exception if there are no elements in the queue.
             *
             * MUST BE THREAD-SAFE.
             */
            T& front();

            /*
             * Pop (aka remove) the head of the queue.
             *
             * Throws out-of-range exception if there are no elements in the queue.
             *
             * MUST BE THREAD-SAFE.
             */
            T pop_front();

            /*
             * Push element to the back of the queue. It will become the new tail element.
             *
             * Throws out-of-range exception if the queue is full. 
             *
             * MUST BE THREAD-SAFE.
             */
            void push_back(const T& t);

            /*
             * Gets the number of elements in the queue currently.
             *
             * MUST BE THREAD-SAFE.
             */
            size_t size(); 

            /*
             * Returns the maximum number of elements that the queue can support.
             *
             * MUST BE THREAD-SAFE.
             */
            size_t capacity() const;
    };

    template <class T, int N>
    inline my_ring_buffer<T, N>::my_ring_buffer() : d_head(0), d_tail(0), d_sz(0) {
    }

    template <class T, int N>
    inline T& my_ring_buffer<T, N>::front() {
        if (d_sz == 0) {
            throw std::out_of_range("Tried to get front from empty queue");
        }
        return d_ring_p[d_head];
    }

    template <class T, int N>
    inline T my_ring_buffer<T, N>::pop_front() {
        if (d_sz == 0) {
            throw std::out_of_range("Tried to pop from empty queue");
        }
        T t = d_ring_p[d_head];
        d_head = (d_head + 1) % N;
        d_sz--;
        return t;
    }

    template <class T, int N>
    inline void my_ring_buffer<T, N>::push_back(const T& t) {
        if (d_sz == N) {
            throw std::out_of_range("Tried to push to full queue");
        }
        d_ring_p[d_tail] = t;
        d_tail = (d_tail + 1) % N;
        d_sz++;
    }

    template <class T, int N>
    inline size_t my_ring_buffer<T, N>::size() {
        return d_sz; 
    }

    template <class T, int N>
    inline size_t my_ring_buffer<T, N>::capacity() const {
        return N;
    }
}

#endif
