#pragma once

#include <cstddef>

template<typename T, std::size_t N>
class Array
{
public:
    // base constructor, called by default
    Array()
    {
        // allocate memory 
        // size required is size of T type object
        //      times the number of items N
        mValues = new T[N];
    }
    // constructor overload
    Array(T initValue)
    {
        mValues = new T[N];
        for (std::size_t i = 0; i < N; ++i)
        {
            mValues[i] = initValue;
        }
    }
    // destructor when destroyed
    ~Array()
    {
        delete[] mValues;
        mValues = nullptr;
    }

    Array(const Array<T, N>& cpy)
    {
        mValues = new T[N];
        for (int i = 0; i < N; ++i)
        {
            mValues[i] = cpy.mValues[i];
        }
    }

    Array(Array<T, N>&& cpy)
    {
        mValues = new T[N];
        for (int i = 0; i < N; ++i)
        {
            mValues[i] = std::move(cpy.mValues[i]);
        }
        delete[] cpy.mValues;
        cpy.mValues = nullptr;
    }

    Array& operator=(const Array<T, N>& cpy)
    {
        mValues = new T[N];
        for (int i = 0; i < N; ++i)
        {
            mValues[i] = cpy.mValues[i];
        }
        return *this;
    }
    Array& operator=(Array<T, N>&& cpy)
    {
        mValues = new T[N];
        for (int i = 0; i < N; ++i)
        {
            mValues[i] = std::move(cpy.mValues[i]);
        }
        delete[] cpy.mValues;
        cpy.mValues = nullptr;

        return *this;
    }

    // gets the number of elements in the array
    const std::size_t Size() const
    {
        return N;
    }
    // gets the data stored in the array
    T* Data()
    {
        return mValues;
    }
    // const version
    const T* Data() const
    {
        return mValues;
    }

    // operator overloads to access data
    T& operator[](std::size_t index)
    {
        // can add custom data to catch out of bounds
        // eg: assert, throw/catch
        return mValues[index];
    }
    // const version
    const T& operator[](std::size_t index) const
    {
        return mValues[index];
    }

private:
    T* mValues = nullptr;
};