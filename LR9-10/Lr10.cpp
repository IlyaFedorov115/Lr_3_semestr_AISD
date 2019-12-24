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
#include <cmath>


using namespace std;


long int fact(int N) {

	long int a = 1;

	for (int i = N; i != 0; i--) {

		a *= i;
	}

	return a;
}

double df(int r, int k, double* y) {

	if (r == 1) return y[k + 1] - y[k];

	return df(r - 1, k + 1, y) - df(r - 1, k, y);
	
}

double NFORWARD(int n, double* x, double* y, double dot) {

	int r = 0;
	double dq = (dot - x[0]) / (x[1] - x[0]);
	double q;
	double answer = y[0];

	for (r = 1; r < n; r++) {

		q = dq;

		for (int i = 1; i < r; i++) {
			q *= dq - i;
		}
		answer += (q / fact(r)) * df(r, 0, y);

	}
	return answer;
}


double NBACKWARD(int n, double* x, double* y, double dot) {


	int r = 0;
	double dq = (dot - x[n - 1]) / (x[1] - x[0]);
	double q;
	double answer = y[n - 1];

	for (r = 1; r < n; r++) {

		q = dq;

		for (int i = 1; i < r; i++) {
			q *= dq + i;
		}

		answer += (q / fact(r)) * df(r, n - r - 1, y);
	}
	return answer;
}


double STIRLING(int n, double* x, double* y, double dot) {
	double S, Q = 1, q, p1 = 1, p2 = 1, mn = 1000;
	int t, i, j, d;

	for (j = 0; j < n; j++) {
		if (fabs(x[j] - dot) < mn) {
			mn = fabs(x[j] - dot);
			d = j;
		}
	}
	q = (dot - x[d]) / (x[1] - x[0]);

	if (d > (n - d)) { t = n - d; }
	else { t = d; }
	S = y[d];
//8
		for (i = 1; i <= t; i++) {
			p1 = p2 * (2 * i - 1); p2 = p1 * 2 * i;
			S = S + (q * Q / p1) * (df(2 * i - 1, t - i, y) + df(2 * i - 1, t - i + 1, y)) / 2;
			S = S + ((q * q) * Q / p2) * df(2 * i, t - i, y);
			Q = Q * (q * q - i * i);
		}
	return S;
}





int main() {
	cout.precision(15);
	const int n = 11;
	double dots[3] = { 0.584, 0.9080, 2.5030 };
	int t;
	double answ;
	double x[n] = { 0 };
	double y[n] = { 0 };
	ifstream in("dots.txt");
	ofstream out("out.txt");
	for (int i = 0; i < n; i++) {
		in >> x[i];
		in >> y[i];
	}
	answ = STIRLING(n, x, y, dots[0]);
			cout << "Рассчитано схемой Стирлинга: " << answ << endl;
			out << "Рассчитано схемой Стирлинга: " << answ << endl;
			
	answ = STIRLING(n, x, y, dots[1]);
			cout << "Рассчитано схемой Стирлинга: " << answ << endl;
			out << "Рассчитано схемой Стирлинга: " << answ << endl;
			
			
	answ = STIRLING(n, x, y, dots[2]);
			cout << "Рассчитано схемой Стирлинга: " << answ << endl;
			out << "Рассчитано схемой Стирлинга: " << answ << endl;		
	for (int i = 0; i < 3; i++) {
		for (t = -1; t < n - 1; t++) {
			if (dots[i] < x[t + 1]) break;
		}
		if ((t >= (n - 1) / 2) && (t < (n + 1) / 2)) {
			answ = STIRLING(n, x, y, dots[i]);
			cout << "Рассчитано схемой Стирлинга: " << answ << endl;
			out << "Рассчитано схемой Стирлинга: " << answ << endl;
		}
		else if (t > n / 2) {
			answ = NBACKWARD(n, x, y, dots[i]);
			cout << "Рассчитано формулой Ньютона назад: " << answ << endl;
			out << "Рассчитано формулой Ньютона назад: " << answ << endl;
		}
		else {
			answ = NFORWARD(n, x, y, dots[i]);
			cout << "Рассчитано формулой Ньютона вперед: " << answ << endl;
			out << "Рассчитано формулой Ньютона вперед: " << answ << endl;
		}
	}
}

