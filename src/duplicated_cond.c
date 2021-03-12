/*
`-Wduplicated-cond`

This warns about duplicated conditions in an `if`-`else if` chain.

Trivial cases, like the following are easily detected and can help
prevent simple typos in code.
*/

int main(void) {
    int x = 0;
    if (x == 0) {

    } else if (x == 1) {

    } else if (x == 0) {

    }
    return 0;
}
