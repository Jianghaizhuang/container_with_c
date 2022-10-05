#include <stdio.h>
#include "stdlib.h"
#include "string.h"

typedef struct Base {
	void *ptr_vtbl;
	int ele1;
	int ele2;
} Base;

typedef struct Vtbl {
	void (*pf1)(void*);
	void (*pf2)(void*, int);
	void (*pf3)(void*, int, int);
} Vtbl;

void foo1(void*);
void foo2(void*, int);
void foo3(void*, int, int);
Vtbl g_vtbl = { &foo1, &foo2, &foo3 };

void foo1(void* this_ptr) {
	if (this_ptr == NULL) {
		printf("Derivec class, parameter wrong.\n");
		return;
	}
	Base* ptr = (Base*)this_ptr;
	printf("function 1 : %d .\n", ptr->ele1);
}
void foo2(void* this_ptr, int val1) {
	if (this_ptr == NULL) {
		printf("Derivec class, parameter wrong.\n");
		return;
	}
	Base* ptr = (Base*)this_ptr;
	printf("function 2 : %d .\n", ptr->ele2);
}
void foo3(void* this_ptr, int val1, int val2) {
	if (this_ptr == NULL) {
		printf("Derivec class, parameter wrong.\n");
		return;
	}
	Base* ptr = (Base*)this_ptr;
	printf("function 3 : %d and %d \n", ptr->ele1, ptr->ele2);
}

void initBase(Base* p) {
	p->ptr_vtbl = &g_vtbl;
	p->ele1 = 1024;
	p->ele2 = 3333;
}



void sfool(void*);
typedef struct Svtbl {
	Vtbl base_vbtl;
	void (*pf4)(void*);
} Svtbl;

Svtbl g_svbtl = {{&foo1, &foo2, &foo3}, &sfool};

typedef struct Derive {
	Base a;
	int ele3;
} Derive;

void initDerive(Derive *p) {
	p->a.ptr_vtbl = &g_svbtl;
	p->a.ele1 = 1024;
	p->a.ele2 = 112234;
	p->ele3 = 1314;
}

void sfool (void* this_ptr) {
	if (this_ptr == NULL) {
		printf("Derivec class, parameter wrong.\n");
		return;
	} 
	Derive* ptr = (Derive*)this_ptr;
	printf("Derived class print : %d .\n", ptr->ele3);
	
}


int main() {

	Base bs;
	initBase(&bs);
	(((Vtbl*)bs.ptr_vtbl)->pf1)(&bs);

	Derive de;
	initDerive(&de);
	(((Svtbl*)(de.a.ptr_vtbl))->pf4)(&de);
	Svtbl* ptr_der = (Svtbl*)(de.a.ptr_vtbl);
	ptr_der->pf4(&de);
	ptr_der->base_vbtl.pf1(NULL);

	return 0;
}