#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct str
{
    char* data;
    size_t size;
} str;

void test_str_contains(void);

str strc(char* str);
void print_str(str string);
bool str_valid(str);
bool str_match(str a, str b);
bool str_contains(str src, str pattern);
str str_sub(str src, size_t begin, size_t end);
// str find_first(str src, str pattern);
// str find_last(str src, str pattern);
// str str_remove_prefix(str src, str prefix);
// str str_remove_suffix(str src, str suffix);

int main(void) {

    str my_str = strc("hello mom!");
    print_str(my_str);

    printf("my_str is valid: %u\n", str_valid(my_str));
    
    str invalid_str = strc(NULL);
    printf("invalid_str is valid: %u\n", str_valid(invalid_str));

    printf("strs 'hello mom' and 'hello mom' match: %u\n", str_match(strc("hello mom"), strc("hello mom")));
    printf("strs 'hello mom' and 'hello Mom' match: %u\n", str_match(strc("hello mom"), strc("hello Mom")));

    test_str_contains();

    return 0;
}

void print_str(str string) {
    printf(
        "str of size %zu: %s\n",
        string.size,
        string.data
    );
}

str strc(char* data)
{
    if (!data) {
        return (str){
            .data = NULL,
            .size = 0
        };
    }
    return (str){
        .data = data,
        .size = strlen(data)
    };
}

bool str_valid(str string)
{
    return (string.data != NULL && string.size > 0);
}

bool str_match(str a, str b)
{
    if (!(str_valid(a) && str_valid(b)))
    {
        return false;
    }
    if (a.size != b.size) 
    {
        return false;
    }
    for (int i = 0; i < a.size; i++)
    {
        if (a.data[i] != b.data[i]) 
        {
            return false;
        }    
    }
    return true;
}

bool str_contains(str src, str pattern) 
{
    if (!(str_valid(src) && str_valid(pattern)))
    {
        return false;
    }
    if (src.size < pattern.size) 
    {
        return false;
    }
    for (int i = 0; i <= (src.size - pattern.size); i++)
    {
        for (int j = 0; j < pattern.size; j++) 
        {
            if (src.data[i+j] != pattern.data[j])
            {
                break; 
            }
            if (j == pattern.size-1)
            {
                return true;
            }
        }
    }
    return false;
}

str str_sub(str src, size_t begin, size_t end)
{
    if (!str_valid(src))
        return (str){ .data = NULL, .size = 0 };

    if (begin > end || end > src.size)
        return (str){ .data = NULL, .size = 0 };

    return (str){
        .data = src.data + begin,
        .size = end - begin
    };
}
// str find_first(str src, str pattern);
// str find_last(str src, str pattern);
// str str_remove_prefix(str src, str prefix);
// str str_remove_suffix(str src, str suffix);


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
