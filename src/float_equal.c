/*
`-Wfloat-equal`

This will warn when floating-point values are used in equality comparisons.

Doing so is usually considered unsafe since floating-point values are essentially
approximations to infinitely precise real numbers.

Compiling with `-Wfloat-equal` will generate a warning in both of the following cases.
*/

#include <math.h>
#include <stdio.h>

int main(void) {
    {
        /*
        Example 1:
        Two `double` variables are compared for equality.
        */
        double x = 3.14;
        double y = 3.14;
        if (x == y) {
            printf("Equal\n");
        }
    }
    {
        /*
        Example 2:
        A `double` variable is compared against a float-point literal for equality.
        */
        double x = 3.14;
        if (x == 3.14) {
            printf("Equal\n");
        }
    }
    {
        /*
        In such cases, to more reliably compare floating-point values, it is often convenient
        to check whether the absolute value of their difference is below some acceptable threshold.
        The exact tolerance would be decided upon in the context of the computations taking place.
        Here is an example using `fabs` to take the absolute value of the difference and comparing that against some small `EPSILON`:
        */
        #define EPSILON 0.00001
        double x = 3.14;
        double y = 3.14;
        if (fabs(x - y) < EPSILON) {
            printf("Equal\n");
        }
    }
    return 0;
}
