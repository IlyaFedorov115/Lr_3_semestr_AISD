#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>

#pragma inline

#include <math.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#include <wchar.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
using namespace std;

void fixed(){
    cin.clear(); 
    while (cin.get() != '\n');
}


int main()
{
 /*   SetConsoleCP(1251);
    SetConsoleOutputCP(1251); */
   setlocale(LC_ALL,"RUSSIAN"); 
    printf("\nВведите параметр x (радиан) для вычисления cosh(x): ");
	double x, res;
	double exp = 1.0;
	double two = 2.0;
	cin >> x; 
	while (cin.fail()){
         fixed();
         printf("\nВведите параметр x (радиан): ");
         cin >> x;
     }
   res = x;
  _asm{
         FLD1
		 FCHS                    /* TOp = -1.0   */
	     FLD x
        // FABS

     cosh_justFits:

		FLDL2E
        fmul    st(0),st(1)        //; x * log2(e)
        fld     st(0)
        FRNDINT               //; int(x * log2(e))
        fsubr   st(0),st(1)        //; fract(x * log2(e))
        fst res
		//fxch                      //////////////////////
		fabs
		 //fst res
        f2xm1                 //; 2^(fract(x * log2(e))) - 1
        fld1
        faddp  st(1), st(0)               //; 2^(fract(x * log2(e)))
        fscale                //; e^x */
		
		 FLD1
		 FDIV st(0), st(1)       /* Exp (-x) */
		 FADDP st(1), st(0)

		 FLD1
		 FLD1
		 FADDP st(1),st(0)
		 FDIVR st(0), st(1)
	     //// FSCALE                  /* cosh (x) = (exp(x) + exp(-x)) / 2 */
	     FSTP x
		 FSTP ST(0)
		 FSTP ST(0)
		// FSTP st(1)
		 jmp cosh_end

   cosh_tooBig:
        FSTP ST(0)                   /* pop two items off the stack */
        FSTP x
        jmp cosh_end
/*
  cosh is more accurately calculated by the polynomial
        (1 + x^2/2)
  when x is tiny (|x| < 2^-13).
*/
	cosh_tiny:
		 FMUL ST(0), ST(0)
		 FSCALE                  /* divide by 2  */
		 FSUBRP ST(1),ST(0)    /* +1 == - (-1) */
		 FSTP x
		 //jmp cosh_end
     cosh_end:
  }
  

     if (x == -1.0) cout << "\nпереполнение";
     printf("\nРезультат:\ncosh(%lf) = %lf", res , x);
	 printf("\nНажмите любую клавишу");
     getchar();
     
     getchar();
     
    return 0;
}
