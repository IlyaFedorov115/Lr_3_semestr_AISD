#include<iostream>
#include<new>
#include<random>
#include<fstream>
using namespace std;
#define Maxint 2147483647

int MAX_NUMBER = 16384; //максимальноедлиначисла
int MAX_COUNT_BORD = 24; //максимальноеколичесво интервалов
bool GetInformation(int &NumRanDat, int* & Number, int &Xmin, int &Xmax, int &NInt, int* &LGrInt);//получениеданных
bool InsertBorder(int* &LGrInt,int cur_len,int num,int min,int max);//вставка произвольных интервалов вмассив
void GetRandomNum(int* &Number,int len,int min,int max);//генерирование случайныхчисел
void InitArray(int* &Number,int len);//заполение массива 0-ми
void PrintResult1(int* Number,int len);
void PrintResult2(int* LGrInt ,int* CountNum,int len);
extern "C"
{
	void SORTSTEP1(int Number[], intNumRanDat,int CountNumUnit1[],intXmin);
	void SORTSTEP2(int CountNumUnit1[],int lenUnit1, intLGrInt[],intCountNumN[],intNInt,intXmin);
}




void fixed(){
    cin.clear(); 
    while (cin.get() != '\n');
}


int isDigit(const char* str){
    if (((str[0] == '-' || str[0] == '+') && strlen(str)>1) || isdigit(str[0])){
       for (int i = 1; i < strlen(str) ; i++){
            if (isdigit(str[i]) == 0) return 0;
    }
    return 1;
    }
    else 
        return 0;
} 




int getInt(){
  string str; long int res;
  int result;
  while (true){
    cin >> str;
    while(!isDigit(str.c_str())){
        fixed();
        cout << "\x1b[1;31m\nОшибка!! Введите корректно:\x1b[0m " ;
        cin >> str;
    }
    res = atol(str.c_str());
   if (res>= Maxint || res <= -Maxint){
       cout << "\n\x1b[1;31mСлишком большое по модулю число \nвведите: ";
   } 
   else break;
   }
   result = atoi(str.c_str());
  return  result;
}



int main(void)
{
	int NumRanDat = 0; //количествопревдослучайныхчисел
	int *Number = NULL; //массивчисел
	int Xmin = 0; //леваяграницадиапазона
	int Xmax = 0; //правая граница диапазона
	int NInt = 0; //количество границ (не в ключай граничный значения)
	int *LGrInt = NULL; //массив левых границ
	int *CountNumUnit1 = NULL;//для интеревалов едnничной длины
	int lenUnit1 = 0;
	int* CountNumN = NULL; //для интервалов проивольной длины
	
	if(!GetInformation(NumRanDat,Number,Xmin,Xmax,NInt,LGrInt)) //получитьзначения
		return 1;
		
	PrintArray(Number,NumRanDat); //вывестислучайныечисла
	lenUnit1=Xmax-Xmin+1; //выделениепамяти
	CountNumUnit1= new int[lenUnit1];
	
	if(!CountNumUnit1){ std::cout<<"Ошибка: неудалось выделить память\n";return 1;}
	
	InitArray(CountNumUnit1,lenUnit1);
    CountNumN = newint[NInt];
	
	if(!CountNumN){std::cout<<"Ошибка: не удалось выделить память\n";return 1;}
	
	InitArray(CountNumN,NInt);

	SORTSTEP1(Number,NumRanDat,CountNumUnit1,Xmin); // распределениепоинтервалам 1
	SORTSTEP2(CountNumUnit1,lenUnit1,LGrInt,CountNumN,NInt,Xmin); //распределениепоинервалампроизвольнойдлины
	PrintResult1(CountNumUnit1,lenUnit1); //выводрезультатапервойпроцедуры
	PrintResult2(LGrInt,CountNumN,NInt); //выводрезультатавторойпроцедуры
	delete [] CountNumN;
	delete [] CountNumUnit1;
	delete [] Number;
	delete [] LGrInt;
	return 0;
    
}
	
