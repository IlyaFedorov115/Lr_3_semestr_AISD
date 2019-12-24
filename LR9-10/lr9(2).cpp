/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
# include <math.h>

# include <conio.h>
using namespace std;
const int n=11;
int n1 = 70;
double x[n]={0.0328, 0.4440, 0.9784, 1.6778, 4.1312, 4.7896, 4.8144, 5.4640, 5.5928, 6.3488, 6.3584};
double x1[70];
double y[n] = {-5.6456, -2.2113, -0.0446, 0.2889, 7.5487, 18.9187, 19.4780, 38.1016, 42.7838, 77.8960, 78.4322};
//double y1[70];

double z=2.7176;

double f(int, int);

double Interp_N() ;

double Eit(int ,int);

int main()

{
    ofstream out;
    out.open("result.txt");
    z = 0;
    for (int i = 0; i < 70; i++){
        out << Interp_N() << "\n";
        z+= 0.1;
    }
   
    getch();
return 0;
}

double f(int m, int l){
    double s;
    if (m==0) { s=y[0]; }
    else { if (m==1) { s=(y[l+1]-y[l])/(x[l+1]-x[l]); }
    else { s=(f(m-1,l+1)-f(m-1,l))/(x[l+m]-x[l]); }
}

return s;

}

double Eit(int n,int m)

{

double s;

if (n==0) {s=y[m];}

else

{ s=((z-x[m-n])*Eit(n-1,m)-(z-x[m])*Eit(n-1,m-1))/(x[m]-x[m-n]); }

return (s);

}

double Interp_N()

{

int i,j; double s,p;

s=0;

for (i=0;i<n;i++)

{

p=1;

for (j=0;j<i;j++)

{

p=p*(z-x[j]);

}

s=s+p*f(i,0);

}

return s;

}
