/*
`-Wmissing-prototypes`

This warns whenever a global function is defined without a previous prototype declaration.

As pointed out by GCC's own manual page, it can be used "to detect global functions that do not have a matching prototype declaration in a header file."

For example, this function:
*/
int foo(int i) {
    return i;
}
/*
would require a prototype declaration such as:
*/
int foo(int i);
/*
to prevent a warning being triggered.

This is in contrast to `-Wmissing-declarations`, which does not require the declaration to be a prototype. Hence,
*/
int foo();
/*
would not be sufficient to suppress the warning under `-Wmissing-prototypes`.
*/
int main(void) {
    return 0;
}
