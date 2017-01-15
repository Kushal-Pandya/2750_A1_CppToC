#include <stdio.h>
#include <stdlib.h>

class A {
	int a;
	int add(int b, int c) {
		return (b+c);
	}
};

int main() {
	class A myAClass;
	myAClass.a = 7;
	myAClass.add(1, 1);
}