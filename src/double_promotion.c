/*
`-Wdouble-promotion`

This warns when a `float` is implicitly promoted to a `double`.

It often arises when performing computations involving floating-point literals,
which are implicitly of type `double`.

When `float` values are used in such computations, a warning would be triggered, since the entire
computation is performed using `double` values through type promotion.

Compiling with `-Wdouble-promotion` will generate such a warning for the following code:
*/

int main(void) {
    float radius = 5;
    float area = radius * radius * 3.14; // this line generates a warning
    return 0;
}

/*
Compiling alongside `-Wconversion` or `-Wfloat-conversion` would generate a warning on the same line,
since the resulting `double` from the computation would be converted back into a `float`, resulting in a possible loss of precision.

An explicit cast of the literal `3.14` as in `(float)3.14` would silence both warnings, since the computation would be performed using `float` values.
*/
