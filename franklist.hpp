#ifndef FRANKLIST_HPP
#define FRANKLIST_HPP

#include "franklist.h"
#include <stdexcept>

namespace vhuk {

template <typename T>
std::ostream& operator<<(std::ostream& out, const FrankList<T>& rhv) {
	for (auto i = rhv.cbegin(); i != rhv.cend(); ++i) {
		out << *i << " ";
	}
		return out;
}

//default and paramteric ctors for node
template<typename T>
FrankList<T>::Node::Node()
	:val(), next(nullptr), prev(nullptr), asc(nullptr), desc(nullptr) {}

template<typename T>
FrankList<T>::Node::Node(T val)
	:val(val), next(nullptr), prev(nullptr), asc(nullptr), desc(nullptr) {}

//base_iterator ctor and dtor : reminder: all nonconst iterators inherits from const iterators and const from base iterator
template<typename T>
FrankList<T>::base_iterator::base_iterator(Node* ptr) 
	:ptr(ptr) {}

template<typename T>
FrankList<T>::base_iterator::~base_iterator() {
	ptr = nullptr;
};


template<typename T>
bool FrankList<T>::base_iterator::operator==(const base_iterator& rhv) const {
	if (ptr == rhv.ptr) {
		return true;
	}
	return false;
}

template<typename T>
bool FrankList<T>::base_iterator::operator!=(const base_iterator& rhv) const {
	if (ptr == rhv.ptr) {
		return false;
	}
	return true;
}

//const_iterator 
//copy ctor
template<typename T> 
FrankList<T>::const_iterator::const_iterator(const base_iterator& rhv) 
	:base_iterator(rhv.ptr) {}

//move ctor
template<typename T>
FrankList<T>::const_iterator::const_iterator(base_iterator&& rhv)
	:base_iterator(rhv.ptr) {
		rhv.ptr = nullptr;
	}

//copy = operator
template<typename T>
const typename FrankList<T>::const_iterator& FrankList<T>::const_iterator::operator=(const base_iterator& rhv) {
	this->ptr = rhv.ptr;
	return *this;
}

//move = operator
template<typename T>
const typename FrankList<T>::const_iterator& FrankList<T>::const_iterator::operator=(base_iterator&& rhv) {
	if (this->ptr != rhv.ptr) {
		this->ptr = rhv.ptr;
		rhv.ptr = nullptr;
	}
	return *this;
}

//* and -> operators 
template<typename T>
typename FrankList<T>::const_reference FrankList<T>::const_iterator::operator*() const {
	return (this->ptr->val);
}

template<typename T>
typename FrankList<T>::const_pointer FrankList<T>::const_iterator::operator->() const {
	return this->ptr;
}

//preincrement 
template<typename T>
const typename FrankList<T>::const_iterator& FrankList<T>::const_iterator::operator++() {
	this->ptr = this->ptr->next;
	return (*this);
}

//postincrement
template<typename T>
const typename FrankList<T>::const_iterator FrankList<T>::const_iterator::operator++(int) {
	const_iterator tmp(*this);
	++(*this);
	return tmp;
}

//predecrement
template<typename T>
const typename FrankList<T>::const_iterator& FrankList<T>::const_iterator::operator--() {
	this->ptr = this->ptr->prev;
	return (*this);
}

//postdecrement
template<typename T>
const typename FrankList<T>::const_iterator FrankList<T>::const_iterator::operator--(int) {
	const_iterator tmp(*this);
	--(*this);
	return tmp;
}

template<typename T>
FrankList<T>::const_iterator::const_iterator(Node* ptr) : base_iterator(ptr) {}

//itertor class (inherits from const_iterator)
//copy ctor
template<typename T>
FrankList<T>::iterator::iterator(const base_iterator& rhv) 
	:const_iterator(rhv.ptr) {}
        
//move ctor
template<typename T>
FrankList<T>::iterator::iterator(base_iterator&& rhv)
	:const_iterator(rhv.ptr) {
		rhv.ptr = nullptr;
	}

//operator *
template<typename T>
typename FrankList<T>::reference FrankList<T>::iterator::operator*() {
	return this->ptr->val;
}

//operator ->
template<typename T>
typename FrankList<T>::pointer FrankList<T>::iterator::operator->() {
	return this->ptr;
}

//copy = operator       
template<typename T>
const typename FrankList<T>::iterator& FrankList<T>::iterator::operator=(const base_iterator& rhv) {
	this->ptr = rhv.ptr;
	return *this;
}
      
//move = operator
template<typename T>
const typename FrankList<T>::iterator& FrankList<T>::iterator::operator=(base_iterator&& rhv) {
	if (this == &rhv) {
		return *this;
	}
	this->ptr = rhv.ptr;
	this->rhv.ptr = nullptr;
	return *this;
}

template<typename T>
FrankList<T>::iterator::iterator(Node* ptr) : const_iterator(ptr) {}

//const_reverse_iterator: base_iterator	
//copy ctor
template<typename T>
FrankList<T>::const_reverse_iterator::const_reverse_iterator(const base_iterator& rhv) 
	:base_iterator(rhv.ptr) {}
        
//move ctor
template<typename T>
FrankList<T>::const_reverse_iterator::const_reverse_iterator(base_iterator&& rhv)
	:base_iterator(rhv.ptr) {
		rhv.ptr = nullptr;
	}
	 
//copy = operator       
template<typename T>
const typename FrankList<T>::const_reverse_iterator& FrankList<T>::const_reverse_iterator::operator=(const base_iterator& rhv) {
	this->ptr = rhv.ptr;
	return *this;
}
      
//move = operator
template<typename T>
const typename FrankList<T>::const_reverse_iterator& FrankList<T>::const_reverse_iterator::operator=(base_iterator&& rhv) {
	if (this == &rhv) {
		return *this;
	}
	this->ptr = rhv.ptr;
	rhv.ptr = nullptr;
	return *this;
}
        
//operator *
template<typename T>
typename FrankList<T>::const_reference FrankList<T>::const_reverse_iterator::operator*() const {
	return this->ptr->val;
}

//operator ->
template<typename T>
typename FrankList<T>::const_pointer FrankList<T>::const_reverse_iterator::operator->() const {
	return this->ptr;
}
        
//preincrement 
template<typename T>
const typename FrankList<T>::const_reverse_iterator& FrankList<T>::const_reverse_iterator::operator++() {
	this->ptr = this->ptr->prev;
	return (*this);
}

//postincrement
template<typename T>
const typename FrankList<T>::const_reverse_iterator FrankList<T>::const_reverse_iterator::operator++(int) {
	const_reverse_iterator tmp(*this);
	--(*this);
	return tmp;
}

//predecrement
template<typename T>
const typename FrankList<T>::const_reverse_iterator& FrankList<T>::const_reverse_iterator::operator--() {
	this->ptr = this->ptr->next;
	return (*this);
}

//postdecrement
template<typename T>
const typename FrankList<T>::const_reverse_iterator FrankList<T>::const_reverse_iterator::operator--(int) {
	const_reverse_iterator tmp(*this);
	++(*this);
	return tmp;
}

template<typename T>
FrankList<T>::const_reverse_iterator::const_reverse_iterator(Node* ptr) : base_iterator(ptr) {}
        
//reverse_iterator :const_reverse_iterator
//copy = operator       
template<typename T>
const typename FrankList<T>::reverse_iterator& FrankList<T>::reverse_iterator::operator=(const base_iterator& rhv) {
	this->ptr = rhv.ptr;
	return *this;
}
      
//move = operator
template<typename T>
const typename FrankList<T>::reverse_iterator& FrankList<T>::reverse_iterator::operator=(base_iterator&& rhv) {
	if (this == &rhv) {
		return *this;
	}
	this->ptr = rhv.ptr;
	rhv.ptr = nullptr;
	return *this;
}       

//operator *
template<typename T>
typename FrankList<T>::reference FrankList<T>::reverse_iterator::operator*()  {
	return this->ptr->val;
}

//operator ->
template<typename T>
typename FrankList<T>::pointer FrankList<T>::reverse_iterator::operator->() {
	return this->ptr;
}

template<typename T>
FrankList<T>::reverse_iterator::reverse_iterator(Node* ptr) : const_reverse_iterator(ptr) {}

//const_asc_iterator : base_iterator
//copy and move ctors
template<typename T>
FrankList<T>::const_asc_iterator::const_asc_iterator(const base_iterator& rhv)
	:base_iterator(rhv.ptr) {}

template<typename T>
FrankList<T>::const_asc_iterator::const_asc_iterator(base_iterator&& rhv)
	:base_iterator(rhv.ptr) {
		rhv.ptr = nullptr;
	}
//copy= and move=
template<typename T>
const typename FrankList<T>::const_asc_iterator& FrankList<T>::const_asc_iterator::operator=(const base_iterator& rhv) {
	this->ptr = rhv.ptr;
	return this;
}

template<typename T>
const typename FrankList<T>::const_asc_iterator& FrankList<T>::const_asc_iterator::const_asc_iterator::operator=(base_iterator&& rhv) {
	if (this == &rhv) {
		return *this;
	}
	this->ptr = rhv.ptr;
	rhv.ptr = nullptr;
	return *this;
}

//* and -> operators
template<typename T>
typename FrankList<T>::const_reference FrankList<T>::const_asc_iterator::operator*() const {
	return this->ptr->val;
}
      
template<typename T>
typename FrankList<T>::const_pointer FrankList<T>::const_asc_iterator::operator->() const {
	return this->ptr;
}   
     
//preincrement 
template<typename T>
const typename FrankList<T>::const_asc_iterator& FrankList<T>::const_asc_iterator::operator++() {
	this->ptr = this->ptr->asc;
	return (*this);
}

//postincrement
template<typename T>
const typename FrankList<T>::const_asc_iterator FrankList<T>::const_asc_iterator::operator++(int) {
	const_asc_iterator tmp(*this);
	++(*this);
	return tmp;
}

//predecrement
template<typename T>
const typename FrankList<T>::const_asc_iterator& FrankList<T>::const_asc_iterator::operator--() {
	this->ptr = this->ptr->desc;
	return (*this);
}

//postdecrement
template<typename T>
const typename FrankList<T>::const_asc_iterator FrankList<T>::const_asc_iterator::operator--(int) {
	const_asc_iterator tmp(*this);
	--(*this);
	return tmp;
}      
     
template<typename T>
FrankList<T>::const_asc_iterator::const_asc_iterator(Node* ptr) : base_iterator(ptr) {}

// class asc_iterator : public const_asc_iterator
template<typename T>
FrankList<T>::asc_iterator::asc_iterator(const base_iterator& rhv) 
	:const_asc_iterator(rhv.ptr) {}

template<typename T>
FrankList<T>::asc_iterator::asc_iterator(base_iterator&& rhv)
	:const_asc_iterator(rhv.ptr) {
		rhv.ptr = nullptr;
	}

//* and -> operators
template<typename T>
typename FrankList<T>::reference FrankList<T>::asc_iterator::operator*() {
	return this->ptr->val;
}
      
template<typename T>
typename FrankList<T>::pointer FrankList<T>::asc_iterator::operator->() {
	return this->ptr;
}   

template<typename T>
const typename FrankList<T>::asc_iterator& FrankList<T>::asc_iterator::operator=(const base_iterator& rhv) {
	this->ptr = rhv.ptr;
	return *this;
}


template<typename T>
const typename FrankList<T>::asc_iterator& FrankList<T>::asc_iterator::operator=(base_iterator&& rhv) {
	if (this == &rhv) {
		return *this;
	}
	this->ptr = rhv.ptr;
	rhv.ptr = nullptr;
	return *this;
}
  
template<typename T>
FrankList<T>::asc_iterator::asc_iterator(Node* ptr) : const_asc_iterator(ptr) {}
   
//const_desc_iterator: base_iterator
//copy and move ctors
template<typename T>
FrankList<T>::const_desc_iterator::const_desc_iterator(const base_iterator& rhv)
	:base_iterator(rhv.ptr) {}

template<typename T>
FrankList<T>::const_desc_iterator::const_desc_iterator(base_iterator&& rhv)
	:base_iterator(rhv.ptr) {
		rhv.ptr = nullptr;
	}
//copy= and move=
template<typename T>
const typename FrankList<T>::const_desc_iterator& FrankList<T>::const_desc_iterator::operator=(const base_iterator& rhv) {
	this->ptr = rhv.ptr;
	return this;
}

template<typename T>
const typename FrankList<T>::const_desc_iterator& FrankList<T>::const_desc_iterator::const_desc_iterator::operator=(base_iterator&& rhv) {
	if (this == &rhv) {
		return *this;
	}
	this->ptr = rhv.ptr;
	rhv.ptr = nullptr;
	return *this;
}

//* and -> operators
template<typename T>
typename FrankList<T>::const_reference FrankList<T>::const_desc_iterator::operator*() const {
	return this->ptr->val;
}
      
template<typename T>
typename FrankList<T>::const_pointer FrankList<T>::const_desc_iterator::operator->() const {
	return this->ptr;
}   
     
//preincrement 
template<typename T>
const typename FrankList<T>::const_desc_iterator& FrankList<T>::const_desc_iterator::operator++() {
	this->ptr = this->ptr->desc;
	return (*this);
}

//postincrement
template<typename T>
const typename FrankList<T>::const_desc_iterator FrankList<T>::const_desc_iterator::operator++(int) {
	const_desc_iterator tmp(*this);
	--(*this);
	return tmp;
}

//predecrement
template<typename T>
const typename FrankList<T>::const_desc_iterator& FrankList<T>::const_desc_iterator::operator--() {
	this->ptr = this->ptr->asc;
	return (*this);
}

//postdecrement
template<typename T>
const typename FrankList<T>::const_desc_iterator FrankList<T>::const_desc_iterator::operator--(int) {
	const_desc_iterator tmp(*this);
	++(*this);
	return tmp;
}      
     
template<typename T>
FrankList<T>::const_desc_iterator::const_desc_iterator(Node* ptr) : base_iterator(ptr) {}

//desc_iterator : const_desc_iterator
template<typename T>
FrankList<T>::desc_iterator::desc_iterator(const base_iterator& rhv) 
	:const_desc_iterator(rhv.ptr) {}

template<typename T>
FrankList<T>::desc_iterator::desc_iterator(base_iterator&& rhv)
	:const_desc_iterator(rhv.ptr) {
		rhv.ptr = nullptr;
	}

//* and -> operators
template<typename T>
typename FrankList<T>::reference FrankList<T>::desc_iterator::operator*() {
	return this->ptr->val;
}
      
template<typename T>
typename FrankList<T>::pointer FrankList<T>::desc_iterator::operator->() {
	return this->ptr;
}   

template<typename T>
const typename FrankList<T>::desc_iterator& FrankList<T>::desc_iterator::operator=(const base_iterator& rhv) {
	this->ptr = rhv.ptr;
	return *this;
}


template<typename T>
const typename FrankList<T>::desc_iterator& FrankList<T>::desc_iterator::operator=(base_iterator&& rhv) {
	if (this == &rhv) {
		return *this;
	}
	this->ptr = rhv.ptr;
	rhv.ptr = nullptr;
	return *this;
}
  
template<typename T>
FrankList<T>::desc_iterator::desc_iterator(Node* ptr) : const_desc_iterator(ptr) {}    

//const_multi_iterator
//copy ctor
template<typename T> 
FrankList<T>::const_multi_iterator::const_multi_iterator(const base_iterator& rhv) 
	:base_iterator(rhv.ptr) {}

//move ctor
template<typename T>
FrankList<T>::const_multi_iterator::const_multi_iterator(base_iterator&& rhv)
	:base_iterator(rhv.ptr) {
		rhv.ptr = nullptr;
	}

//copy = operator
template<typename T>
const typename FrankList<T>::const_multi_iterator& FrankList<T>::const_multi_iterator::operator=(const base_iterator& rhv) {
	this->ptr = rhv.ptr;
	return *this;
}

//move = operator
template<typename T>
const typename FrankList<T>::const_multi_iterator& FrankList<T>::const_multi_iterator::operator=(base_iterator&& rhv) {
	if (this->ptr != rhv.ptr) {
		this->ptr = rhv.ptr;
		rhv.ptr = nullptr;
	}
	return *this;
}

//* and -> operators 
template<typename T>
typename FrankList<T>::const_reference FrankList<T>::const_multi_iterator::operator*() const {
	return (this->ptr->val);
}

template<typename T>
typename FrankList<T>::const_pointer FrankList<T>::const_multi_iterator::operator->() const {
	return this->ptr;
}

//preincrement 
template<typename T>
const typename FrankList<T>::const_multi_iterator& FrankList<T>::const_multi_iterator::operator++() {
	if (mode) {
		this->ptr = this->ptr->next;
	} else {
		this->ptr = this->ptr->asc;
	}
	return (*this);
}

//postincrement
template<typename T>
const typename FrankList<T>::const_multi_iterator FrankList<T>::const_multi_iterator::operator++(int) {
	const_multi_iterator tmp(*this);
	++(*this);
	return tmp;
}

//predecrement
template<typename T>
const typename FrankList<T>::const_multi_iterator& FrankList<T>::const_multi_iterator::operator--() {
	if (mode) {
		this->ptr = this->ptr->prev;
	} else {
		this->ptr = this->ptr->desc;
	}
	return (*this);
}

//postdecrement
template<typename T>
const typename FrankList<T>::const_multi_iterator FrankList<T>::const_multi_iterator::operator--(int) {
	const_multi_iterator tmp(*this);
	--(*this);
	return tmp;
}

template <typename T>
void
FrankList<T>::const_multi_iterator::chmod()
{
    mode = !mode;
}     

template<typename T>
FrankList<T>::const_multi_iterator::const_multi_iterator(Node* ptr) : base_iterator(ptr) {}

//multi_iterator : const_multi_iterator
template <typename T>
FrankList<T>::multi_iterator::multi_iterator(const base_iterator& rhv)
    :const_multi_iterator(rhv.ptr) {}

template <typename T>
FrankList<T>::multi_iterator::multi_iterator(base_iterator&& rhv)
    :const_multi_iterator(rhv.ptr) {
    rhv.ptr = nullptr;
}

template <typename T>
const typename FrankList<T>::multi_iterator&
FrankList<T>::multi_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const typename FrankList<T>::multi_iterator&
FrankList<T>::multi_iterator::operator=(base_iterator&& rhv)
{	
    if(this == &rhv) {
    	return *this;
    }
    this->ptr = rhv.ptr;
    rhv.ptr = nullptr;
    return *this;
}

template <typename T>
typename FrankList<T>::reference
FrankList<T>::multi_iterator::operator*()
{
    return this->ptr->val;
}

template <typename T>
typename FrankList<T>::pointer
FrankList<T>::multi_iterator::operator->()
{
    return this->ptr;
}

template <typename T> //check this
FrankList<T>::multi_iterator::multi_iterator(Node* ptr) : const_multi_iterator(ptr) {}

//const_multi_reverse_iterator : base_iterator
template <typename T>
FrankList<T>::const_multi_reverse_iterator::const_multi_reverse_iterator(const base_iterator& rhv)
    :base_iterator(rhv.ptr)
{}


template <typename T>
FrankList<T>::const_multi_reverse_iterator::const_multi_reverse_iterator(base_iterator&& rhv)
    :base_iterator(rhv.ptr)
{
    rhv.ptr = nullptr;
}

template <typename T>
const typename FrankList<T>::const_multi_reverse_iterator&
FrankList<T>::const_multi_reverse_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const typename FrankList<T>::const_multi_reverse_iterator&
FrankList<T>::const_multi_reverse_iterator::operator=(base_iterator&& rhv)
{
    if (this == &rhv) {
    	return *this;
    	}
    this->ptr = rhv.ptr;
    rhv.ptr = nullptr;
    return *this;
}

template <typename T>
typename FrankList<T>::const_reference FrankList<T>::const_multi_reverse_iterator::operator*() const {
    return this->ptr->val;
}

template <typename T>
typename FrankList<T>::const_pointer FrankList<T>::const_multi_reverse_iterator::operator->() const {
    return this->ptr;
}

template <typename T>
const typename FrankList<T>::const_multi_reverse_iterator&
FrankList<T>::const_multi_reverse_iterator::operator++()
{
    if (mode) {
        this->ptr = this->ptr->prev;
    }
    else {
        this->ptr = this->ptr->desc;
    }
    return *this;
}

template <typename T>
const typename FrankList<T>::const_multi_reverse_iterator
FrankList<T>::const_multi_reverse_iterator::operator++(int)
{
    const_multi_reverse_iterator tmp(*this);
    --(*this);
    return tmp;
}

template <typename T>
const typename FrankList<T>::const_multi_reverse_iterator&
FrankList<T>::const_multi_reverse_iterator::operator--()
{
    if (mode) {
        this->ptr = this->ptr->next;
    }
    else {
        this->ptr = this->ptr->asc;
    }
    return *this;
}

template <typename T>
const typename FrankList<T>::const_multi_reverse_iterator
FrankList<T>::const_multi_reverse_iterator::operator--(int)
{
    const_multi_reverse_iterator tmp(*this);
    ++(*this);
    return tmp;
}

template <typename T>
void
FrankList<T>::const_multi_reverse_iterator::chmod()
{
    mode = !mode;
}

template <typename T>
FrankList<T>::const_multi_reverse_iterator::const_multi_reverse_iterator(Node* ptr)
    :base_iterator(ptr)
{}

//multi_reverse_iterator : const_multi_reverse_iterator
template <typename T>
FrankList<T>::multi_reverse_iterator::multi_reverse_iterator(const base_iterator& rhv)
    :const_multi_reverse_iterator(rhv.ptr)
{}

template <typename T>
FrankList<T>::multi_reverse_iterator::multi_reverse_iterator(base_iterator&& rhv)
    :const_multi_reverse_iterator(rhv.ptr)
{
    rhv.ptr = nullptr;
}

template <typename T>
const typename FrankList<T>::multi_reverse_iterator&
FrankList<T>::multi_reverse_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
    return *this;
}