bool GetInformation(int &NumRanDat, int* & Number, int &Xmin, int &Xmax, int& NInt, int* &LGrInt){
	int len = 0;
	int i = 0;
	string str;
	setlocale(LC_ALL, "rus");
	//получение количества чисел
	cout<<"\x1b[1;33mВведите количество случайных чисел, 0 < N < 16384:\x1b[0m ";
	cin >> NumRanDat;//

	while(NumRanDat <= 0 || NumRanDat >= 16384){	
	    fixed();
		cout<<"\x1b[1;31mОшибка: число должно быть в правильном диапазоне\x1b[0m\n" <<"\x1b[1;33m Введите количество случайных чисел: \x1b[0m";
		cin>>NumRanDat;
	}
	
	//получение диапaзона
   cout<<"\n\x1b[1;33mВведите диапазон случайных чисел:\x1b[0m \n"<<"От: ";

    Xmin = getInt();
    cout <<"\nДо :";
     Xmax = getInt();
   // Xmin = atoi(buf);
   
	while(Xmax <= Xmin){	
	    fixed();
		cout<<"\x1b[1;31mОшибка: правая граница диапaзона должна быть больше левой\x1b[0m\n"<<"Введите правую границу: ";
		Xmax = getInt();
	}
	
//}	
	
	//выделяемпамять
	 Number = new int[NumRanDat];
	if(!Number){
	    cout<<"Ошибка: неудалось выделить память\n";
	    return false;
	}
	
//////////////////////////////////////////////////////////////////////////	
	GetRandomNum(Number,NumRanDat,Xmin,Xmax);
	
	//получение количества интервалов
	cout<<"\n\x1b[1;33mВведите количество интервалов, но которые разобьется диапазон 0 < N <= 24: \x1b[0m";
	cin>>NInt;
	while(NInt<= 0 || NInt>= 25){	
	    fixed();
		cout<<"\x1b[1;31mОшибка: число должно быть в правильном диапазоне\x1b[0m\n";
		cout<<"\nВведите количество интервалов: ";
		cin>>NInt;
	}
	LGrInt = new int[NInt];        //массив левых границ
	if(!LGrInt){ 
	    cout<<"\nОшибка: неудалось выделить память\n";
	    return 0;
	}

	//получение интервалов
	cout<<"\n\x1b[1;33mВыбор интервалов.\n\x1b[0m"
		<<"\t\x1b[1;34m1\x1b[0m.Установить интервалы равномерно по диапaзону\n"
		<<"\t\x1b[1;34m2\x1b[0m.Установить интервалы самостоятельно\n";
	
	while(i == 0){	
	    cin>>i;
		switch(i){
		 case 1:
			len = Xmax-Xmin;
			for(i = 0;i < NInt; i++){
			    LGrInt[i] = Xmin+len/NInt*i;  
			}
			break;
		 case 2:
			LGrInt[0] = Xmin;
			cout<<"\nГраница 1: "<< Xmin <<"\n\n";
			for(i = 1;i < NInt; i++){
				do{
				cout << "Граница "<< i+1 <<": ";
				cin >> len;
				}while(!InsertBorder(LGrInt,i,len,Xmin,Xmax)); }
			break;
		 default:
			cout<<"\nОшибка: неверный номер операции, введите номер еще раз: ";
			i = 0;
			break;
		}
	}
	return true;
}




bool InsertBorder(int* &LGrInt,int cur_len,int num,int min,int max)
{
	if(num < min || num > max){
	    cout<<"Ошибка: число не в пределах интервала или уже задано\n";
	    return false;
	}
	int i = 0;
	int j = 0;

	while(i < cur_len){	
	    if(LGrInt[i] < num){
	        i++;
		}
		else if(LGrInt[i] == num){
		    cout<<"\nОшибка: число уже присутствует в массиве\n";
			return false;
		}
		else{
			j = i;
			j = cur_len;
			while(i < j){
				LGrInt[j] = LGrInt[j-1];
				j--;
			}
			break;
		}
	}
	LGrInt[i] = num;
	return true;
}


void GetRandomNum(int* &Number,int len,int min,int max)
{
	std::random_devicerd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<>distr(min, max);
	for(--len;len>=0;len--){
		Number[len]=distr(gen);}

}




voidInitArray(int* &Arr,intlen)
{
	for(--len;len>=0;len--){
		Arr[len]=0;}
}





void PrintResult1(int* Number,intlen)
{
	inti=0;
	std::ofstreamfout;
	fout.open("result1.txt");
	if(!fout.is_open()){ 
		std::cout<<"Error: can't open file "<<'\n';
		return ;}

	std::cout<<"Распределение случайных чисел по интервалам единичной длины:\n";
	std::cout<<"№\t Лев.гр.\tКл-во\t\n";
	fout<<"Распределение случайных чисел по инерваламеденичной длины:\n";
	fout<<"№\t Лев.гр.\tКл-во\t\n";
	for(i=0;i<len;i++)
	{
		std::cout<<i<<'\t'<<i<<"\t\t"<< Number[i] <<'\n';
		fout<<i<<'\t'<<i<<"\t\t"<< Number[i] <<'\n';
	}
	std::cout<<"-----------------------------\n";
	fout.close();
}




