#include <math.h>

extern double F(double x);

double Met_P (double a,double b,int n)

{

double h, x, s; int i;

h=(b-a)/n;

x=a; s=0;

for (i=1;i<=n;i++)

{

s=s+F(x+h/2);

x=x+h;

}

s=s*h;

return (s);

}

double Met_T (double a,double b,int n)

{

double h, x1, x2, s; int i;

h=(b-a)/n;

x1=a; x2=a+h; s=0;

for (i=1;i<=n;i++)

{

s=s+F(x1)+F(x2);

x1=x2; x2=x2+h;

}

s=s*h/2;

return (s);

}

double Met_S (double a,double b,int n)

{

double h, x1, x2, x3, s; int i;

h=(b-a)/n;

x1=a; x2=a+h; x3=x2+h; s=0;

for (i=1;i<=n/2;i++)

{

s=s+F(x1)+4*F(x2)+F(x3);

x1=x3; x2=x3+h; x3=x2+h;

}

s=s*h/3;

return (s);

}



#include <iostream>

#include <conio.h>
using namespace std;

int main()

{

double I1, I2, eps, epsil; int n;

clrscr;

cout<<"\n*** Программа вычисляет интеграл f=cos(x^2)на[0,1] ***\n"

<<"*** с заданной точностью eps различными методами ***\n"

<<"\n‚Введите точность: eps=";

cin>>epsil;

cout<<"\n___Метод прямоугольников___";

n=1; eps=1000;

while (eps>epsil)

{

n=n*2;

I1 = Met_P(1,2,n); I2 = Met_P(1,2,n*2);

eps=fabs(I1-I2)/3;

}

I1=I2+eps;

//cout<<"\n\nРезультат: "<<I1<<"\nn = "<<n<<"\nТочность: ";printf(" %0.7f", eps);//<<eps;
cout<<"\n\nРезультат: ";printf(" %0.7f", I1);printf(" I2 = %0.7f", I2); cout<<"\nn = "<<n<<"\nТочность: ";printf(" %0.7f", eps);//<<eps;

cout<<"\n\n___Метод трапеций___";

n=1; eps=1000;

while (epsil<eps)

{

n=n*2;

I1 = Met_T(1,2,n); I2 = Met_T(1,2,n*2);

eps=fabs(I1-I2)/3;

}

I1=I2-eps;

//cout<<"\n\nРезультат: "<<I1<<"\nn = "<<n<<"\nТочность: "; printf(" %0.7f", eps);//<<eps;
cout<<"\n\nРезультат: ";printf(" %0.7f", I1); printf(" I2 = %0.7f", I2);cout<<"\nn = "<<n<<"\nТочность: ";printf(" %0.7f", eps);//<<eps;

cout<<"\n\n___Метод Симпсона ___";

n=1; eps=1000;

while (epsil<eps)

{

n=n*2;

I1 = Met_S(1,2,n); I2 = Met_S(1,2,n*2);

eps=fabs(I1-I2)/15;

}

I1=I2-eps;

//cout<<"\n\nРезультат: "<<I1<<"\nn = "<<n<<"\nТочность: "; printf(" %0.7f", eps); ///<<eps;
cout<<"\n\nРезультат: ";printf(" I1 = %0.7f", I1); printf(" I2 = %0.7f", I2); cout<<"\nn = "<<n<<"\nТочность: ";printf(" %0.7f", eps);//<<eps;

getch();
return 0;
}

double F(double x)
{
    double s;
    s = sinh(x*x);
    return s;
}