template <typename T>
const typename FrankList<T>::multi_reverse_iterator&
FrankList<T>::multi_reverse_iterator::operator=(base_iterator&& rhv)
{
    if (this == &rhv) {
    	return *this;
    }
    this->ptr = rhv.ptr;
    rhv.ptr = nullptr;
    return *this;
}

template <typename T>
typename FrankList<T>::reference
FrankList<T>::multi_reverse_iterator::operator*()
{
    return this->ptr->val;
}

template <typename T>
typename FrankList<T>::pointer
FrankList<T>::multi_reverse_iterator::operator->() {
    return this->ptr;
}
  
template <typename T>
FrankList<T>::multi_reverse_iterator::multi_reverse_iterator(Node* ptr) : const_multi_reverse_iterator(ptr) {}   
  
  
//default and parametric ctors for franklist class
template<typename T>
FrankList<T>::FrankList()
	:head(nullptr), tail(nullptr), ahead(nullptr), atail(nullptr) {}

template<typename T>
FrankList<T>::FrankList(size_type s) 
	:head(nullptr), tail(nullptr), ahead(nullptr), atail(nullptr) {
		for (size_type i = 0; i < s; ++i) {
			push_back(value_type());	
		}
	}
		
template<typename T>
FrankList<T>::FrankList(size_type size, const_reference init) 
	:head(nullptr), tail(nullptr), ahead(nullptr), atail(nullptr) {
		for (size_type i = 0; i < size; ++i) {
			push_back(init);
			}
		} 

