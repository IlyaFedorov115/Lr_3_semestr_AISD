.586p
.MODEL FLAT, C
.DATA
	offsetcountn dd 0 
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
	mov EBX,[EDI]					; получение числа
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
	ADD EDI,CountNumUnit1           ; В edi указатель на последний элемент счетчика единичной длинны
	MOV ECX,DWORD PTR lenUnit1		;поолучениесчетчика
	MOV EAX, DWORD PTR NInt	;получение указателей по последние элементы  массивов 
	DEC EAX
	SHL EAX,2
	push edi
	MOV ESI, LGrInt
	MOV Edi, CountNumN
	ADD Edi,EAX
	ADD ESI,EAX                ; В esi указатель на последний элемент левых границ
	MOV offsetcountn,edi         ; В памяти указатель на последний элемент окончательного массива 
	pop edi
	; опрерации перед выполнением цикла
	SUB EAX,EAX
	MOV EAX, dword PTR Xmin
	ADD EAX, ECX
	DEC EAX
	MOV EBX,[ESI]               ; В еВх последний элемент левых границ
cycle:                  ; В edi указатель на последний элемент счетчика единичной длинны
	CMP EAX,EBX                 ; Сравниваем Хмакс и Левую границу
	JL falseif                   ; если меньше, то переход
	PUSH EAX
	push esi
	mov esi, offsetcountn
	MOV EDX,[Esi]
	MOV EAX,[EDI]
	ADD EDX,EAX                  ; сложили левую границу и последний счетчик единичной длины
	MOV [Esi],EDX
	pop esi
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
