#include "my_string.h"

void array_copy(char* dst, const char* src)
{
	__asm {
		mov esi, [ebp+12]
		mov edi, [ebp+8]

	copy_loop:
		mov al, BYTE PTR[esi]
		cmp al, 0
		je exit

		mov BYTE PTR[edi], al
		
		inc esi
		inc edi
		jmp copy_loop

	exit:
		mov BYTE PTR[edi], 0
	}
}

void array_n_copy(char* dst, const char* src, int count)
{
	__asm {
		mov esi, [ebp+12]
		mov edi, [ebp+8]
		mov ecx, [ebp+16]

		rep movsb

		mov [edi], 0
	}
}

int str_cmp(const char* str0, const char* str1)
{
	__asm {
		mov esi, [ebp+8]
		mov edi, [ebp+12]

	cmp_loop:
		lodsb
		cmp al, 0
		je exit

		cmp al, [edi]
		jne exit

		inc edi
		jmp cmp_loop

	exit:
		xor eax, eax

		mov al, BYTE PTR[esi]
		sub al, BYTE PTR[edi]
	}
}

int str_n_cmp(const char* str0, const char* str1, int count)
{
	__asm {
		mov esi, [ebp+8]
		mov edi, [ebp+12]
		mov ecx, [ebp+16]

		xor eax, eax

		repe cmpsb
		jne not_same
		jmp exit

	not_same:
		dec esi
		dec edi

		mov eax, [esi]
		sub eax, [edi]
	exit:
	}
}

int indexof(const char* str, char c)
{
	__asm {
		mov esi, [ebp+8]
		mov dl, BYTE PTR[ebp+12]
		mov al, -1

	cmp_loop:
		mov cl, BYTE PTR[esi]
		cmp cl, 0
		je exit

		cmp dl, cl
		je found

		inc esi
		jmp cmp_loop

	found:
		mov eax, esi
		mov esi, [ebp+8]
		sub eax, esi

	exit:
	}
}

int indexOfN(const char* str, char c, int count)
{
	__asm {
		mov edi, [ebp+8]
		mov al, BYTE PTR[ebp+12]
		mov ecx, [ebp+16]

		repne scasb
		jne not_found

		dec edi
		mov eax, edi
		mov edi, [ebp+8]
		sub eax, edi
		jmp exit

	not_found:
		mov eax, -1
	exit:
	}
}

int char_count(const char* src, char c)
{
	__asm {
		mov esi, [ebp+8]
		mov dl, BYTE PTR[ebp+12]
		xor eax, eax

	count_loop:
		mov cl, BYTE PTR[esi]
		cmp cl, 0
		je exit

		cmp cl, dl
		jne inc_count

		inc eax

	inc_count:
		inc esi
		jmp count_loop

	exit:
	}
}

void reverse_str(char* str, int count)
{
	__asm {
		mov esi, [ebp+8]
		mov edi, [ebp+8]
		mov ecx, [ebp+12]

		add edi, ecx
		dec edi

		shr ecx, 1

	xchg_loop:
		mov al, [esi]
		xchg al, [edi]
		xchg al, [esi]

		inc esi
		dec edi
		loop xchg_loop
	}
}