//copy ctor
template<typename T>
FrankList<T>::FrankList(const FrankList<value_type>& rhv) 
	:head(nullptr), tail(nullptr), ahead(nullptr), atail(nullptr) {
		for (auto i = rhv.cbegin(); i != rhv.cend(); ++i) {
			push_back(*i);
		}
	}

//move ctor
template<typename T>
FrankList<T>::FrankList(FrankList<value_type>&& rhv) 
	:head(rhv.head), tail(rhv.tail), ahead(rhv.ahead), atail(rhv.atail) {
		rhv.head = nullptr;
		rhv.tail = nullptr;
		rhv.atail = nullptr;
		rhv.ahead = nullptr;
}

//init list //to be checked
template<typename T>
FrankList<T>::FrankList(std::initializer_list<value_type> init)
		:head(nullptr), tail(nullptr), ahead(nullptr), atail(nullptr) {
			for (auto i : init) {
				push_back(i);
			}
}

//initializing with input iterator
template<typename T>
template <typename input_iterator>
FrankList<T>::FrankList(input_iterator f, input_iterator l) 
	:head(nullptr), tail(nullptr), ahead(nullptr), atail(nullptr) {
		for (input_iterator i = f; i < l; ++i) {
			push_back(*i);
		}
	}

//dtor
template<typename T>
FrankList<T>::~FrankList() {
	clear();
}

