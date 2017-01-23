#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int a;

struct B {
	int b;
	int (*Bfn) ();
};

int Bfn() {
	printf("Bfn printed\n");
}

int constructorB(struct B* self) {
	self->Bfn = &Bfn;
}

int main(int argc, char* argv[]) {

	struct B myB;
	constructorB(&myB);

	myB.b = 3;
	myB.Bfn();

	return 0;
}