void PrintResult2(int* LGrInt ,int* CountNum,intlen)
{
	inti=0;
	std::ofstreamfout;
	fout.open("result2.txt");
	if(!fout.is_open()){ 
		std::cout<<"Error: can't open file "<<'\n';
		return ;}

	std::cout<<"Распределение случайных чисел по заданным интервалам:\n";
	std::cout<<"№\t Лев.гр.\tКл-во\t\n";

	fout<<"Распределение случайных чисел по инерваламеденичной длины:\n";
	fout<<"№\t Лев.гр.\tКл-во\t\n";
	for(i=0;i<len;i++){
		std::cout<<i<<'\t'<<LGrInt[i] <<"\t\t"<<CountNum[i] <<'\n';
		fout<<i<<'\t'<<LGrInt[i] <<"\t\t"<<CountNum[i] <<'\n';}
	fout.close()}
 

файл func.asm
.586p
.MODEL FLAT, C
.DATA
	offset countn dd 0 
.CODE
PUBLIC C SORTSTEP1 ;распределение по интервалам единичной длины
SORTSTEP1 PROC C Number:dword, NumRanDat:byte, CountNumUnit1:dword, Xmin:byte
	PUSH EDI  ;сохранение регистров
	PUSH ESI
	MOV EAX, DWORD PTR Xmin			;получение значение xmin
	MOV EDI, Number				;получение адреса массива случайных чисел
	MOV ESI, CountNumUnit1			;получение адреса массива счетчика чисел
	MOV ECX, DWORD PTR NumRanDat	;получение длины массива случайных чисел
cycle:
	MOV EBX,[EDI]					; получение числа
	SUB EBX,EAX						; вычесть xmin
	MOV EDX,[ESI+4*EBX]				; плучить счетчик этого числа
	INC EDX							; прибавить 1
	MOV [ESI+4*EBX],EDX				; занести  в  обратно массив
	ADD EDI,4						; переход  кслед числу
	LOOP cycle						;  повторять пока не прошли весь массив
	POP ESI ;восстановление значений регистров
	POP EDI
	RET
SORTSTEP1 ENDP

PUBLIC C SORTSTEP2 ;распределение по интервалам произвольной длины
SORTSTEP2 PROC C CountNumUnit1:dword, lenUnit1:byte, LGrInt:dword, CountNumN:dword ,NInt:byte, Xmin:byte
	PUSH EDI  ;сохранение регистров
	PUSH ESI
	MOV EDI,DWORD PTR lenUnit1		;получение указателя на последний элемент массива счечикаеденичной длины
	DEC EDI
	SHL EDI,2
	ADD EDI,CountNumUnit1
	MOV ECX,DWORD PTR lenUnit1		;поолучениесчетчика
	MOV EAX, DWORD PTR NInt	;получение указателей по последние элементы  массивов 
	DEC EAX
	SHL EAX,2
	pushedi
	MOV ESI, LGrInt
	MOV Edi, CountNumN
	ADD Edi,EAX
	ADD ESI,EAX
	MOV offsetcountn,edi
	popedi
	; опрерациипередвыполнениемцикла
	SUB EAX,EAX
	MOV EAX, dword PTR Xmin
	ADD EAX, ECX
	DEC EAX
	MOV EBX,[ESI]
cycle:
	CMP EAX,EBX
	JL falseif
	PUSH EAX
	pushesi
	movesi,offsetcountn
	MOV EDX,[Esi]
	MOV EAX,[EDI]
	ADD EDX,EAX
	MOV [Esi],EDX
	popesi
	POP EAX
	JMP endif1
falseif:
	SUB ESI,4
	SUB offsetcountn,4
	MOV EBX,[ESI]
	JMP cycle
endif1:
	DEC EAX
	SUB EDI,4
	LOOP cycle ;повторять до тех ПОР ПОКА НЕ ПРОЙДЕМ ВЕСЬ МАССИВ
	POP ESI ;восстановление значений регистров
	POP EDI
	RET
SORTSTEP2 ENDP
END
 
Пример выполнен