template<typename T>
void FrankList<T>::swap(FrankList<value_type>& rhv) {
	std::swap(head, rhv.head);
	std::swap(tail, rhv.tail);
	std::swap(ahead, rhv.ahead);
	std::swap(atail, rhv.atail);
}

template<typename T>
typename FrankList<T>::size_type FrankList<T>::size() const {
	size_type s = 0;
	for (auto i = cbegin(); i != cend(); ++i) {
		++s;
	}
	return s;
}

template<typename T>
bool FrankList<T>::empty() const {
	if (head == nullptr) {
		return true;
	}
	return false;
}

template<typename T>
void FrankList<T>::resize(size_type s, const_reference init) {
	size_type current_size = size();
	if (s < current_size) {
		while (s < current_size) {
			pop_back();
		}
	} else {
		while (s >= current_size) {
			push_back(init);
		}
	}
}

template<typename T>
void FrankList<T>::clear() noexcept {
	while (head != nullptr) {
		Node* newHead = head;
		head = head->next;
		delete newHead;
	}
	head = nullptr;
	tail = nullptr;
	ahead = nullptr;
	atail = nullptr;
}

template<typename T>
void FrankList<T>::push_front(const_reference elem) {
	Node* newNode = new Node(elem);
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	} else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
	put_in_sorted_order(head);
}

