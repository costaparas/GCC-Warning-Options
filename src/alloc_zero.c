/*
`-Walloc-zero`

This warns about calls to allocation functions decorated
with attribute `alloc_size` that specify zero bytes, e.g. `malloc(0)`.

The behavior in such a case is implementation-defined and relying on
it may result in subtle portability bugs.

Compiling with `-Walloc-zero` will generate a warning on both of these lines:
*/

#include <stdlib.h>

int main(void) {
    int *x = malloc(0);
    x = realloc(x, 0);
    return 0;
}
