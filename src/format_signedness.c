/*
`-Wformat-signedness`

This warns when a format string requires an unsigned argument but the argument is signed, and vice versa.

It is not enabled by `-Wformat=1` or `-Wformat=2`, and is useful to specify alongside `-Wformat=2`.

Compiling with `-Wformat-signedness` will generate such a warning for the following code:
*/

#include <stdio.h>

int main(void) {
    int x = -1;
    printf("%u", x);
    return 0;
}