template<typename T>
void FrankList<T>::pop_front() {
	if (head == nullptr) {
		return;
	}
	if (head->next == nullptr) { //no node
		clear();
		return;
	}
	if (head->asc != nullptr) {
		head->asc->desc = head->desc;
	}
	if (head->desc != nullptr) {
		head->desc->asc = head->asc;
	}
	head = head->next;
	delete head->prev;
	head->prev = nullptr;
}


template<typename T>
void FrankList<T>::push_back(const_reference elem) {
	//for your elem you need a new node
	Node* newNode = new Node(elem);
	if (head == nullptr) { // this is the first node
		head = newNode;
		tail = newNode;
	} else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	put_in_sorted_order(tail); 
}

template<typename T>
void FrankList<T>::pop_back() {
	if (head == nullptr) {
		return;
	}
	if (head->next == nullptr) {
		clear();
		return;
	}
	if (tail->asc != nullptr) {
		tail->asc->desc = tail->desc;
	}
	if (tail->desc != nullptr) {
		tail->desc->asc = tail->asc;
	}
	tail = tail->prev;
	delete tail->next;
	tail->next = nullptr;

}

template<typename T>
typename FrankList<T>::const_reference FrankList<T>::front() const { //return the first node, if it isn't nullptr
	if (head != nullptr) {
		return head->val;
	}
	return nullptr;
}

template<typename T>
typename FrankList<T>::reference FrankList<T>::front() {
	if (head != nullptr) {
		return head->val;
	}
	return nullptr;
}

template<typename T>
typename FrankList<T>::const_reference FrankList<T>::back() const {
	if (head != nullptr) {
		return tail->val;
	}
	return nullptr;
}

template<typename T>
typename FrankList<T>::reference FrankList<T>::back() {
	if (head != nullptr) {
		return tail->val;
	}
	return nullptr;
}

