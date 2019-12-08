#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
using namespace std;

int main()
  {
    // clrscr();
     int k;
     long int s;
     float a1,b1,epsf;
     double a,b,eps,x,x1,X1;
     double F(double);
     double PRM(double,double,double,int);
     double TRAP(double,double,double,int);
     double SIMPSON(double,double,double,int);
     cout<<"\n                 Welcome!\n\n";
     cout<<"I = sin(2x)*exp(-x^2),  [1,2]\n\n";
     //printf("Input a: ");
    // scanf("%f",&a1);
     //a=a1;
    // printf("Input b: ");
     //scanf("%f",&b1);
     //b=b1;
     a = 1.0;
     b = 2.0;
     printf("Input eps: ");
     scanf("%f",&epsf);
     eps=epsf;
     k=2;
     x1 = PRM(a,b,eps,k);
     printf("\n  x1 = %f\n",x1);
     do
	{
	   X1=x1;
	   k=k*2;
	   x1 = PRM(a,b,eps,k);
	   printf("  x1 = %f\n",x1);
	   a1=(X1-x1)/3;
	  // a1=fabs(x1-X1)/3;
	   printf("\n a1 = %0.7f", a1);
	}
     while (fabs(a1)>eps);
    // printf("\n\tMetod pryamougolnikov:  I = %f    k=%d\n",X1-a1,k);
     printf("\n\tMetod pryamougolnikov:  I = %f    k=%d\n",X1,k);
     k=2;
     x1 = TRAP(a,b,eps,k);
     printf("\n  x1 = %f\n",x1);
     do
	{
	   X1=x1;
	   k=k*2;
	   x1 = TRAP(a,b,eps,k);
	   printf("  x1 = %f\n",x1);
	   a1=(X1-x1)/3;
	  // a1=fabs(x1-X1)/3;
	   printf("\n a1 = %0.7f", fabs(a1));
	}
     while (fabs(a1)>eps);
    // printf("\tMetod trapecii:         I = %f    k=%d\n",X1-a1,k);
    printf("\n\tMetod trapecii:  I = %f    k=%d\n",X1,k);
     k=2;
     x1 = SIMPSON(a,b,eps,k);
     printf("\n x1 = %f",x1);
     do
	{
	   X1=x1;
	   k=k*2;
	   x1 = SIMPSON(a,b,eps,k);
	   printf("  x1 = %f\n",x1);
	   a1=(X1-x1)/3;
	  // a1=fabs(x1-X1)/3;
	   printf(" a1 = %0.7f", a1);
	} while (fabs(a1)>eps);
     //printf("\tMetod Simpsona:         I = %f    k=%d\n",X1-a1,k);
     printf("\n\tMetod Simpsona:  I = %f    k=%d\n",X1,k);
     cout<<"\nPress any key to exit, please.\n";
     getch();
  }

double F(double x)
{
    double s;
    s = sinh(x*x);
    return s;
}

double PRM(double L,double R,double Eps,int n)
   {
      double X,h=(R-L)/n;
      int i;
      float sum=0;
      if (Eps<=0.0) {puts("Nevernoe zadanie tochnosti\n");exit(1);}
      for(i=0;i<=n-1;i++)
	 {
	    X = L+i*h;     /* vichislenie serediny otrezka */
	    sum=sum+F(X+h/2);
	 }
      return(sum*h);
   }

double TRAP(double L,double R,double Eps,int n)
   {
      double X,h=(R-L)/n;
      int i;
      float sum=0;
      if (Eps<=0.0) {puts("Nevernoe zadanie tochnosti\n");exit(1);}
      for(i=0;i<=n-1;i++)
	 {
	    X = L+i*h;     /* vichislenie serediny otrezka */
	    sum=sum+F(X)+F(L+(i+1)*h);
	 }
      return(sum*h/2);
   }

double SIMPSON(double L,double R,double Eps,int n)
   {
      double X,h=(R-L)/n;
      int i;
      float sum=0;
      if (Eps<=0.0) {puts("Nevernoe zadanie tochnosti\n");exit(1);}
      for(i=0;i<=n-1;i+=2)
	 {
	    X = L+i*h;     /* vichislenie serediny otrezka */
	    sum=sum+F(X)+4*F(L+(i+1)*h)+F(L+(i+2)*h);
	 }
      return(sum*h/3);
   }
