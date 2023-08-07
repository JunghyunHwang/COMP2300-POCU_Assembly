#include <stdio.h>
#include <assert.h>

void array_copy(char* dst, const char* src);
int str_cmp(const char* dst, const char* src);
int indexof(const char* str, char c);
int char_count(const char* src, char c);
void reverse_str(const char* str, int count);

#define MAX_SIZE 40

int main(void)
{
	const char reverse[] = "dloc ot tnew evol ruo dna egnahc nosaeS";
	char src[] = "Season change and our love went to cold";
	char dst[MAX_SIZE];

	array_copy(dst, src);
	assert(str_cmp(src, dst) == 0);

	assert(indexof(src, 'w') == 27);
	assert(indexof(dst, 'w') == 27);

	assert(char_count(src, 'a') == 3);
	assert(char_count(src, 'e') == 4);

	reverse_str(dst, MAX_SIZE - 1);
	assert(str_cmp(reverse, dst) == 0);

	return 0;
}

void array_copy(char* dst, const char* src)
{
	__asm {
		mov edi, [ebp+8]
		mov esi, [ebp+12]

	cpy_loop:
		cmp [esi], 0
		je exit

		mov al, BYTE PTR[esi]
		mov BYTE PTR[edi], al

		inc esi
		inc edi
		jmp cpy_loop
	exit:
		mov BYTE PTR[edi], 0
	}
}

int str_cmp(const char* str0, const char* str1)
{
	__asm {
		mov esi, [ebp+8]
		mov edi, [ebp+12]

	cmp_loop:
		cmp [esi], 0
		je exit

		mov al, [esi]
		cmp al, [edi]
		jne exit
		
		inc esi
		inc edi
		jmp cmp_loop

	exit:
		mov eax, [esi]
		sub eax, [edi]
	}
}

int indexof(const char* str, char c)
{
	__asm {
		mov esi, [ebp+8]
		mov dl, BYTE PTR[ebp+12]
		mov eax, -1

	cmp_loop:
		cmp [esi], 0
		je exit

		cmp dl, BYTE PTR[esi]
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

int char_count(const char* src, char c)
{
	__asm {
		mov esi, [ebp+8]
		mov dl, [ebp+12]
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
		mov edi, esi
		mov ecx, [ebp+12]

		add edi, ecx
		dec edi

		shr ecx, 1

	reverse_loop:
		mov al, BYTE PTR[esi]
		xchg al, BYTE PTR[edi]
		xchg al, BYTE PTR[esi]

		inc esi
		dec edi
		loop reverse_loop
	}
}
