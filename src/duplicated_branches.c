/*
`-Wduplicated-branches`

This warns when an `if`-`else` statement has identical branches.

No warning is generated in the case both branches have a null statement.

This option is able to detect trivial cases, like the following.
It can be effective in preventing simple typos that could cause bugs.
*/

int main(void) {
    int x = 0;
    if (x == 0) {
        return x;
    } else {
        return x;
    }
    return 0;
}
