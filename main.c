/* Copyright (C) Hola 2012, 2013
 *
 * Welcome to TheCodeIL.com Challenge!
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


int const DEFAULT_BUFFER_SIZE = 1024;


// public API interface
void str_free(void *ptr);
char* str_cpy(char **dst, const char *src);
char* str_cat(char **dst, const char *src);
int str_printf(char **str, const char *format, ...);


// private helper functions, can be inline if possible
int p_str_len(const char *src) {
	if (src == NULL)
		return -1;
	char *s = (char*)src;
	while (*s != 0)
		s++;
	return s - src + 1;
}

char* p_str_cpy(const char *dst, const char *src) {
	char *d = (char*)dst, *s = (char*)src;
	while ((*d = *s) != 0) {
		d++; s++;
	}
	return d;
}

void p_assign(char **dst, char *src) {
	if (*dst != NULL)
		str_free(*dst);
	*dst = src;	
}


// public API functions
void str_free(void *ptr) {
	free(ptr);
}

char* str_cpy(char **dst, const char *src) {
	int l_str = p_str_len(src);
	if (l_str <= 0)
		return NULL;

	char *res = malloc(l_str);
	p_str_cpy(res, src);
	p_assign(dst, res);
    return *dst;
}

char* str_cat(char **dst, const char *src) {
	int l_dst = p_str_len(*dst), l_str = p_str_len(src);
	if (l_str <= 0)
		return *dst;
	else if (l_dst <= 0)
		return str_cpy(dst, src);
		
	char *res = malloc(l_dst + l_str - 1);
	char *r = p_str_cpy(res, *dst);
	p_str_cpy(r, src);
	p_assign(dst, res);
    return *dst;
}

int str_printf(char **str, const char *format, ...) {
	va_list args;
	va_start (args, format);
	char *dst = malloc(DEFAULT_BUFFER_SIZE);
	int res = vsprintf (dst, format, args);
	p_assign(str, dst);
	va_end (args);	
	return res;
}


// main
int main(int argc, char *argv[])
{
    char *s = NULL;
	str_cpy(&s, "Hola Hola");
    str_cpy(&s, s+5);
    str_cat(&s, " World");
    str_printf(&s, "%s!", s);
    puts(s); /* result: "Hola World!" */
    str_free(&s);
    return 0;
}

