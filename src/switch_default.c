/*
`-Wswitch-default`

This warns whenever a `switch` statement does not have a `default` case.

Compiling with `-Wswitch-default` will generate such a warning for the following code:
*/

#include <stdio.h>

int main(void) {
    int i = 0;
    switch (i) {
    case 0:
        printf("Zero\n");
        break;
    case 1:
        printf("One\n");
        break;
    }
    return 0;
}
/*
This option can be "noisy", since valid code need not have a `default` case for all `switch` statements.
*/
