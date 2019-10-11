; Текст программы
;      Учебная программа N2  цикла лаб.раб. по дисциплине
;          "Организация и функционирование аппаратных и
;                программных  средств  ЭВМ"
;
;      ТЕКСТ  ПРОГРАММЫ
;.386
EOFLine  EQU  '$'         ; Определение символьной константы
a  EQU 2
B  EQU 2
I  EQU 7
K  EQU 3                         ;     "Конец строки"


; Стек  программы

AStack    SEGMENT  STACK
          DW 12 DUP(?)    ; Отводится 12 слов памяти
AStack    ENDS

; Данные программы
DATA      SEGMENT

;  Директивы описания данных

I1 DW 0
I2 DW 0
Res DW 0
DATA      ENDS

; Код программы

CODE      SEGMENT
          ASSUME CS:CODE, DS:DATA, SS:AStack

; Головная процедура
; Головная процедура
Main      PROC  FAR

          push  DS       ;\  Сохранение адреса начала PSP в стеке
          sub   AX,AX    ; > для последующего восстановления по
          push  AX       ;/команде ret, завершающей процедуру  
          
          ;записываем условие для F1 
    ;IF_f12:      
          mov AX,a       ; Заносим значение а
          sub AX,b       ; Вычитаем из а значение b
          cmp ax,0       ; Сравниваем a и b
          Jg Else_f12    ; Переход к Else_f12, (JG) если а>b 
          mov AX,i       ; ИЛИ выполняем блок для a<=b 
          shl AX,1       ; выражение f1 = 2i+7
          mov Bx,7       ;           f2 = 2(i-3)
          add AX,Bx      ; Сложение
          mov I1,AX      ; Присваиваем I1 значение Ах   
          ; f2 теперь для a<=b
		  mov bx,i
		  sub BX,3
		  shl BX,1
		  mov I2,BX
		  cmp I2,BX
		  je IF_f3       ;переход к функции f3
    Else_f12:            ; Выражение f1 = 20-4i  (a>b)
          mov AX,i       ; Выражение f2 = 3+4i
          shl AX,1       ; Умножаем на 4
		  shl AX,1
          mov BX,20
          sub BX,AX      ; Вычитаем 20-4i
          mov I1,BX      ; Присваиваем F1 значение Bх   
          
		  
		  ; ВОЗМОЖНО ФЛАГИ при ОТРИЦ числах глянуть
		  ; Теперь выражение f2 для случая (a>b)
          mov BX,3
		  add BX,AX
		  mov I2,BX      ; Заносим результат f2
          cmp BX,I2
		  je IF_f3       ; переход к F3

	IF_f3:
		  mov BX,k
		  cmp BX,0       ; проверка на k<0
		  JGE Else_f3     ; JGE если k>= 0  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		  mov BX,I1
		  cmp BX,0
		  JGE N_abs      ; если >= 0, то пропустить преобразование
		  not BX
		  add BX,1
	  N_abs:	 
	      mov AX,I2
		  cmp AX,0
		  JGE N_abs2
		  not AX
		  add AX,1
	  N_abs2:
		  sub BX,AX
		  mov Res, BX  ; КОНЕЦ блока для K>=0
          jmp My_prog		  
		  
	Else_f3:
		  mov AX,I2
		  cmp AX,0
		  JGE N_abs3
		  not AX
		  sub AX,1
	  N_abs3:
		  mov BX,7
		 ; cmp BX,AX
	 ;	  JG END_F3      ; если bx>ax
	 ;	  xchg BX,AXquit
	  ;END_F3:
	      sub bx,ax      ;вычитаю и если bx<0, то флаг CF=1
          sbb cx,cx		 ; вычитаю и вычитаю флаг
		  not cx         ;обнуляю cx если bx<0 (т.к. тогда ax > bx) 
          and cx,bx
          add ax,cx      ; в ax наибольшее
        ;  ret            ; Выход в DOS по команде,
		   mov Res,ax
          jmp My_prog               ; находящейся в 1-ом слове PSP.

    My_prog:
		;  ret 
  mov  ah,4ch                          ; # функции ДОС завершения программы
   int  21h                             ; завершение программы и выход в ДОС
	
CODE      ENDS
Main      ENDP
          END main