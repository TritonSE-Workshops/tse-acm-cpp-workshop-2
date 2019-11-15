#ifndef ACMTSE_MY_UNIQUE_PTR_HPP
#define ACMTSE_MY_UNIQUE_PTR_HPP

#include <cstddef>
#include <algorithm>

namespace acmtse {

    // This is the solution! Turn back if you are still working on this!
    template<class T>
    class my_unique_ptr {
        private:
            T* d_data_p;
        public:
            /*
             * Default constructor
             */
            my_unique_ptr();

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
             * Move copy constructor
             */
            my_unique_ptr(my_unique_ptr&& other);

            /*
             * Move assignment operator
             */
            my_unique_ptr& operator=(my_unique_ptr&& other);

            /*
             * We wish to delete the compiler-generated copy constructors
             * and assignment operators because a unique pointer should not
             * be copyable or assignable.
             */
            my_unique_ptr(const my_unique_ptr&) = delete;
            my_unique_ptr& operator=(const my_unique_ptr& other) = delete;

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
            T& operator*() const;

            /*
             * Releases and returns the underlying raw pointer that this 
             * unique pointer owns. This implies that this unique pointer 
             * will now be effectively null. 
             */
            T* release();
    };

    template <class T>
    inline my_unique_ptr<T>::my_unique_ptr() : d_data_p(nullptr) {
    }

    template <class T>
    inline my_unique_ptr<T>::my_unique_ptr(T* data) : d_data_p(data) {
    }

    template <class T>
    inline my_unique_ptr<T>::~my_unique_ptr() {
        delete d_data_p;
    }

    template <class T>
    inline my_unique_ptr<T>::my_unique_ptr(my_unique_ptr&& other) : d_data_p(other.d_data_p) {
        other.d_data_p = nullptr;
    }

    template <class T>
    inline my_unique_ptr<T>& my_unique_ptr<T>::operator=(my_unique_ptr&& other) {
        d_data_p = other.d_data_p;
        other.d_data_p = nullptr;
        return *this;
    }

    template <class T>
    inline T* my_unique_ptr<T>::operator->() const {
        return d_data_p;
    }

    template <class T>
    inline T& my_unique_ptr<T>::operator*() const {
        return *d_data_p;
    }

    template <class T>
    inline T* my_unique_ptr<T>::release() {
        T* result = d_data_p;
        d_data_p = nullptr;
        return result;
    }

    template <class T>
    inline T* my_unique_ptr<T>::get() const {
        return d_data_p;
    }
}

#endif
