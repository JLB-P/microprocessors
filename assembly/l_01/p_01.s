;area de constantes y variables
;-------------------------
;
			area constantes, data, readonly 	;area de código de solo lectura	
DIR_SRAM 	equ	0x20000000	
;area de programaOptions for target como
;----------------
			area l_01, code, readonly 	; area de código de solo lectura
			entry
			export __main				; se exporta a startup_stm32f10x_md.s
			
;inicio del programa
;-------------------
__main
	;direccionamiento inmediato
	mov r0,#0x69		;mover 1 byte a r0
	mov r1,#0x1234		;mover 2 bytes(word) a r1
	movw r2,#0x6655		;otra manera de mover 2 bytes a r2
	ldr r3,=0x12345678	;mover 4bytes(dword) a r3
	;direccionamiento de registro
	mov r4,r3			;copia el valor de r3 en r4
	;direccionamiento de registro indirecto
	ldr r5,=DIR_SRAM	;cargar la dirección de la RAM en r5
	str r4,[r5]			;almacenar el valor que contiene r4 
						;en la dirección a donde apunta r5
	;registro de estados
	ldr r0,=0xFFFFFFFF	;carga el número máximo en r0
	mov r2,#0x55		;carga un valor cualquiera en r2
	mov r3,#0x11		;carga un valor cualquiera en r3
	adds r5,r0,#1		;al valor de r0 suma 1 y resultado en r5
	adc r6,r2,r3		;r6=r2+r3+C(acarreo)
	;registro apuntador a la pila
	push {r0,r1-r5}		;guarda el contenido de r0 y r1 a r5 en 
						;la pila de datos a partir de la dirección
						;a donde apunta SP
	pop {r7}			;Extrae un dato de la pila y lo deposita en r7
	;registro de enlace LR
	bl	sub1
	orrs r8,r8,r9
ciclo
	b ciclo				;Ciclo infinito


;subroutines
;----------------
sub1	mov r9,#32
		mov r8,#64
		bx	lr 
		; end of sub1
		
	end
;fin del programa
;----------------
		



