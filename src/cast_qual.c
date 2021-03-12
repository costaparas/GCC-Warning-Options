/*
`-Wcast-qual`

This warns in two distinct cases:
* Whenever a pointer is cast so as to *remove* a type qualifier from the target type.
* When making a cast that *introduces* a type qualifier in an unsafe way.

Compiling with `-Wcast-qual` will generate such a warning in both of the following cases.
*/

#include <stdlib.h>

int main(void) {
    {
        /*
        Example 1:
        The casting of `y` to `char *` discards the `const` qualifier.
        Declaring `x` as `char *` would silence the warning.
        */
        const char *x = "x";
        char *y = (char *)x;
    }
    {
        /*
        Example 2:
        The casting of `y` to `const char **` is unsafe.
        To be safe, all intermediate pointers in cast from `char **` to `const char **` must be `const` qualified.
        If `y` is declared as `const char **` (and `x` as `const char *`), this would be safe, and the warning would be silenced.
        */
        char *x = malloc(sizeof *x);
        char **y = &x;
        const char **z = (const char **)y;
    }
    return 0;
}
