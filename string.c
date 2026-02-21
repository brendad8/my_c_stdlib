#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct str
{
    size_t length;
    char* data;

} str;

#define strc(s)        (str){.data = (s), .length = sizeof((s)) - 1}
#define str_fmt(s)     (int)(s).length, (s).data
#define str_isnull(s)  ((s).data   == NULL)
#define str_isempty(s) (((s).data) ? (s).length == 0 : 1)

bool str_match(str a, str b);
bool str_contains(str s, str pattern);
bool str_starts_with(str s, str prefix);
bool str_ends_with(str s, str suffix);
str  str_sub(str s, size_t begin, size_t end);
str  str_remove_prefix(str s, str prefix);
str  str_remove_suffix(str s, str suffix);
// int str_compare(str a, str b); → lexicographical compare, useful for sorting
// str_from_ptr(char* data, size_t len)
// size_t str_index_of(str s, str pattern)

void test_str_isnull(void);
void test_str_match(void);
void test_str_contains(void);
void test_str_sub(void);
void test_str_remove_prefix(void);
void test_str_remove_suffix(void);


int main(void) {

    str my_str = strc("hello mom!");
    printf("my_str: %.*s\n", str_fmt(my_str));

    str null_str = strc(NULL);
    printf("null_str: %.*s\n", str_fmt(null_str));

    printf("my_str is null: %d\n", str_isnull(my_str));
    printf("null_str is null: %d\n", str_isnull(null_str));
    
    printf("my_str is empty: %d\n", str_isempty(my_str));
    printf("null_str is empty: %d\n", str_isempty(null_str));


    // printf("my_str is valid: %u\n", str_isnull(my_str));
    //
    // str invalid_str = strc(NULL);
    // printf("invalid_str is valid: %u\n", str_isnull(invalid_str));
    //
    // printf("strs 'hello mom' and 'hello mom' match: %u\n", str_match(strc("hello mom"), strc("hello mom")));
    // printf("strs 'hello mom' and 'hello Mom' match: %u\n\n", str_match(strc("hello mom"), strc("hello Mom")));
    //
    // printf("example.csv starts with example: %u\n", str_starts_with(strc("example.csv"), strc("example")));
    // printf("example.csv starts with examples: %u\n", str_starts_with(strc("example.csv"), strc("examples")));
    // printf("example.csv starts with example.csvs: %u\n\n", str_starts_with(strc("example.csv"), strc("example.csvs")));
    //
    // printf("example.csv ends with .csv: %u\n", str_ends_with(strc("example.csv"), strc(".csv")));
    // printf("example.csv ends with .csvs: %u\n", str_ends_with(strc("example.csv"), strc(".csvs")));
    // printf("example.csv ends with example.csvs: %u\n\n", str_ends_with(strc("example.csv"), strc("example.csvs")));
    //
    // test_str_contains();

    return 0;
}

bool str_match(str a, str b)
{
    if (!(str_isnull(a) && str_isnull(b)))
        return false;

    return a.length == b.length && memcmp(a.data, b.data, a.length) == 0;
}

// future use KMP / Boyer–Moore
bool str_contains(str s, str pattern) 
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

bool str_starts_with(str s, str prefix)
{
    if (!(str_isnull(s) && str_isnull(prefix)))
        return false;

    if (s.length < prefix.length)
        return false;

    return memcmp(s.data, prefix.data, prefix.length) == 0;
}

bool str_ends_with(str s, str suffix)
{
    if (!(str_isnull(s) && str_isnull(suffix)))
        return false;
    
    if (s.length < suffix.length)
        return false;

    return memcmp(s.data + (s.length - suffix.length), suffix.data, suffix.length) == 0;
}

str str_remove_prefix(str s, str prefix) 
{
    if (!(str_isnull(s)))
        return s;
    
    if (!(str_isnull(prefix)) || s.length < prefix.length)
        return s;

    if (memcmp(s.data, prefix.data, prefix.length) != 0)
        return s;
    
    return (str){ .data = s.data + prefix.length, .length = s.length - prefix.length };
}


str str_remove_suffix(str s, str suffix)
{
    if (!(str_isnull(s)))
        return s;
    
    if (!(str_isnull(suffix)) || s.length < suffix.length)
        return s;

    if (memcmp(s.data + s.length - suffix.length, suffix.data, suffix.length) != 0)
        return s;
    
    return (str){ .data = s.data, .length = s.length - suffix.length };
}



void test_str_contains(void)
{
    /* basic */
    assert(str_contains(strc("hello mom"), strc("mom")) == true);
    assert(str_contains(strc("hello mom"), strc("mome")) == false);
    assert(str_contains(strc("hello mom"), strc("hello mom")) == true);
    assert(str_contains(strc("hello mom"), strc("hello mom!")) == false);

    /* partial match must NOT pass */
    assert(str_contains(strc("abcde"), strc("abcdx")) == false);
    assert(str_contains(strc("aaaaa"), strc("aaab")) == false);

    /* overlapping matches (breaks your original code) */
    assert(str_contains(strc("abababa"), strc("ababa")) == true);
    assert(str_contains(strc("aaaaa"), strc("aaa")) == true);

    /* tricky repeated-prefix cases */
    assert(str_contains(strc("susssussy"), strc("sussy")) == true);
    assert(str_contains(strc("mississippi"), strc("issip")) == true);
    assert(str_contains(strc("mississippi"), strc("issiq")) == false);

    /* single-character */
    assert(str_contains(strc("a"), strc("a")) == true);
    assert(str_contains(strc("a"), strc("b")) == false);

    /* invalid strings */
    assert(str_contains(strc(NULL), strc("a")) == false);
    assert(str_contains(strc("a"), strc(NULL)) == false);
}
