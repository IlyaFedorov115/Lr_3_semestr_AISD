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
  s = cosh(cos(x));
 // cout << "\ns = "<< s <<"\n";
  return s;
}



/*
double P(double x, int n){
  if (n == 1) return 1.0;  ///n = 1 n == 2
  if (n == 2) return x;
  double Px;
  Px = ((2.0*n+1)/(n+1))*P(x,n-1)*x-(n/(n+1))*P(x,n-2);
  cout << "\nPx(n) = " << Px;;
  return Px;
  
}
*/




double P(double x, int n) {
	if (n == 0) {
		return 1.0;
	}
	else if (n == 1) {
		return x;
	}
	else {
		return ((2.0 * ( (double)n - 1.0) + 1.0) / ((double)n))*x*P(x, n - 1) - (((double)n - 1.0) / (double)n) * P(x, n - 2);
	}
}





double P1(double x, int n){
  double P1x;
  P1x = (n/(1.0-x*x))*(P(x,n-1)-x*P(x,n));
  //cout << "\nP1x(n) = " << P1x << " " << n;
  return P1x;
}


double NEWTON(int n, int j) {
  double Y, Y1, DX, Eps0,X;
  double m1 = 0.0,  // наименьшее значение модуля 1-ой производной
         M2 = 0.0;  // наибольшее значение модуля 2-ой производной
 
  Eps0 = 0.00001;
  
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
   //cout << "\n DX = " << DX;
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
       // cout << "\nXj " << Xj;
        //wj = (1-Xj*Xj)*(P1(Xj,n))*(P1(Xj,n))
        wj = 2/((1-Xj*Xj)*P1(Xj,n)*P1(Xj,n));
        //cout << "\n Wj " << wj;
       // wj = 2/wj;
        tj = (a+b)/2+(b-a)*Xj/2;
        res += wj*F(tj);
       // cout << "\n Res = \n" << res;
    }
    res = res*(b-a)/2;
    return res;
}




int main()
{
    cout<<"\nHello World\n";
    cout.precision(15);
    double res = GAUSS(3,0,M_PI);
    cout << "\nДля n = 3";
    cout << "\n\tres = " << res;
    cout << "\n\t delta = " << res - 3.97746326050642;
    
    
    
    res = GAUSS(5,0,M_PI);
    cout << "\nДля n = 5";
    cout << "\n\tres = " << res;
    cout << "\n\t delta = " << res - 3.97746326050642;
    
    
    
   res = GAUSS(8,0,M_PI);
    cout << "\nДля n = 8";
    cout << "\n\tres = " << res;
    cout << "\n\t delta = " << res - 3.97746326050642;
    
    res = GAUSS(10,0,M_PI);
    cout << "\nДля n = 10";
    cout << "\n\tres = " << res;
    cout << "\n\t delta = " << res - 3.97746326050642;
    
    
    res = GAUSS(12,0,M_PI);
    cout << "\nДля n = 12";
    cout << "\n\tres = " << res;
    cout << "\n\t delta = " << res - 3.97746326050642;
   //cout << GAUSS(3,0,M_PI);
    return 0; 
}
