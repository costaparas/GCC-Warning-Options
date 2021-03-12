/*
`-Wpadded`

This warns whenever padding is added to a structure, which can be an indication of non-optimal storage.

Simple rearrangement of the `struct` fields can potentially reduce and/or eliminate the padding.

However, it may not always be trivially possible to do so.

Consider the following contrived structure containing two `int` variables and one `double`.

Under `-Wpadded`, the code would trigger two warnings---once for having to align the `double` and once for having to align the whole structure.
*/
struct foo {
    int int1;
    double double1;
    int int2;
};

/*
The more obvious arrangement of the fields eliminates the need for padding altogether, thereby suppressing the warning.
*/
struct foo {
    int int1;
    int int2;
    double double1;
};

int main(void) {
    return 0;
}
