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

using namespace std;
int n = 11;
double z = 2.7176;


double f(int m, int l, double* x, double* y){
    double s;
    if (m==0) { s=y[0]; }
    else { if (m==1) { s=(y[l+1]-y[l])/(x[l+1]-x[l]); }
    else { s=(f(m-1,l+1,x,y)-f(m-1,l,x,y))/(x[l+m]-x[l]); }
}
return s;
}

double AITKEN(int n, int m, double* x, double* y) {
	double s;

	if (n == 0) s = y[m];
	else {
		s = ((z - x[m - n]) * AITKEN(n - 1, m, x, y) - (z - x[m]) * AITKEN(n - 1, m - 1, x, y)) / (x[m] - x[m - n]);
	}

	return s;
}

double INEWTON(double* x, double* y) {
	int i, j; 
	double s, p;
	s = 0;

	for (i = 0; i < n; i++) {
		p = 1;

		for (j = 0; j < i; j++) {
			p = p * (z - x[j]);
		}
		s = s + p * f(i, 0, x, y);
	}

	return s;
}


int main() {
	double* x = new double[n];
	double* y = new double[n];
	char tmp;
	ifstream in;
	ofstream out;
	in.open("input.txt");
	cout.precision(15);

	for (int i = 0; i < n; i++) {
		in >> x[i];
	}
	for (int i = 0; i < n; i++) {
		in >> y[i];
	}
	double newton = INEWTON(x, y);
	double ait = AITKEN(11, 11, x, y);
	out << newton << endl << ait;
	cout << "\nРезультат: " << newton<< "\nРезультат: " << ait;
		
	return 0;	
}

