#include "str.h"

/********************************************************************************/
bool str_match(str a, str b)
{
    if (str_isnull(a) || str_isnull(b))
        return false;

    return a.length == b.length && memcmp(a.data, b.data, a.length) == 0;
}

/********************************************************************************/
int str_find_first(str s, str pattern)
{
    if (str_isnull(s) || str_isnull(pattern))
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

/********************************************************************************/
int str_find_last(str s, str pattern)
{
    if (str_isnull(s) || str_isnull(pattern))
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

/********************************************************************************/
bool str_contains(str s, str pattern) 
{
    return str_find_first(s, pattern) != -1;
}

/********************************************************************************/
str str_sub(str s, size_t begin, size_t end)
{
    if (!str_isnull(s))
        return (str){ .data = NULL, .length = 0 };

    if (begin > end || end > s.length)
        return (str){ .data = NULL, .length = 0 };

    return (str){
        .data = s.data + begin,
        .length = end - begin
    };
}

/********************************************************************************/
bool str_starts_with(str s, str prefix)
{
    if (str_isnull(s) || str_isnull(prefix))
        return false;

    if (s.length < prefix.length)
        return false;

    return memcmp(s.data, prefix.data, prefix.length) == 0;
}

/********************************************************************************/
bool str_ends_with(str s, str suffix)
{
    if (str_isnull(s) || str_isnull(suffix))
        return false;
    
    if (s.length < suffix.length)
        return false;

    return memcmp(s.data + (s.length - suffix.length), suffix.data, suffix.length) == 0;
}

/********************************************************************************/
str str_remove_prefix(str s, str prefix) 
{
    if (str_isnull(s) || str_isnull(prefix) || s.length < prefix.length)
        return s;

    if (memcmp(s.data, prefix.data, prefix.length) != 0)
        return s;
    
    return (str){ .data = s.data + prefix.length, .length = s.length - prefix.length };
}

/********************************************************************************/
str str_remove_suffix(str s, str suffix)
{
    if (str_isnull(s) || str_isnull(suffix) || s.length < suffix.length)
        return s;

    if (memcmp(s.data + s.length - suffix.length, suffix.data, suffix.length) != 0)
        return s;
    
    return (str){ .data = s.data, .length = s.length - suffix.length };
}

/********************************************************************************/


