#ifndef MY_STRING_H
#define MY_STRING_H

void array_copy(char* dst, const char* src);

void array_n_copy(char* dst, const char* src, int count);

int str_cmp(const char* str0, const char* str1);

int str_n_cmp(const char* str0, const char* str1, int count);

int indexof(const char* str, char c);

int indexOfN(const char* str, char c, int count);

int char_count(const char* src, char c);

void reverse_str(const char* str, int count);

#endif /* MY_STRING_H*/