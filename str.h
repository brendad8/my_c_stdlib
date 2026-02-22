
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
    size_t length;
    const char* data;

} str;


#define cstr(l) \
    ((str){ .data = (l), .length = sizeof((l)) - 1 })

#define str_fmt(s) \
    (int)(s).length, (s).data

#define str_isnull(s) \
    ((s).data == NULL)

#define str_isempty(s) \
    (((s).data) ? (s).length == 0 : 1)


int str_find_first(str s, str pattern);
int str_find_last(str s, str pattern);
bool str_match(str a, str b);
bool str_contains(str s, str pattern);
bool str_starts_with(str s, str prefix);
bool str_ends_with(str s, str suffix);
str  str_sub(str s, size_t begin, size_t end);
str  str_remove_prefix(str s, str prefix);
str  str_remove_suffix(str s, str suffix);
str str_pop_first_split(str* s, str split_by);

// int str_compare(str a, str b);
// str_from_ptr(char* data, size_t len);
// size_t str_index_of(str s, str pattern);


#endif /* STR_H */
