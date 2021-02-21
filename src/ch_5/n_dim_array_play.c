/* <h

Sorts input strings.

/h> */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

static int month_days_table[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int i;         // iterator
int leap;      // flag to indicate leap year
int p_month;   // pointer to month for `month_day`
int p_day;     // pointer to day for `month_day`

int day_of_year(int day, int month, int year) {
// Computes the day of the year from a date.

    // Error check inputs
    if (day <= 0 || day >= 32 || month <= 0 || month >= 13 || year < 0) {
        fprintf(stderr, "The day-month-year date %i-%i-%i is not valid", \
                day, month, year);
        exit(1);
    }

    int *p_day = &day;
    leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    int *p_table = &month_days_table[leap][1];
    // Add to `day` until `month == 0`.
    while (--month) {
        *p_day += *p_table++;
    }
    return day;
}


void month_day(int year_day, int year, int *p_month, int *p_day) {
// Computes the month and the day from a year-day and a year.

    // Error check inputs
    if (year_day <= 0 || year_day >= 367 || year <= 0) {
        fprintf(stderr, "The year_day (%i) and/or year (%i) provided is not "\
                        "valid.", year_day, year);
        exit(1);
    }

    leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    int *p_table = &month_days_table[leap][1];
    *p_month = 1;
    // Decrement `year_day` until it corresponds to the date in the month.
    *p_day = year_day;
    do { 
        (++*p_month);
    } while ((*p_day -= *p_table) > (*p_table++));
}

int main() {
    
    printf("\n%i", day_of_year(29, 9, 2020));
    month_day(323, 2020, &p_month, &p_day);
    printf("\n%i/%i", p_day, p_month);

}