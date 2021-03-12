/*
`-Wstrict-prototypes`

This warns if a function is declared or defined without specifying the argument types.

Example 1:
The `main` function is defined without argument types.
In C, the `main` function shall either be `void` as in `int main(void)` or have 2 arguments as in `int main(int argc, char *argv[])`.
*/
int main() {
    return 0;
}

/*
Example 2:
The `return_number` function is defined without argument types.
It should be `void`, but without specifying this, user code can inadvertently pass arguments, as shown.
*/
int return_number() {
    return 42;
}

int main(void) {
    return_number("foobar");
    return 0;
}
