/******************************************************************************
                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.
*******************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
//#include "methods.h"
#define PI 3.14159265
using namespace std;
double delta, c, d;


double Round(double X, double Delta) {
  if (Delta <= 1E-9) {
    puts("Неверное задание точности округления\n");
    exit(1);
  }
 
  if (X > 0.0) {
    return Delta * long(X / Delta + 0.5);
  } else {
    return Delta * long(X / Delta - 0.5);
  }
}



double F(double x) {
 /* if(x < 0){
    cout << "Отрицательный x";
    exit(1);
  } */
  extern double delta;
  double s;
  long S;
  //s = atan(x)*180/PI - log(x);
   s = atan(x) - log(x);
  if (s / delta < 0) {
    S = s / delta - 0.5;
  } else {
    S = s / delta + 0.5;
  }
 
  s = S * delta;
  s = Round(s, delta);
  return s;
}




double BISECT(double Left, double Right, double Eps, int &N) {
  double E = fabs(Eps) * 2.0;
  double FLeft = F(Left);
  double FRight = F(Right);
  double X = 0.5 * (Left + Right);
  double Y;
 
  if (FLeft * FRight > 0.0) {
    puts("Неверное задание интервала\n");
    exit(1);
  }
 
  if (Eps <= 0.0) {
    puts("Неверное задание точности\n");
    exit(1);
  }
 
  if (FLeft == 0.0) {
    return Left;
  }
 
  if (FRight == 0.0) {
    return Right;
  }
 
  for (N = 0; Right - Left >= E; N++) {
    X = 0.5 * (Right + Left);	// вычисление середины отрезка
    Y = F(X);
 
    if (Y == 0.0) {
      return X;
    }
 
    if (Y * FLeft < 0.0) {
      Right = X;
    } else {
      Left = X;
      FLeft = Y;
    }
  }
  return X;
}



int main() {
  int k;
  long int s;
  float a1, b1, c1, d1, eps1, delta1;
  double a, b, eps, x;
  printf("Введите eps: ");
  scanf("%f", &eps1);
  eps = eps1;
  printf("Введите a: ");
  scanf("%f", &a1);
  a = a1;
  printf("Введите b: ");
  scanf("%f", &b1);
  b = b1;
  printf("Введите delta: ");
  scanf("%f", &delta1);
  delta = delta1;
  x = BISECT(a, b, eps, k);
  printf("x = %f  k = %d\n", x, k);
  return 0;
}
