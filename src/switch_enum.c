/*
`-Wswitch-enum`

This warns whenever a `switch` statement has an index of enumerated type and lacks a `case` for one or more of the named codes of
that enumeration.

This is distinct from the `-Wswitch` option enabled by `-Wall` in that this option will issue a warning independent of the presence of a `default` label.

To better-distinguish between these two similar options, let us consider three related examples making use of the `enum EXAMPLE` shown:
*/

#include <stdio.h>

enum EXAMPLE {
    FOO,
    BAR,
    FOOBAR
};

int main(void) {
    enum EXAMPLE foo = FOO;

    /*
    This `switch` would generate a warning with either option enabled, since it has neither a `case` for `FOOBAR`, nor a `default`.
    */
    switch (foo) {
    case FOO:
        printf("foo\n");
        break;
    case BAR:
        printf("bar\n");
        break;
    }

    /*
    This `switch` would generate a warning only with `-Wswitch-enum`, since the `default` case is enough to satisfy `-Wswitch`'s requirements.
    */
    switch (foo) {
    case FOO:
        printf("foo\n");
        break;
    case BAR:
        printf("bar\n");
        break;
    default:
        printf("foobar\n");
        break;
    }

    /*
    This `switch` would not generate a warning from either option, since there is an explicit `case` for all three enumeration codes.
    */
    switch (foo) {
    case FOO:
        printf("foo\n");
        break;
    case BAR:
        printf("bar\n");
        break;
    case FOOBAR:
        printf("foobar\n");
        break;
    }
    return 0;
}
