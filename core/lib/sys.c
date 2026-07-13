#include <stddef.h>

void *memset(void *s, int c, unsigned int n)
{
    unsigned char *p = s;

    while(n--)
    {
        *p++ = (unsigned char)c;
    }

    return s;
}


void *memcpy(void *dest, const void *src, unsigned int n)
{
    unsigned char *d = dest;
    const unsigned char *s = src;

    while(n--)
    {
        *d++ = *s++;
    }

    return dest;
}