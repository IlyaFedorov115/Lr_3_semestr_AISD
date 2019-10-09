; Учебная программа  лабораторной работы №2 по дисциплине "Архитектура компьютера"
;
;
EOL  EQU  '$'
ind  EQU   2
n1   EQU  500
n2   EQU  -50

; Стек  программы

AStack    SEGMENT  STACK
          DW 12 DUP(?)
AStack    ENDS

; Данные программы

DATA      SEGMENT

;  Директивы описания данных  5-ый вариант

mem1      Db    10
mem2      Db    6
vec1      DW    3,2,4

DATA      ENDS

; Код программы

CODE      SEGMENT
          ASSUME CS:CODE, DS:DATA, SS:AStack

; Головная процедура
Main      PROC  FAR
          push  DS
          sub   AX,AX
          push  AX
          mov   AX,DATA
          mov   DS,AX

;  ПРОВЕРКА РЕЖИМОВ АДРЕСАЦИИ НА УРОВНЕ СМЕЩЕНИЙ
;  Регистровая адресация
          mov  ax,n1
          mov  ax,mem2
          mov  bl,10
          mov  bh,15

          ret   2
Main      ENDP
CODE      ENDS
          END Main
