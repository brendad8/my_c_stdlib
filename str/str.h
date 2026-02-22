
#ifndef STR_H
#define STR_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct str 
{
    const char* data;
    size_t length;

} str;


#define cstr(l) ((str){ .data = (l), .length = sizeof((l)) - 1 })
#define str_fmt(s) (int)(s).length, (s).data
#define str_empty(s) (((s).data) ? (s).length == 0 : 1)
#define str_from_ptr(ptr) ((str){ .data = ptr, .length = strlen(ptr) })

int  str_cmp(str a, str b);
int  str_find_first(str s, str pattern);
int  str_find_last(str s, str pattern);
bool str_eq(str a, str b);
bool str_contains(str s, str pattern);
bool str_starts_with(str s, str prefix);
bool str_ends_with(str s, str suffix);
str  str_sub(str s, size_t begin, size_t length);
str  str_remove_prefix(str s, str prefix);
str  str_remove_suffix(str s, str suffix);
str  str_pop_first_split(str* s, str pattern);


// str_eq(a, b)
// str_cmp(a, b) (lexicographic)
// str_find(haystack, needle)
// str_sub(str s, size_t start, size_t len)
// str_trim, str_chop_prefix, str_chop_suffix
// str_split(str s, char delim)

#ifdef STR_IMPLEMENTATION


int str_cmp(str a, str b)
{
    size_t min_length = a.length < b.length ? a.length : b.length;
    int cmp = memcmp(a.data, b.data, min_length);
    return cmp != 0 ? cmp : (int)(a.length - b.length);
}

bool str_eq(str a, str b)
{
    if (str_empty(a) || str_empty(b))
        return false;

    return a.length == b.length && memcmp(a.data, b.data, a.length) == 0;
}

int str_find_first(str s, str pattern)
{
    if (str_empty(s) || str_empty(pattern))
        return -1;

    if (s.length < pattern.length || pattern.length == 0) 
        return -1;

    for (int i = 0; i <= (s.length - pattern.length); i++)
    {
        for (int j = 0; j < pattern.length; j++) 
        {
            if (s.data[i+j] != pattern.data[j])
                break; 

            if (j == pattern.length-1)
                return i;
        }
    }
    return -1;
}

int str_find_last(str s, str pattern)
{
    if (str_empty(s) || str_empty(pattern))
        return -1;

    if (s.length < pattern.length || pattern.length == 0) 
        return -1;

    for (int i = s.length - 1; i >= pattern.length - 1; i--)
    {
        for (int j = 0; j < pattern.length; j++) 
        {
            if (s.data[i-j] != pattern.data[pattern.length - j - 1])
                break; 

            if (j == pattern.length - 1)
                return (i - pattern.length + 1);
        }
    }
    return -1;
}

bool str_contains(str s, str pattern) 
{
    return str_find_first(s, pattern) != -1;
}

str str_sub(str s, size_t begin, size_t length)
{
    if (str_empty(s))
        return s;

    if (begin > s.length - 1 || begin + length > s.length - 1)
        return (str){ .data = NULL, .length = 0 };

    return (str){.data = s.data + begin, .length = length};
}

bool str_starts_with(str s, str prefix)
{
    if (str_empty(s) || str_empty(prefix))
        return false;

    if (s.length < prefix.length)
        return false;

    return memcmp(s.data, prefix.data, prefix.length) == 0;
}

bool str_ends_with(str s, str suffix)
{
    if (str_empty(s) || str_empty(suffix))
        return false;
    
    if (s.length < suffix.length)
        return false;

    return memcmp(s.data + (s.length - suffix.length), suffix.data, suffix.length) == 0;
}

str str_remove_prefix(str s, str prefix) 
{
    if (str_empty(s) || str_empty(prefix) || s.length < prefix.length)
        return s;

    if (memcmp(s.data, prefix.data, prefix.length) != 0)
        return s;
    
    return (str){ .data = s.data + prefix.length, .length = s.length - prefix.length };
}

str str_remove_suffix(str s, str suffix)
{
    if (str_empty(s) || str_empty(suffix) || s.length < suffix.length)
        return s;

    if (memcmp(s.data + s.length - suffix.length, suffix.data, suffix.length) != 0)
        return s;
    
    return (str){ .data = s.data, .length = s.length - suffix.length };
}

str str_pop_first_split(str* s, str pattern)
{
    str res;
    int idx = str_find_first(*s, pattern);

    if (idx == -1) 
    {
        res = (str){.data = s -> data, .length = s -> length};
        s->data    = NULL;
        s->length  = 0;
    }
    else
    {
        res = (str){.data = s->data, .length = (size_t)idx};
        s->data   += idx + pattern.length;
        s->length -= idx + pattern.length;

    }
    
    return res;
}

#endif /* STR_IMPLEMENTATION */

#endif /* STR_H */
