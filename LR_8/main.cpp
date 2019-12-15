/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <cmath>

using namespace std;


double F(double x) {
  double s;
  long S;
 
  // функция f(x)
  s = cosh(cos(x));
 /*
  if (s / delta < 0) {
    S = s / delta - 0.5;
  } else {
    S = s / delta + 0.5;
  }
//  s = S * delta;
//  s = Round(s, delta); */
  return s;
}




double P(double x, int n){
  if (n == 0) return 1.0;
  if (n == 1) return x;
  double Px;
  Px = (2*n+1)/(n+1)*P(x,n-1)*x-(n/(n+1))*P(x,n-2);
  return Px;
  
}


double P1(double x, int n){
  double P1x;
  P1x = (n/(1-x*x))*(P(x,n-1)-x*P(x,n));
  return P1x;
}


double NEWTON(int n, int j) {
  double Y, Y1, DX, Eps0,X;
  double m1 = 0.0,  // наименьшее значение модуля 1-ой производной
         M2 = 0.0;  // наибольшее значение модуля 2-ой производной
 
//  Eps0 = sqrt(2 * m1 * Eps / M2);
  Eps0 = 0.0000001;
  X = cos(M_PI*(4*j-1)/(4*n+1));
  do {
    Y = P(X,n);
 
    if (Y == 0.0) {
      return X;
    }
 
    Y1 = P1(X,n);
 
    if (Y1 == 0.0) {
      puts("Производная обратилась в ноль\n");
      exit(1);
    }
 
    DX = Y / Y1;
    X -= DX;
    //N++;
  } while (fabs(DX) > Eps0);
 
  return X;
}



double GAUSS(int n, double a, double b){
    double res = 0.0;
    double Xj;
    double wj;
    double tj;
    for (int j = 1; j <= n; j++){
        Xj = NEWTON(n,j);
        //wj = (1-Xj*Xj)*(P1(Xj,n))*(P1(Xj,n))
        wj = (1-Xj*Xj)*pow((P1(Xj,n)),2);
        wj = 2/wj;
        tj = (a+b)/2+(b-a)*Xj/2;
        res += wj*F(tj);
    }
    res = res*(b-a)/2;
    return res;
}




int main()
{
    cout<<"\nHello World";
    
    return 0;
}
