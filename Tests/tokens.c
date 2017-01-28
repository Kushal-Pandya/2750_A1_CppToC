#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int a;

struct B {
	int b;
	int (*Bfn) ();
	int (*Bfn2) ();
};

int Bfn(struct B self) {
	int c = 5, f = 5;
	printf("Bfn printed %d\n", self.b);
}

int Bfn2() {
	printf("TESTING\n");
}

int constructorB(struct B* self) {
	self->Bfn = &Bfn;
	self->Bfn2 = &Bfn2;
	self->b = 5;
}

int main(int argc, char* argv[]) {

	struct B myB;
	constructorB(&myB);

	myB.Bfn(myB);
	myB.Bfn2(myB);


	return 0;
}