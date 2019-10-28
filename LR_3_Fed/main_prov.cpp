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
  double a, b,eps2, x;
  eps1 = 0.1;
  double eps[11];
 
 eps[0] = 0.1;    eps[1] = 0.05;    eps[2] = 0.01;
  eps[3] = 0.005;    eps[4] = 0.001;    eps[5] = 0.0005;
   eps[6] = 0.0001;     eps[7] = 0.00005;   eps[8] = 0.00001;
    eps[9] = 0.000005;    eps[10] = 0.000001;
  a = 3.0;
  b = 4.0;
  eps2 = 0.000001;
  for (int i = 0; i<11; i++){
       delta = eps[i];
       x = BISECT(a, b, eps2, k);
       printf("\n %d) x = %f  k = %d\n  delta = %lf",i, x, k,delta);
  }

  return 0;
}
