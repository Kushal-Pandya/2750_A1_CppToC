#include<stdio.h>
#include<stdlib.h>

// This is a comment

float num = 1.5;

class A {
	int a;
	int add() {
		/*This is also a comment*/
		return (1+1);
	}
	int subtract(int d, int e) {
		return (d-e);
	}
};

class B {
	int a;
	int add(int b, int c) {
		return (b+c);
	}
};

int main() {
	class A myAClass;
	class B myBClass;

	myAClass.a = 7;
	myAClass.add(1, 1);

	printf("Hi this has \" esc char class");

}
