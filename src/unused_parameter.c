/*
`-Wunused-parameter`

This warns whenever a function parameter is unused aside from its declaration, and is enabled by `-Wextra` but not by `-Wall`.

Such a warning would be triggered for the following function, since the parameter `a` is unused in the function body.
*/
void foo(int a) {

}
/*
This option has the drawback that perfectly valid code which contains one or more functions not using all of their parameters would fail to compile.

However, well-designed code should generally avoid this altogether, and having an unused parameter can often be a sign of a code smell. This is not unlike the other options in the "`-Wunused` family", such as `-Wunused-function` and `-Wunused-variable`---both of which *are* enabled by `-Wall`.

In any case, the GCC maintainers decided for `-Wall` not to request `-Wunused-parameter`.

Having `-Wunused-parameter` enabled is quite useful to help avoid code smells. It is also trivial to suppress the warning for specific parameters, should it become necessary.

GCC's own manual page suggests:

> To suppress this warning use the "unused" attribute.

Doing so would look like the following:
*/
void bar(__attribute__((unused)) int a) {

}
/*
This has two drawbacks:
1. It is a verbose syntax.
2. It is compiler-specific, which makes the code non-portable.

A much more obvious way to suppress the warning would be a dummy cast to a `void` type, typically done at the very beginning of the function body for readability:
*/
void foobar(int a) {
    (void)a;
}
/*
This makes the code more portable, less verbose and easier to understand.
*/

int main(void) {
    return 0;
}
