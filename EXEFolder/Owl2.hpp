#pragma once
/*
	Realization of OneWayListTemplate using ChainPosition
	Author: Dr. Holly
*/

#include "dereferee.h"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
class OneWayList2
	//! is modeled by tuple of
	//!   left: string of T
	//!   right: string of T
	//! exemplar self
{
public: // standard Operations
	OneWayList2 ();
		//! alters self
		//! ensures: self.left = < >  and  self.right = < >
	OneWayList2 (const OneWayList2& s);
	~OneWayList2 ();
	void clear (void);
		//! alters self
		//! ensures: self.left = < >  and  self.right = < >
	void operator &= (OneWayList2& rhs);
		//! alters self, rhs
		//! ensures: self = #rhs  and  rhs = #self
	OneWayList2& operator = (OneWayList2& rhs);
		//! alters self
		//! preserves rhs
		//! ensures: self = rhs

	// OneWayList2 Specific Operations
	void moveToStart (void);
		//! alters self
		//! ensures: self.left = < >  and  self.right = #self.left o #self.right
	void moveToFinish (void);
		//! alters self
		//! ensures: self.right = < >  and  self.left = #self.left o #self.right
	void advance (void);
		//! alters self
		//! requires: self.right /= < >
		//! ensures: there exists x: T 
		//!       (self.left = #self.left o <x>  and  #self.right = <x> o self.right)
	void addRight (T& item);
		//! alters self
		//! consumes item
		//! ensures: self.left = #self.left  and  self.right = <#item> o #self.right
	void removeRight (T& item);
		//! alters self
		//! produces item
		//! requires: self.right /= < >
		//! ensures: self.left = #self.left  and  #self.right = <item> o self.right
	T& operator [] (Integer index);
		//! preserves self
		//! preserves p
		//! requires: there exists x: T  and  y: string of T, self.right = <x> o y
		//! ensures: operator [] = &x
	void swapRights (OneWayList2& s);
		//! alters self, other_s
		//! ensures: self.left = #self.left  and  s.left = #s.left  and
		//!       s.right = #self.right  and  self.right = #s.right
	Integer leftSize (void);
		//! preserves self
		//! ensures: leftSize() = |self.left|
	Integer rightSize (void);
		//! preserves self
		//! ensures: rightSize() = |self.right|
	void displayRep (void);

private: // representation
	class NodeClass {
	public:
		T value;
		checked (NodeClass*) next;
	};

	class BookkeepingClass {
	public:
		checked (NodeClass*) head;
		Integer lz;
		Integer rz;
	};

	checked (BookkeepingClass*) rep;

	// disallowed OneWayList2 Operations

	OneWayList2* operator & (void) {return (this);};
	const OneWayList2* operator & (void) const {return (this);};
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------
template <class T>
OneWayList2<T>::OneWayList2 ()
{
	rep = new BookkeepingClass;
	rep->head = NULL;
}	// OneWayList2

//-----------------------------------------------------------------------

template <class T>
OneWayList2<T>::OneWayList2 (const OneWayList2& s)
{
	T item;
	Integer lz, rz, i, z;

	rep = new BookkeepingClass;
	rep->head = NULL;
	rep->rz = 0;
	rep->lz = 0;	

	checked (NodeClass*) newNode;
	
	rz = s.rep->rz;
	lz = s.rep->lz;
	
	newNode = s.rep->head;
	while(newNode != NULL){
		item = newNode->value;
		checked (NodeClass*) newNode;
		checked (NodeClass*) prevNode;
		newNode = new NodeClass;
		newNode->value &= item;
		prevNode = rep->head;
		if(rep->lz == 0) {
			newNode->next = rep->head;
			rep->head = newNode;
			rep->rz++;
		} else {
			i = 1;
			z = rep->lz;
			while(i != z) {
				prevNode = prevNode->next;
				i++;
			} //end while
			newNode->next = prevNode->next;
			prevNode->next = newNode;
			rep->rz++;
		} //end if
		newNode = newNode->next;
		rep->rz--;
		rep->lz++;
	} // end while
	rep->rz = rz;
	rep->lz = lz;
} // Copy Constructor

//-----------------------------------------------------------------------
template <class T>
OneWayList2<T>::~OneWayList2 ()
{
	checked (NodeClass*) newNode;
	checked (NodeClass*) nextNode;

	newNode = rep->head;
	while(newNode != NULL) {
		nextNode = newNode->next;
		delete newNode;
		newNode = nextNode;
	} // end while
	delete rep;
}	// ~OneWayList2

//-----------------------------------------------------------------------

template <class T>
void OneWayList2<T>::operator &= (OneWayList2& rhs)
{
	checked (BookkeepingClass*) temp;
	temp = rep;
	rep = rhs.rep;
	rhs.rep = temp;
}	// operator &=

//-----------------------------------------------------------------------

template <class T>
OneWayList2<T>& OneWayList2<T>::operator = (OneWayList2& rhs)
{
	T item;
	Integer lz, rz, i, z;

	checked (NodeClass*) newNode;
	checked (NodeClass*) nextNode;
	checked (NodeClass*) copyNode;
	
	rz = rhs.rep->rz;
	lz = rhs.rep->lz;

	newNode = rep->head;
	while(newNode != NULL) {
		nextNode = newNode->next;
		delete newNode;
		newNode = nextNode;
	} // end while
	rep->head = NULL;
	rep->rz = 0;
	rep->lz = 0;
	nextNode = rep->head;
	newNode = rhs.rep->head;
	while(newNode != NULL) {
		item = newNode->value;
		checked (NodeClass*) newNode;
		checked (NodeClass*) prevNode;
		newNode = new NodeClass;
		newNode->value &= item;
		prevNode = rep->head;
		if(rep->lz == 0) {
			newNode->next = rep->head;
			rep->head = newNode;
			rep->rz++;
		} else {
			i = 1;
			z = rep->lz;
			while(i != z) {
				prevNode = prevNode->next;
				i++;
			} //end while
			newNode->next = prevNode->next;
			prevNode->next = newNode;
			rep->rz++;
		} //end if
		newNode = newNode->next;
	} //end while
	rep->rz = rz;
	rep->lz = lz;

	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class T>
void OneWayList2<T>::clear (void)
{
	checked(NodeClass*) newNode;
	checked(NodeClass*) nextNode;

	newNode = rep->head;
	while(newNode != NULL){
		nextNode = newNode->next;
		delete newNode;
		newNode = nextNode;
	} // end while
	rep->head=NULL;

	rep->rz = 0;
	rep->lz = 0;
}	// clear

//-----------------------------------------------------------------------

template <class T>
void OneWayList2<T>::moveToStart (void)
{
	rep->rz = rep->rz + rep->lz;
	rep->lz = 0;
}	// moveToStart

//-----------------------------------------------------------------------

template <class T>
void OneWayList2<T>::moveToFinish (void)
{
	rep->lz = rep->rz + rep->lz;
	rep->rz = 0;
}	// moveToFinish

//-----------------------------------------------------------------------

template <class T>
void OneWayList2<T>::advance (void)
{
	rep->rz--;
	rep->lz++;
}	// advance

//-----------------------------------------------------------------------

template <class T>
void OneWayList2<T>::addRight (T& item)
{	
	Integer i, z;

	checked(NodeClass*) newNode;
	checked(NodeClass*) prevNode;

	newNode = new NodeClass;
	newNode->value &= item;
	prevNode = rep->head;

	if (rep->lz == 0){
		newNode->next = rep->head;
		rep->head = newNode;	
		rep->rz++;
	} else {
		//walk linked list (using left.size)
		//insert node at correct spot
		i = 1;
		z = rep->lz;
		while (i != z) {
			prevNode = prevNode->next;
			i++;
		} // end while
		newNode->next = prevNode->next;
		prevNode->next = newNode;
		rep->rz++;
	} // end if
}	// addRight

//-----------------------------------------------------------------------

template <class T>
void OneWayList2<T>::removeRight (T& item)
{
	Integer i, z;

	checked(NodeClass*) nextNode;
	checked(NodeClass*) prevNode;

	prevNode = rep->head;
	if(rep->lz == 0){
		item &= prevNode->value;
		rep->head = prevNode->next;
		delete prevNode;
	} else {
		i = 1;
		z = rep->lz;
		while(i != z){
			prevNode = prevNode->next;
			i++;
		} // end while
		nextNode = prevNode->next;
		prevNode->next = nextNode->next;
		item &= nextNode->value;
		delete nextNode;
	} // end if
	rep->rz--;
}	// removeRight

//-----------------------------------------------------------------------

template <class T>
T& OneWayList2<T>::operator [] (Integer index)
{
	T x;
	Integer i, z;

	checked(NodeClass*) nextNode;
	checked(NodeClass*) prevNode;

	z = rep->lz;
	prevNode = rep->head;
	while(i != z) {
		prevNode = prevNode->next;
		i++;
	}//end while
	x = prevNode->value;

	return(prevNode->value);
}  // operator []

//-----------------------------------------------------------------------

template <class T>
void OneWayList2<T>::swapRights (OneWayList2& s)
{
	Integer i1, i2, z1, z2;

	i1 = 1;
	i2 = 1;
	z1 = rep->lz;
	z2 = s.rep->lz;

	checked(NodeClass*) n1;
	checked(NodeClass*) n2;
	checked(NodeClass*) temp;

	n1 = rep->head;
	n2 = s.rep->head;
	if(z1 == 0){
		if(z2 == 0) {
			temp = rep->head;
			rep->head = s.rep->head;
			s.rep->head = temp;
		} else {
			while(i2 < z2) {
				n2 = n2->next;
				i2++;
			} //end while
			temp = rep->head;
			rep->head = n2->next;
			n2->next = temp;
		} //end if
	} else {
		while(i1 < z1) {
			n1 = n1->next;
			i1++;
		} //end while
		if(z2 == 0) {
			temp = n1->next;
			n1->next = s.rep->head;
			s.rep->head = temp;
		} else {
			while(i2 < z2) {
				n2 = n2->next;
				i2++;
			} //end while
			temp = n1->next;
			n1->next = n2->next;
			n2->next = temp;
		} //end if
	} //end if
	rep->rz &= s.rep->rz;
}	// swapRights

//-----------------------------------------------------------------------

template <class T>
Integer OneWayList2<T>::leftSize (void)
{
	return (rep->lz);
}	// leftSize

//-----------------------------------------------------------------------

template <class T>
inline Integer OneWayList2<T>::rightSize (void)
{
	return (rep->rz);
}	// rightSize

//-----------------------------------------------------------------------

template <class T>
void OneWayList2<T>::displayRep (void)
{
	Integer i, r, l, z;
	
	l = rep->lz;
	r = rep->rz;	
	i = 0;
	z = l + r;

    checked(NodeClass*) newNode;
	checked(NodeClass*) prevNode;

	std::cout << "&rep = " << rep << endl;
	std::cout << "rep->head = " << rep->head << endl;
	std::cout << "rep->lz = " << rep->lz << endl;
	std::cout << "rep->rz = " << rep->rz << endl;
	std::cout << endl;
	std::cout << "Node #  " << "Node Address    " << "[value,     next]" << endl;

	if(rep->head != NULL) {
		prevNode = rep->head;
		cout << "Node #	" << "Node Address	" << "[value,	    next]"<<endl;
		while(prevNode != NULL) {
			cout << i << "	" << prevNode << "	[" << prevNode->value <<",	" << prevNode->next << "]" <<endl;
			prevNode = prevNode->next;
			i++;
		} // end while
	} // end if
}	// displayRep