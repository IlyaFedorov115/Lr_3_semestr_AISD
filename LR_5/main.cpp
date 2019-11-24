#include <stdio.h>
    #include <math.h>
    #include <stdlib.h>
    #include <iostream>
    #include <conio.h>

FILE * pFile;   

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
     
     
double F(double x,double delta) {
 /* if(x < 0){
    cout << "Отрицательный x";
    exit(1);
  } */
//  extern double delta;
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
     
double PHI(double x,double delta) {
  extern double delta;
  double s;
  long S;
 
  // функция φ(x) - для метода простых итераций
  s = x;
 
  if (s / delta < 0) {
    S = s / delta - 0.5;
  } else {
    S = s / delta + 0.5;
  }
 
  s = S * delta;
  s = Round(s, delta);
  return s;
}



double ITER(double X0, double Eps, int &N,double delta) {
  extern double PHI(double);
 
  if (Eps <= 0.0) {
    puts("Неверное задание точности\n");
    exit(1);
  }
 
  double X1 = PHI(X0,delta);
  double X2 = PHI(X1,delta);
 
  for (N = 2;
       (X1 - X2) * (X1 - X2) > fabs((2 * X1 - X0 - X2) * Eps);
       N++) {
    X0 = X1;
    X1 = X2;
    X2 = PHI(X1,delta);
  }
 
  return X2;
}






int main() {
  int k;
  long int s;
  float a1, b1, c1, d1, eps1, delta1;
  double a, b,eps2, x,delta;
  eps1 = 0.1;
  double eps[11];
 pFile = fopen ("myfile.txt","w");
  eps[0] = 0.1;    eps[1] = 0.05;    eps[2] = 0.01;
  eps[3] = 0.005;    eps[4] = 0.001;    eps[5] = 0.0005;
   eps[6] = 0.0001;     eps[7] = 0.00005;   eps[8] = 0.00001;
    eps[9] = 0.000005;    eps[10] = 0.000001;
  a = 3.0;
  b = 4.0;
  delta = 0.000001;
  for (int i = 0; i<11; i++){
       eps2 = eps[i];
       fprintf(pFile,"\n==============");
       fprintf(pFile,"\n Для eps = %f ",eps2);
       x = HORDA(a, b, eps2, k,delta);
       fprintf(pFile,"\t x = %f", x);
     //  printf("\n==============");
     //  printf("\n k_%d %d) Выполнение для delta = %f   x = %f",k,i,delta,x);
     //  x = HORDA(a, b, eps2, k);
      // printf("\n %d) x = %f  k = %d\n  delta = %f",i, x, k,delta);
  }

  return 0;
}
