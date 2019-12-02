#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <random>
using namespace std;

char alphabet[] = {'a','b', 'c','d'};

void GetRandomNum(int* &Number,int len,int min,int max, const char* output){
    
    ofstream g(output, ios::out | ios::binary);	
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>distr(min, max);
	for(--len; len >= 0; len--){
		Number[len] = distr(gen);
	}

}


//void randomText(int len, ofstream& fout) {
void randomText(int len, const char* name) {
    string s = "";
  //  fout.open("randomText.txt");
    ofstream fout(name, ios::out | ios::binary);	
    len;
    static const char alphanum[] =
              "0123456789 "
              "ABCDEFGHIJKLMNOPQRSTUVWXYZ "
              "\n"
              ".,?! "
              "abcdefghijklmnopqrstuvwxyz ";
    srand(time(0));
    for (int i = 0; i < len; i++) {
       //s.push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);
       fout << alphanum[rand() % (sizeof(alphanum) - 1)];
        
    }
   // s[len] = 0;
   // if (s.size() > 10000) cout << "Смотри случайно сгенерированный текст в файле randomText.txt\n";
    //else cout << "Случайно сгенерированный текст:\n" << s << endl;
    //fout << s;
} 





void generator(int size,const char* output) {
    ofstream g(output, ios::out | ios::binary);	
    srand(time(NULL));
    string text;
    for (int i = 0, j = 0; i < size; i++) {
        j = rand() % 10 + 1;
        
        if (j > size - i) j = size - i;
        i += j;
        for (int k = 0; k < j; k++ ) {
            g << (char)(rand() % 26 + 97);
        }
        g << ' ';
        int en = rand()%10+1;
        if (en > 9) g<< "\n";
    }
     g<<'.';
}



int main()
{
   //generator(1000, "text.txt");
   randomText(100000, "randomText.txt");
    cout<<"Hello World";

    return 0;
}
