/*
`-Wconversion`

This warns about implicit conversions that may alter a value.
In turn, it enables both `-Wsign-conversion` and `-Wfloat-conversion`.

For integers, `-Wsign-conversion` ensures a warning is generated if the sign of an integer may change.

For reals, `-Wfloat-conversion` ensures a warning is generated if the precision of a value may change.
*/

int main(void) {
    {
        /*
        Example 1:
        A signed value is converted into an unsigned value, triggering a warning.
        An explicit cast of the form `(unsigned int)-1` would silence the warning.
        */
        unsigned int x = -1;
    }
    {
        /*
        Example 2:
        The precision of a `double` may be reduced when converted into a `float`.
        An explicit cast like `(float)x` would silence the generated warning.
        */
        double x = 3.14;
        float y = x;
    }
    {
        /*
        Example 3:
        The conversion of a real value to an integer may alter its value.
        An explicit cast like `(int)x` would silence the generated warning.
        */
        float x = 42;
        int y = x;
    }
    /*
    Enabling `-Wconversion` *mandates* the use of an explicit cast in cases such as those above.
    This is advantageous since it *forces* the programmer to be explicit about their intention.
    */
    return 0;
}