template<typename T>
typename FrankList<T>::const_reference FrankList<T>::min() const {
	if (head != nullptr) {
		return ahead->val;
	}
	return nullptr;
}

template<typename T>
typename FrankList<T>::reference FrankList<T>::min() {
	if (head != nullptr) {
		return ahead->val;
	}
	return nullptr;
}
    
template<typename T>
typename FrankList<T>::const_reference FrankList<T>::max() const {
	if (head != nullptr) {
		return atail->val;
	}
	return nullptr;
}

template<typename T>
typename FrankList<T>::reference FrankList<T>::max() {
	if (head != nullptr) {
		return atail->val;
	}
	return nullptr;
}

//copy assignment operator 
template<typename T>
const FrankList<T>& FrankList<T>::operator=(const FrankList<value_type>& rhv) {
	if (&rhv == this) {
		return *this;
	}
	for (auto i = rhv.cbegin(); i != rhv.cend(); ++i) {
		push_back(*i);
	}
	return *this;
}

//move assignment operator
template<typename T>
const FrankList<T>& FrankList<T>::operator=(FrankList<value_type>&& rhv) {
	head = rhv.head;
	tail = rhv.tail;
	ahead = rhv.ahead;
	atail = rhv.atail;

	rhv.head = nullptr;
	rhv.tail = nullptr;
	rhv.ahead = nullptr;
	rhv.atail = nullptr;

	return *this;
}

//assignment operator for init list
template<typename T>
const FrankList<T>& FrankList<T>::operator=(std::initializer_list<value_type> init) {
	if (&init == this) {
		return this;
	}
	for (auto i : init) {
		push_back(i);
	}
	return *this;
}

//comparison operators
template<typename T>
bool FrankList<T>::operator==(const FrankList<value_type>& rhv) const {
	if(size() != rhv.size()) {
		return false;
	}
	for (Node* i = ahead, j = rhv.ahead; i < size(), j < size(); i = i->next, j = j->next) {
		if(i->val != j->val) {
			return false;
		}
	}
	return true;
}

template<typename T>
bool FrankList<T>::operator!=(const FrankList<value_type>& rhv) const {
	if (*this == rhv) {
		return false;
	}
	return true;
}

template<typename T>
bool FrankList<T>::operator<(const FrankList<value_type>& rhv) const {
	if (size() < rhv.size()) {
		return true;
	}
	if (size() == rhv.size()) {
		for (Node* i = ahead, j = rhv.aheadd; i < size(), j < size(); i = i->next, j = j->next) {
			if (i->val > j->val) {
				return false;
			}
		}
	}
		return true;
}

template<typename T>
bool FrankList<T>::operator<=(const FrankList<value_type>& rhv) const {
	if (*this < rhv || *this == rhv) {
		return true;
	}
	return false;
}

template<typename T>
bool FrankList<T>::operator>(const FrankList<value_type>& rhv) const {
	if (*this <= rhv) {
		return false;
	} 
	return true;
}

template<typename T>
bool FrankList<T>::operator>=(const FrankList<value_type>& rhv) const {
	if (*this > rhv || *this == rhv) {
		return true;
	}
	return false;
}


//for god's sake (const iterator & const multi iterator)
template<typename T>
typename FrankList<T>::const_iterator FrankList<T>::cbegin() const {
	return const_iterator(head);
}

template<typename T>
typename FrankList<T>::const_iterator FrankList<T>::cend() const { //check it
	return const_iterator(tail->next);
}

template<typename T>
typename FrankList<T>::const_reverse_iterator FrankList<T>::crbegin() const {
	return const_reverse_iterator(tail);
}

template<typename T>
typename FrankList<T>::const_reverse_iterator FrankList<T>::crend() const { //check it
	return const_reverse_iterator(head->prev);
}

template<typename T>
typename FrankList<T>::const_asc_iterator FrankList<T>::cabegin() const { //minimum start
	return const_asc_iterator(ahead);
}

template<typename T>
typename FrankList<T>::const_asc_iterator FrankList<T>::caend() const { //maximum end
	return const_desc_iterator(atail->next); //check it
}

template<typename T>
typename FrankList<T>::const_desc_iterator FrankList<T>::cdbegin() const { //maximum start
	return const_desc_iterator(atail);
}

template<typename T>
typename FrankList<T>::const_desc_iterator FrankList<T>::cdend() const { //minimum end
	return const_desc_iterator(ahead->prev); //check it
}

//check mode
template<typename T>
typename FrankList<T>::const_multi_iterator FrankList<T>::cmbegin() const {
		return const_multi_iterator(head);
}

template<typename T>
typename FrankList<T>::const_multi_iterator FrankList<T>::cmend() const {
		return const_multi_iterator(tail->next);
}

template<typename T>
typename FrankList<T>::const_multi_iterator FrankList<T>::cmabegin() const {
	return const_multi_iterator(ahead);
}

template<typename T>
typename FrankList<T>::const_multi_iterator FrankList<T>::cmaend() const {
	return const_multi_iterator(atail->asc);
}

template<typename T>
typename FrankList<T>::const_multi_reverse_iterator FrankList<T>::cmrbegin() const {
	return const_multi_reverse_iterator(tail);
}

template<typename T>
typename FrankList<T>::const_multi_reverse_iterator FrankList<T>::cmrend() const {
	return const_multi_reverse_iterator(head->prev);
}

template<typename T>
typename FrankList<T>::const_multi_reverse_iterator FrankList<T>::cmrdbegin() const {
	return const_multi_reverse_iterator(atail);
}

