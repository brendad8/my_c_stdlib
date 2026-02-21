#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct str
{
    size_t length;
    const char* data;

} str;

#define strl(l)        ((str){ .data = (l), .length = sizeof((l)) - 1 })
#define strp(p)        ((str){ .data = (p), .length = strlen((p)) })
#define str_fmt(s)     (int)(s).length, (s).data
#define str_isnull(s)  ((s).data == NULL)
#define str_isempty(s) (((s).data) ? (s).length == 0 : 1)


bool str_match_impl(str a, str b);
bool str_contains_impl(str s, str pattern);
bool str_starts_with_impl(str s, str prefix);
bool str_ends_with_impl(str s, str suffix);
str  str_sub_impl(str s, size_t begin, size_t end);
str  str_remove_prefix_impl(str s, str prefix);
str  str_remove_suffix_impl(str s, str suffix);

// int str_compare(str a, str b); → lexicographical compare, useful for sorting
// str_from_ptr(char* data, size_t len)
// size_t str_index_of(str s, str pattern)


int main(void) {

    str my_str = strl("hello mom!");
    printf("my_str: %.*s\n", str_fmt(my_str));

    str a = strl("Hi mom");
    str b = strl("Hi dad");
    str c = strl("Hi mom");

    return 0;
}

bool str_match_impl(str a, str b)
{
    if (!(str_isnull(a) && str_isnull(b)))
        return false;

    return a.length == b.length && memcmp(a.data, b.data, a.length) == 0;
}

bool str_contains_impl(str s, str pattern) 
{
    if (!(str_isnull(s) && str_isnull(pattern)))
        return false;

    if (s.length < pattern.length) 
        return false;

    for (size_t i = 0; i <= (s.length - pattern.length); i++)
    {
        for (size_t j = 0; j < pattern.length; j++) 
        {
            if (s.data[i+j] != pattern.data[j])
                break; 

            if (j == pattern.length-1)
                return true;
        }
    }
    return false;
}

str str_sub_impl(str s, size_t begin, size_t end)
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

bool str_starts_with_impl(str s, str prefix)
{
    if (!(str_isnull(s) && str_isnull(prefix)))
        return false;

    if (s.length < prefix.length)
        return false;

    return memcmp(s.data, prefix.data, prefix.length) == 0;
}

bool str_ends_with_impl(str s, str suffix)
{
    if (!(str_isnull(s) && str_isnull(suffix)))
        return false;
    
    if (s.length < suffix.length)
        return false;

    return memcmp(s.data + (s.length - suffix.length), suffix.data, suffix.length) == 0;
}

str str_remove_prefix_impl(str s, str prefix) 
{
    if (!(str_isnull(s)))
        return s;
    
    if (!(str_isnull(prefix)) || s.length < prefix.length)
        return s;

    if (memcmp(s.data, prefix.data, prefix.length) != 0)
        return s;
    
    return (str){ .data = s.data + prefix.length, .length = s.length - prefix.length };
}


str str_remove_suffix_impl(str s, str suffix)
{
    if (!(str_isnull(s)))
        return s;
    
    if (!(str_isnull(suffix)) || s.length < suffix.length)
        return s;

    if (memcmp(s.data + s.length - suffix.length, suffix.data, suffix.length) != 0)
        return s;
    
    return (str){ .data = s.data, .length = s.length - suffix.length };
}


