#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int a;

struct B {
	int b;
	int (*Bfn) ();
	int (*Bfn2) ();
};

int Bfn() {
	printf("Bfn printed\n");
}

int Bfn2() {
	printf("TESTING\n");
}

int constructorB(struct B* self) {
	self->Bfn = &Bfn;
	self->Bfn2 = &Bfn2;
}

int main(int argc, char* argv[]) {

	struct B myB;
	constructorB(&myB);

	myB.b = 3;
	myB.Bfn();
	myB.Bfn2();

	return 0;
}