template<typename T>
typename FrankList<T>::const_multi_reverse_iterator FrankList<T>::cmrdend() const {
	return const_multi_reverse_iterator(ahead->desc);
}

//iterator and multiiterator
template<typename T>
typename FrankList<T>::iterator FrankList<T>::begin() {
	return iterator(head);
}

template<typename T>
typename FrankList<T>::iterator FrankList<T>::end() {
	return iterator(tail->next);
}

template<typename T>
typename FrankList<T>::reverse_iterator FrankList<T>::rbegin() {
	return reverse_iterator(tail);
}

template<typename T>
typename FrankList<T>::reverse_iterator FrankList<T>::rend() {
	return reverse_iterator(head->prev);
}

template<typename T>
typename FrankList<T>::asc_iterator FrankList<T>::abegin() {
	return asc_iterator(ahead);
}

template<typename T>
typename FrankList<T>::asc_iterator FrankList<T>::aend() {
	return asc_iterator(atail->asc);
}

template<typename T>
typename FrankList<T>::desc_iterator FrankList<T>::dbegin() {
	return desc_iterator(atail);
}

template<typename T>
typename FrankList<T>::desc_iterator FrankList<T>::dend() {
	return desc_iterator(ahead->desc);
}

template<typename T>
typename FrankList<T>::multi_iterator FrankList<T>::mbegin() {
	return multi_iterator(head);
}

template<typename T>
typename FrankList<T>::multi_iterator FrankList<T>::mend() {
	return multi_iterator(tail->next);
}

template<typename T>
typename FrankList<T>::multi_iterator FrankList<T>::mabegin() {
	return multi_iterator(ahead);
}

template<typename T>
typename FrankList<T>::multi_iterator FrankList<T>::maend() {
	return multi_iterator(atail->asc);
}

template<typename T>
typename FrankList<T>::multi_reverse_iterator FrankList<T>::mrbegin() {
	return multi_reverse_iterator(tail);
}

template<typename T>
typename FrankList<T>::multi_reverse_iterator FrankList<T>::mrend() {
	return multi_reverse_iterator(head->prev);
}

template<typename T>
typename FrankList<T>::multi_reverse_iterator FrankList<T>::mrdbegin() {
	return multi_reverse_iterator(atail);
}
    
template<typename T>
typename FrankList<T>::multi_reverse_iterator FrankList<T>::mrdend() {
	return multi_reverse_iterator(ahead->descs);
}

 

template <typename T>
template <typename iter> iter FrankList<T>::insert(iter pos, size_type size, const_reference val) {
	for (size_type i = 0; i < size; ++i) {
		pos = insert(pos, val);
		}
	return pos;
}
    
template <typename T>
template <typename iter> iter FrankList<T>::insert(iter pos, std::initializer_list<value_type> init) {
	for (auto i : init) {
		pos = insert(pos, i);
		}
	return pos;
}

template <typename T> 
template <typename iter, typename input_iterator> iter FrankList<T>::insert(iter pos, input_iterator f, input_iterator l) {
	for (; f != l; ++f) {
		pos = insert(pos, *f);
		}
	return pos;
}


template <typename T>    
template <typename iter> iter FrankList<T>::erase(iter pos) {
	if (pos.ptr == nullptr) {
	throw std::out_of_range("Nothing to erase");
	}
	iter tmp(pos);
	++tmp;
	if (pos.ptr == head) {
		this->pop_front();
		return tmp;
	} else if (pos.ptr == tail) {
		this->pop_back();
		return tmp;
	} else {
		Node* deleting = pos.ptr;
		if (deleting->prev) {
			deleting->prev->next = deleting->next;
		} 
		if (deleting->next) {
			deleting->next->prev = deleting->prev;
		}
		if (deleting->asc) {
			deleting->asc->desc = deleting->desc;
		}
		if (deleting->desc) {
			deleting->desc->asc = deleting->asc;
		}
		delete pos.ptr;
	}
	return tmp;
}

template <typename T>    
template <typename iter> iter FrankList<T>::erase(iter f, iter l) {
	while (f != l) {
		f = erase(f);
	}
	return f;
}
 
template <typename T>   
typename FrankList<T>::size_type FrankList<T>::remove(const_reference val) {
    size_type count = 0;
    for (auto i = begin(); i != end();) {
        if (*i == val) {
            i = erase(i); 
            ++count;
        } else {
            ++i;
        }
    }
    return count;
}

template <typename T>
template <typename unary_predicate> 
typename FrankList<T>::size_type FrankList<T>::remove_if(unary_predicate func) {
    size_type count = 0;
    for (auto i = begin(); i != end();) {
        if (func(*i)) {
            i = erase(i); 
            ++count;
        } else {
            ++i;
        }
    }
    return count;
}

template <typename T>
void FrankList<T>::reverse() {
	std::swap(head, tail);
	Node* ptr = head;
	while (ptr) {
		std::swap(ptr->next, ptr->prev);
		ptr = ptr->next;
	}
}

template <typename T>
void FrankList<T>::sort(bool reversed) {
	if (ahead == nullptr) {
		return;
	}
	
	Node* tmp = nullptr;
	if (reversed == false) { //not reversed sort
		tmp = ahead;
		while (tmp) {
			tmp->next = tmp->asc;
			tmp->prev = tmp->desc;
			tmp = tmp->asc;
		}
		head = ahead;
		tail = atail;
	} else { //reversed sort
		tmp = atail;
		while (tmp) {
			tmp->next = tmp->desc;
			tmp->prev = tmp->asc;
			tmp = tmp->desc;
		}
		head = atail;
		tail = ahead;
	}
}
   

