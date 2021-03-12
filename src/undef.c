/*
`-Wundef`

This warns if an undefined identifier is evaluated in a `#if`
directive. Such identifiers are replaced with zero.

A warning about an undefined identifier could likely point to a typo
or other problem with the code, as in the following case.
*/
#define M 42

#if N

#endif

/*
If the intention is to check whether the identifier is defined, then it should be
explicitly checked using the `defined` operator, as shown here.
*/
#if defined N

#endif

int main(void) {
    return 0;
}
