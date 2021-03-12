/*
`-Wwrite-strings`

This gives string constants the type `const
char[length]` so that copying the address of one into a
non-`const char *` pointer produces a warning.

The theory behind enabling this warning is that it can assist
with finding at compile time, code that can try to
write into a string constant.

At the same time, it forces the programmer to always use `const` in
declarations of string literals, so can be a nuisance.

In the following case, a warning is triggered since `x` is not explicitly declared as `const`.
*/

int main(void) {
    char *x = "foobar";
    return 0;
}
