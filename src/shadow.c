/*
`-Wshadow`

This warns whenever a local variable or type declaration shadows
another variable, parameter, type, or whenever a built-in
function is shadowed.

In the following simple example, `x` is redeclared in a new scope,
which shadows the original definition of `x`, triggering a warning with `-Wshadow` enabled.

Though not erroneous, such code can signal a code smell. It is usually best to use a different name in the inner scope.
*/

int main(void) {
    int x = 0;
    {
        int x = 1;
    }
    return 0;
}
