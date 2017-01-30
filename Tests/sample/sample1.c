#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* different ways to access variables */

int a;
struct A {
int a;
void (*Aprint1i)();
void (*Aprint2)();
void (*Aprint3)();
}
void Aprint3(){
}
struct B {
void (*Bprint4)();
}
void Bprint4(){
}


// simple function outside of a class 


float product(float a,float b) {
return(a*b);
}

int main(int argc,char *argv[]) {
struct A myA;
constructorA(&myA);
struct B myB;
constructorB(&myB);
int value;
char str[100];
printf("Hello \" there\n");
strcpy(str,"A string containing the word class may be tricky");
a=4;
value=1;
myA.print1(value);
myA.print2();
myA.print3();
myB.print4();
}



