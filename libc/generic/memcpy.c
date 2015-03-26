typedef __UINTPTR_TYPE__ size_t;

void *__franken_memcpy(void *, const void *, size_t);

void *
__franken_memcpy(void *dest, const void *src, size_t n)
{
	char *d = dest;
	const char *s = src;

	while (n--)
		*d++ = *s++;
	return dest;
}

/* compiler may generate memcpy, so if libc not linked may need it */
void *memcpy(void *, const void *, unsigned long) __attribute__ ((weak, alias ("__franken_memcpy")));
