#pragma once

#include "pretty.h"

#include <iostream>

//#define USE_PRETTY 1

template<typename T, int N>
struct Map_allocator {
	using value_type = T;
	static const int nSize{ N };
	using pointer = T * ;
	using const_pointer = const T*;
	using reference = T & ;
	using const_reference = const T&;

	void* memory;
	int nIt;

	template<typename U>
	struct rebind {

		using other = Map_allocator<U, nSize>;
	};

	Map_allocator() : nIt(0) {
		memory = std::malloc((nSize + 1) * sizeof(T));
	}

	~Map_allocator() {	}

	template<typename U>
	Map_allocator(const Map_allocator<U, nSize>& alloc)
		: memory(alloc.memory), nIt(alloc.nIt + 1) {
	}

	T *allocate(std::size_t n) {

	#ifndef USE_PRETTY
		
	#else
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
	#endif
		nIt++;
		return &(reinterpret_cast<T *>(memory)[nIt - 1]);
	}

	void deallocate(T *p, std::size_t n) {
	
	}

	template<typename U, typename ...Args>
	void construct(U *p, Args &&...args) {
	#ifndef USE_PRETTY
		
	#else
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
		new(p) U(std::forward<Args>(args)...);
	}

	void destroy(T *p) {
#ifndef USE_PRETTY
		
#else
		std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
		std::free(memory);
	}
};