template <typename T>
typename FrankList<T>::iterator FrankList<T>::find(const_reference elem) {
    if (elem == head->val) {
    	return this->begin();
    }
    for (auto i = begin(); i != end(); ++i) {
    	if (*i == elem) {
    		organize_left(i.ptr);
    		 return iterator(i);
    	}
    }
  return this->end();
 
}

template <typename T>
typename FrankList<T>::iterator FrankList<T>::rfind(const_reference elem) {
	if (elem == tail->val) {
    		return this->rbegin();
   	 }
	for (auto i = rbegin(); i != rend(); ++i) {
    		if (*i == elem) {
    			organize_right(i.ptr);
    			return reverse_iterator(i);
    		}
    	}
    return this->rend();
}
   
template<typename T>
template <typename unary_predicate>
void FrankList<T>::traverse(unary_predicate func, bool sorted, bool reversed) {
	if (head == nullptr) {
		return;
	}
	if (!sorted && !reversed) { //false, false
		for (auto i = begin(); i != end(); ++i) {
			func(*i);
		}
	} else if (!sorted) { //reversed
		for (auto i = rbegin(); i != rend(); ++i) {
			func(*i);
		}
	} else if (!reversed) { //sorted
		for (auto i = abegin(); i != aend(); ++i) {
			func(*i);
		}
	} else { //true, true
		for (auto i = dbegin(); i != dend(); ++i) {
			func(*i);
		}
	}
} 

template<typename T>
void FrankList<T>::print(bool sorted, bool reversed) {
	if (head == nullptr) {
	std::cout << "empty list";
	return;
	}
	if (!sorted && !reversed) {
		for (auto i = begin(); i != end(); ++i) {
			std::cout << *i << " ";
		}
	} else if (!reversed) { //reverse = false, ascending order
		for (auto i = abegin(); i != aend(); ++i) {
			std::cout << *i << " ";
		}
	} else if (!sorted) { //sorted = false
		for (auto i = rbegin(); i != rend(); ++i) {
			std::cout << *i << " ";
		}
	} else { //both true, descending order
		for (auto i = dbegin(); i != dend(); ++i) {
			std::cout << *i << " ";
		}
	}

} 
  
template<typename T> 
void FrankList<T>::put_in_sorted_order(Node* ptr) {
	if (ptr == nullptr) {
		return;
	}
	if (ahead == nullptr) {
		ahead = ptr;
		atail = ptr;
		return;
	}
	Node* newptr = ahead;
	while (newptr->val <= ptr->val && newptr->asc != nullptr) {
			newptr = newptr->asc;
	}

	if (newptr->val < ptr->val) {
		ptr->asc = newptr->asc;
		newptr->asc = ptr;
		ptr->desc = newptr;
		if (ptr->asc == nullptr) {
			atail = ptr;
		}
	} else { // your min elem isn't minimum anymore
		ptr->desc = newptr->desc;
		if(newptr->desc != nullptr) {
			newptr->desc->asc = ptr;
		} else { // you found your min
			ahead = ptr;
		}
		ptr->asc = newptr; //all is ordered, so you know where should be put newptr
		newptr->desc = ptr; // these two nodes should point to each other
		
	}
}


template <typename T>
void FrankList<T>::organize_left(Node* ptr) {
	if (ptr == nullptr || ptr->prev == nullptr) {
      		  return;
   	 }
   	 Node* current = ptr;
    	 Node* prevNode = current->prev;
	 std::swap(current->val, prevNode->val);
    	 if (current->val > prevNode->val) {
               current->asc = prevNode->asc;
       	       prevNode->desc = current->desc;
    } else if (current->val < prevNode->val) {
       	       prevNode->asc = current->asc;
               current->desc = prevNode->desc;
    }
    // final touches for head and tail
    if (prevNode->prev != nullptr) {
        prevNode->prev->next = current;
    }
    current->prev = prevNode->prev;
    prevNode->prev = current;
    prevNode->next = current->next;
    current->next = prevNode;

    if (prevNode->next != nullptr) {
        prevNode->next->prev = prevNode;
    }
}

template <typename T>
void FrankList<T>::organize_right(Node* ptr) {

	if (ptr == nullptr || ptr->next == nullptr) {
        		return;
   	 }

         Node* current = ptr;
    	 Node* nextNode = current->next;
	 std::swap(current->val, nextNode->val);
        if (current->val < nextNode->val) {
          	 current->asc = nextNode->asc;
          	 nextNode->desc = current->desc;
   	 } else if (current->val > nextNode->val) {
   	 	nextNode->asc = current->asc;
        	current->desc = nextNode->desc;
    }

    if (nextNode->next != nullptr) {
        nextNode->next->prev = current;
    }
    current->next = nextNode->next;
    nextNode->next = current;
    nextNode->prev = current->prev;
    current->prev = nextNode;

    if (nextNode->prev != nullptr) {
        nextNode->prev->next = nextNode;
    }
}

template <typename T>
template <typename iter> iter FrankList<T>::insert_def(iter pos, const_reference val) {
    	if (pos.ptr== nullptr) {
    		throw std::out_of_range("impossible to insert");
    	}
    	if (pos.ptr == head) {
    		push_front(val);
    	} else if (pos.ptr == tail) {
    		push_back(val);
    	} else {
    		Node* place = new Node(val);
    		pos.ptr->prev->next = place;
    		place->prev = pos.ptr->prev;
    		pos.ptr->prev = place;
       		place->next = pos.ptr;
    		put_in_sorted_order(place);
    	}
    	return pos;
}
    
template <typename T>
template <typename iter> iter FrankList<T>::insert_rev(iter pos, const_reference val) {
	//do the same if there is 1 elem
	insert(pos, val);
	//in case there is more than 1 elem, the next elems should be positiond before the previous elem(s)
	--pos;
	return pos;		
} 

}
#endif 
