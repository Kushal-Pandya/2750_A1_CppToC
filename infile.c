#include<stdio.h>
#include<stdlib.h>

// This is a comment

//float num = 1.5;

struct A theA;
struct A otherA;
float num;

int globalFn(int param) {
printf("%d",param);
}

int main(int argc,char *argv[]) {
struct A myAClass;
constructorA(&myAClass);
struct B myBClass;
constructorB(&myBClass);
char str[50];
myAClass.a=7;
myAClass.add(1,1);
printf("Hi this has \" esc char class");
}


struct A {
int a;
int b;
int c;
char *value;
int (*Aadd)();
double (*Asubtracti)();
void (*Aset)();
};
void Aset(){
}
struct B {
int a;
struct A myA;
constructorA(&myA);
int (*Baddi)();
};
int Badd(){
}



