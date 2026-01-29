#pragma once

#include <algorithm>
#include <iterator>
#include <cstddef>

template<typename T>
class ContainerIterator
{
public:
	// define ids/names for stl use (std::sort, std::find..)
	using iterator_category = std::random_access_iterator_tag;
	// Value type = T
	using value_type = T;
	// different types in the iterator may find
	using difference_type = std::ptrdiff_t;
	// points to the value type T
	using pointer = T*;
	// stores value T data
	using reference = T&;

public:
	ContainerIterator(T* ptr) : mPtr(ptr) {}
	// data operator we return the address of the pointer
	T& operator*() const { return *mPtr; }
	// pointer operator gets the stored data in the pointer
	T* operator->() const { return mPtr; }

	// ++iter
	ContainerIterator& operator++() { ++mPtr; return *this; }
	// --iter
	ContainerIterator& operator--() { --mPtr; return *this; }
	// iter++
	ContainerIterator& operator++(int) { ContainerIterator tmp = *this; ++(this); return *this; }
	// iter--
	ContainerIterator& operator--(int) { ContainerIterator tmp = *this; --(this); return *this; }

	ContainerIterator operator+(difference_type n) const { return ContainerIterator(mPtr + n); }
	ContainerIterator operator-(difference_type n) const { return ContainerIterator(mPtr - n); }
	ContainerIterator& operator+=(difference_type n) const { mPtr += n; return *this; }
	ContainerIterator& operator-=(difference_type n) const { mPtr -= n; return *this; }

	difference_type operator-(const ContainerIterator& other) const { return mPtr - other.mPtr; }

	// comparisons
	bool operator==(const ContainerIterator& other) const { return mPtr == other.mPtr; }
	bool operator!=(const ContainerIterator& other) const { return mPtr != other.mPtr; }
	bool operator<(const ContainerIterator& other) const { return mPtr < other.mPtr; }
	bool operator>(const ContainerIterator& other) const { return mPtr > other.mPtr; }
	bool operator>=(const ContainerIterator& other) const { return mPtr >= other.mPtr; }
	bool operator<=(const ContainerIterator& other) const { return mPtr <= other.mPtr; }

private:
	T* mPtr;
};