section .data
	; Divide km/h by 3.6 to get m/s
	conversion dd 3.6

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

	movss xmm1, [rdx + rax + 4*0] ; Vi
	movss xmm0, [rdx + rax + 4*1] ; Vf
	movss xmm2, [rdx + rax + 4*2] ; T

	; Vf - Vi
	subss xmm0, xmm1

	; Convert to m/s
	divss xmm0, [conversion]

	; (Vi - Vf) / T
	divss xmm0, xmm2

	; store in car_accelerations
	mov eax, r10d
	imul eax, 4

	; convert to integer
	cvtss2si r11d, xmm0
	mov [r8 + rax], r11d

	inc r10d

	cmp r10d, ecx
	jl L1

	ret