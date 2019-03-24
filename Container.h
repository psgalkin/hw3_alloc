#pragma once

#include <iostream>

#include "Map_allocator.h"

template<typename Alloc>
class My_Cont {
private:
	My_Cont* next;
	My_Cont* first;
	My_Cont* last;
	Map_allocator<My_Cont, Alloc::nSize> alloc;
	int size;
	void set_new_last(My_Cont* cont, My_Cont* newLast);
public:
	template<typename U>
	My_Cont(U al) : next(nullptr), first(this), last(this), alloc(al) {}
	
	My_Cont() : val(0), next(nullptr), first(this), last(this), alloc(), size(0) {}
	My_Cont(int i) : val(i), next(nullptr), first(this), last(this), alloc(), size(0) {}
	
	int val;

	void push_back(int i);
	void show() {
		if (next != nullptr) {
			std::cout << val << '\n';
			next->show();
		}
	}
	~My_Cont() {
		alloc.destroy(this);
	};
};

template<typename Alloc>
void My_Cont<Alloc>::set_new_last(My_Cont<Alloc>* cont, My_Cont<Alloc>* newLast)
{
	if (cont == nullptr) { return; }
	else { cont->last = newLast; } 
	set_new_last(cont->next, newLast);
	return;
}

template<typename Alloc>
void My_Cont<Alloc>::push_back(int i)
{
	size++;
	//if (size > alloc.nSize) throw std::exception("Error: oversize\n");
	void* point = alloc.allocate(0);
	
	auto newcont = reinterpret_cast<My_Cont<Alloc>*>(point);
	alloc.construct(newcont, alloc);
	
	newcont->val = i;
	newcont->first = first;
	last->next = newcont;
	set_new_last(this, newcont);
	last = newcont;
}
