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
     
    
double HORDA(double Left, double Right, double Eps, int &N,double delta) {
      double FLeft = F(Left,delta);
      double FRight = F(Right,delta);
      double X, Y;
     
      if (FLeft * FRight > 0.0) {
        puts("Неверное задание интервала\n");
        exit(1);
      }
     
      if (Eps <= 0.0) {
        puts("Неверное задание точности\n");
        exit(1);
      }
     
      N = 0;
      
      if (FLeft == 0.0) {
        return Left;
      }
     
      if (FRight == 0.0) {
        return Right;
      }
     
      do {
        X = Left - (Right - Left) * FLeft / (FRight - FLeft);
        fprintf(pFile,"\n %d) x[%d] = %f",N+1,N,X);
        Y = F(X,delta);
         fprintf(pFile," f(x[%d]) = %f",N,Y);
        if (Y == 0.0) {
          return X;
        }
     
        if (Y * FLeft < 0.0) {
          Right = X;
          FRight = Y;
        } else {
          Left = X;
          FLeft = Y;
        }
     
        N++;
       // printf("\n x[%d] = %f",N,X);
      } while (fabs(Y) >= Eps);
     
      return X;
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
