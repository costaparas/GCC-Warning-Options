/*
`-Winit-self`

This warns about uninitialized variables that are initialized with themselves.

It must be used alongside `-Wuninitialized`, which is enabled by `-Wall` and `-Wextra`.

This scenario is explicitly ignored by `-Wuninitialized` by default; `-Winit-self` turns on
this check.

The following minimal example would trigger such a warning:
*/

int main(void) {
    int x = x;
    return 0;
}
