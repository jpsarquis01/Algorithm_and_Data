#pragma once

#include <cstddef>

template<typename T, std::size_t N>
class Array
{
public:
	// Base Constructor,called by default
	Array()
	{
		// Allocates memory 
		// Size required is size of T type object
		// Time the number of items N
		mValues = new T[N];
	}

	// Constructor Overload
	Array(T initValue)
	{
		mValues = new T[N];
		for (std::size_t i = 0; i < N; ++i)
		{
			mValues[i] = initValue;
			                                      
		}
	}

	// Destructor when destroied
	~Array()
	{
		delete[] mValues;
		//mValues = nullptr;
	}

	// Gets the number of elements in the array
	std::size_t Size()
	{
		//int size = sizeof(this) / sizeof(T);
		return N;
	}

	// Gets data stored in the array
	T* Data()
	{
		return mValues;
	}

	// Const version
	const T* Data() const
	{
		return mValues;
	}

	// Operator overloads to access data
	T& operator[](std::size_t index)
	{
		// Can add some data to catch out of bounds
		// eg: assert, throw/catch
		return mValues[index];
	}

	//const version
	const T& operator[](std::size_t index) const
	{
		return mValues[index];
	}

private:
	T* mValues;

};