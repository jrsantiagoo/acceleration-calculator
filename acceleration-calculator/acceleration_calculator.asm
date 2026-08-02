section .text

default rel
bits 64
global calculate_acceleration

calculate_acceleration:
	; ECX: 1st param num_cars
	; RDX: 2nd param car_matrix (address of first element)
	; R8:  3rd param car_accelerations (address of first element)
	
	xor r10, r10 ; array indexing
	xor r11d, r11d ; temp register

L1: 
	; Number of bytes between each column: 4 (single precision floating point)
	; Number of bytes between each row: 4 * 3 columns = 12
	mov eax, r10d
	imul eax, 12  
	movss xmm0, [rdx + rax + 4*0]

	mov eax, r10d
	imul eax, 4
	cvtss2si r11d, xmm0
	mov [r8 + rax], r11d

	inc r10d

	cmp r10d, ecx
	jl L1

	ret