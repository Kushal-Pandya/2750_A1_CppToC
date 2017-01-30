#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct A {
int a;
int (*Asumiii)();
}
int Asum(){
}
struct B {
float a;
float b;
float c;
void (*Bsetaf)();
void (*Bsetbf)();
void (*Bsetcf)();
float (*Bgeta)();
float (*Bgetb)();
float (*Bgetc)();
}
float Bgetc(){
}

int main(int argc,char *argv[]) {
struct A myA;
constructorA(&myA);
int total;
int a;
int b;
int c;
struct B myB;
constructorB(&myB);
float val;
a=1;
b=2;
c=3;
total=myA.sum(a,b,c);
printf("output shoudl be 6: %d\n",total);
val=1.5;
myB.seta(val);
printf("output should be 1.50000: %f\n",myB.geta());
}

