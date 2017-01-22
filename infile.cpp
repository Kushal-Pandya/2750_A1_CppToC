#include<stdio.h>
#include<stdlib.h>

// This is a comment

class A {
	int a;
	int add(int b, int c) {
		/*This is also a comment*/
		return (b+c);
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
	myAClass.a = 7;
	myAClass.add(1, 1);

	printf("Hi this has \" esc char class");

}
