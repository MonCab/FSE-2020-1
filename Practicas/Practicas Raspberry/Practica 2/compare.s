@Seccion de codigo
	.text
	.global _start

_start:
	mov	r3,#4
	mov	r4,#5
	mov	r7,#4		@Syscall para escritura
	mov	r0,#1		@stdout
	cmp     r3,r4
	beq	case_equal
	blt	case_lower
	bgt	case_grater
	ldr	r1,=message_4
	b	end

case_grater:	
	ldr	r1,=message
	b 	end

case_lower:
	ldr 	r1,=message_2
	b	end

case_equal:
	ldr	r1,=message_3
	b	end

end:
	mov 	r2,#14		@Tamaño de la impresion
	svc	#0		@El procesador entra en modo supervisor
	mov	r7,#1		@r7 <- 1 Salida del programa
	mov	r0,#0		@status <- 0
	svc	#0		@El procesador entra en modo supervisor	
@Seccion de datos	
	.data

message:
       .ascii "\nr1 > r2\n\n"

message_2:
       .ascii "\nr1 < r2\n\n"

message_3:
       .ascii "\nSon iguales\n\n"

message_4:
	.ascii "\nNo se pudo\n\n"

	



