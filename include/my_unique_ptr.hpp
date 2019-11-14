#ifndef ACMTSE_MY_UNIQUE_PTR_HPP
#define ACMTSE_MY_UNIQUE_PTR_HPP

#include <cstddef>
#include <algorithm>
#include <mutex>

namespace acmtse {

    // Make this work by implementing everything labeled with TODO!
    template<class T>
    class my_unique_ptr {
        private:
            T* d_data_p;
            std::mutex d_mtx;
        public:
            /*
             * Default constructor
             */
            my_unique_ptr() = default; // TODO: Add something here ...

            /*
             * Explicit constructor, takes in a raw pointer that the
             * unique pointer will manage. 
             *
             * This action represents a
             * transfer of control from the raw pointer's original
             * owner to the unique pointer.
             */
            explicit my_unique_ptr(T* data);

            /*
             * Destructor. Keep in mind that the unique pointer owns
             * its raw pointer so it is free to delete it.
             */
            ~my_unique_ptr();

            /*
             * Assignment operator (note: rvalue usage).
             */
            my_unique_ptr& operator=(my_unique_ptr&& other) noexcept;

            /*
             * We wish to delete the compiler-generated copy constructors
             * and assignment operators because a unique pointer should not
             * be copyable or assignable.
             */
            my_unique_ptr(const my_unique_ptr&) = delete; // TODO: Add something here ... 
            my_unique_ptr& operator=(const my_unique_ptr& other) = delete; // TODO: Add something here ... 

            /*
             * Returns the underlying raw pointer. Already implemented. 
             */
            T* get() const;
 
            /*
             * Arrow operator, equivalent to dereferencing an object and accessing it.
             */
            T* operator->() const;

            /*
             * Deference operator.
             */
            T& operator*()  const;

            /*
             * Releases and returns the underlying raw pointer that this 
             * unique pointer owns. This implies that this unique pointer 
             * will now be effectively null. 
             */
            T* release();
    };

    template <class T>
    inline my_unique_ptr<T>::my_unique_ptr(T* data) {
        // TODO: Add implementation of explicit constructor
    }

    template <class T>
    inline my_unique_ptr<T>::~my_unique_ptr() {
        // TODO: Add implementation of destructor
    }

    template <class T>
    inline my_unique_ptr<T>& my_unique_ptr<T>::operator=(my_unique_ptr&& other) noexcept {
        // TODO: Add implementation of rvalue assignment operator 
    }

    template <class T>
    inline T* my_unique_ptr<T>::operator->() const {
        // TODO: Add implementation of arrow operator
    }

    template <class T>
    inline T& my_unique_ptr<T>::operator*() const {
        // TODO: Add implementation of dereference operator 
    }

    template <class T>
    inline T* my_unique_ptr<T>::release() {
        // TODO: Add implementation of release
    }

    template <class T>
    inline T* my_unique_ptr<T>::get() const {
        return d_data_p;
    }
}

#endif
