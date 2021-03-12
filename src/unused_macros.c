/*
`-Wunused-macros`

This warns about macros defined in the main file that are unused.

What is meant by "main file" is the `.c` file in which the macro is defined.

Built-in macros, macros defined on the command line, and
macros defined in include files are not warned about.

In the following program, the constant `X` is defined, but never used.

This is not unlike the familiar `-Wall`-enabled `-Wunused-variable` option for local and static variables.
*/
#define X 42

int main(void) {
    return 0;
}
