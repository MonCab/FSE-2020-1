@ Syscall defines
.equ SYSCALL_EXIT,     1


        .globl _start
_start:

        bl exit
        
exit:

	@ YOUR CODE HERE
	mov r0,#42
	mov r7,#SYSCALL_EXIT	@Salida es syscall 1
	swi 0x0			@Llamada al sistema
