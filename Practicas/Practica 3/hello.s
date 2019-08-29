	.text
	.global _start

_start:
	mov	r7,#4		@r7 <- 4 Escritura para syscall
	mov	r0,#1		@r0 <- 1 LLamada a stdout
	ldr	r1,=message	@r1 <- &message direccióon de mem. con el mensaje 
	mov 	r2,#20		@r2 <- len(message) Tamaño del mensaje
	svc	#0		@El procesador entra en modo supervisor
	mov	r7,#1		@r7 <- 1 Salida del programa
	mov	r0,#0		@status <- 0
	svc	#0		@El procesador entra en modo supervisor
       
	.data			@Declarar y almacenar datos

message:
       .ascii "\nFSE2020-1 IS COOL\n\n"
