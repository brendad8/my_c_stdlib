
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#include "../basic.h"

typedef struct {
    i32 year;
    i32 month;
    i32 day;
} date;

static int read_ndigits(const char **s, int n) 
{
    int val = 0;
    for (int i = 0; i < n; i++) {
        if (!isdigit((*s)[0])) {
            fprintf(stderr, "Expected digit\n");
            exit(EXIT_FAILURE);
        }
        val = val * 10 + ((*s)[0] - '0');
        (*s)++;
    }
    return val;
}

i32 is_leap_year(i32 year) 
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

i32 days_in_month(i32 year, i32 month) 
{
    i32 days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (month == 2 && is_leap_year(year))
        return 29;
    return days[month - 1];
}

i32 is_valid_date(i32 year, i32 month, int day) 
{
    if (year < 1 || month < 1 || month > 12)
        return 0;
    if (day < 1 || day > days_in_month(year, month))
        return 0;
    return 1;
}

i64 date_to_julian(date d) 
{
    i32 a = (14 - d.month) / 12;
    i32 y = d.year + 4800 - a;
    i32 m = d.month + 12 * a - 3;

    return d.day + (153 * m + 2) / 5 + 365L * y +
           y / 4 - y / 100 + y / 400 - 32045;
}

date julian_to_date(long jdn) 
{
    date d;
    long a = jdn + 32044;
    long b = (4 * a + 3) / 146097;
    long c = a - (146097 * b) / 4;

    long d1 = (4 * c + 3) / 1461;
    long e = c - (1461 * d1) / 4;
    long m = (5 * e + 2) / 153;

    d.day = e - (153 * m + 2) / 5 + 1;
    d.month = m + 3 - 12 * (m / 10);
    d.year = 100 * b + d1 - 4800 + m / 10;

    return d;
}

date date_new(i32 year, i32 month, i32 day) 
{
    if (!is_valid_date(year, month, day)) {
        fprintf(stderr, "Invalid date: %d-%02d-%02d\n", year, month, day);
        exit(EXIT_FAILURE);
    }

    date d;
    d.year = year;
    d.month = month;
    d.day = day;
    return d;
}

date date_add_days(date d, i32 num_days) 
{
    long jdn = date_to_julian(d);
    jdn += num_days;
    return julian_to_date(jdn);
}

date date_add_weeks(date d, i32 num_weeks) 
{
    return date_add_days(d, num_weeks*7);
}

i64 date_diff(date d1, date d2) 
{
    long jdn1 = date_to_julian(d1);
    long jdn2 = date_to_julian(d2);
    return jdn2 - jdn1;
}

// date str_to_date(const char *str, const char *fmt) {
//     int year = -1, month = -1, day = -1;
//
//     while (*fmt && *str) {
//         if (*fmt == '%') {
//             fmt++;
//             switch (*fmt) {
//                 case 'Y':
//                     year = read_ndigits(&str, 4);
//                     break;
//                 case 'y': {
//                     int y2 = read_ndigits(&str, 2);
//                     year = (y2 <= 68) ? (2000 + y2) : (1900 + y2);
//                     break;
//                 }
//                 case 'm':
//                     month = read_ndigits(&str, 2);
//                     break;
//                 case 'd':
//                     day = read_ndigits(&str, 2);
//                     break;
//                 default:
//                     fprintf(stderr, "Unsupported format specifier: %%%c\n", *fmt);
//                     exit(EXIT_FAILURE);
//             }
//         } else {
//             /* Literal character must match */
//             if (*fmt != *str) {
//                 fprintf(stderr, "Format mismatch at '%c'\n", *str);
//                 exit(EXIT_FAILURE);
//             }
//             str++;
//         }
//         fmt++;
//     }
//
//     if (*fmt || *str) {
//         fprintf(stderr, "Extra characters in input\n");
//         exit(EXIT_FAILURE);
//     }
//
//     if (year == -1 || month == -1 || day == -1) {
//         fprintf(stderr, "Incomplete date\n");
//         exit(EXIT_FAILURE);
//     }
//
//     return date_new(year, month, day);
// }

i32 main() 
{
    date d1 = date_new(2024, 3, 1);
    date d2 = date_add_days(d1, 30);

    printf("Original date: %04d-%02d-%02d\n", d1.year, d1.month, d1.day);
    printf("After 30 days: %04d-%02d-%02d\n", d2.year, d2.month, d2.day);

    date d3 = date_new(2024, 4, 15);
    long diff = date_diff(d1, d3);

    printf("Days between %04d-%02d-%02d and %04d-%02d-%02d: %ld days\n",
           d1.year, d1.month, d1.day,
           d3.year, d3.month, d3.day,
           diff);

    date d4 = str_to_date("2024-03-01", "%Y-%m-%d");
    date d5 = str_to_date("15/04/24", "%d/%m/%y");

    printf("%04d-%02d-%02d\n", d4.year, d4.month, d4.day);
    printf("%04d-%02d-%02d\n", d5.year, d5.month, d5.day);

    return 0;
}
