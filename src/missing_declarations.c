/*
`-Wmissing-declarations`

This warns whenever a global function is defined without a previous declaration.

As pointed out by GCC's own manual page, it can be used "to detect global functions that are not declared in header files."

For example, this function:
*/
int foo(int i) {
    return i;
}
/*
would require *at least* a declaration such as:
*/
int foo();
/*
to prevent a warning being triggered.

If compiling alongside `-Wstrict-prototypes`, a *prototype declaration* such as:
*/
int foo(int i);
/*
would be necessary. But, from `-Wmissing-declaration`'s perspective, both would be acceptable declarations.
*/
int main(void) {
    return 0;
}
