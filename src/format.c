/*
`-Wformat=2`

The `-Wformat` family of warning options warn about malformed arguments to
formatted input and output functions, such as `printf` and `scanf`.

The `-Wall` option enables only `-Wformat=1`.

Additional safety checks are performed by `-Wformat=2`.

These additional checks are more aggressive, and can help identify
code that may pose a security vulnerability.

One such example is passing a variable as the format string.

If the variable is initialized from an untrusted source, and is maliciously crafted,
it may crash the program, or be used to launch a [format string attack](https://owasp.org/www-community/attacks/Format_string_attack).

In the following example, the format string is a variable containing sequential `%s` format specifiers.

On some systems, this will cause the program to crash (simply add more `%s` to the format string if it doesn't crash).

This occurs since `printf` will attempt to interpret numbers from the stack as addresses for strings and dereference the addresses to print the contents. With enough `%s` in the format string, it is more likely that the numbers encountered are not valid addresses, leading to a crash.

A warning will be triggered by `-Wformat-security`, which is enabled in turn by `-Wformat=2`, but not `-Wformat=1`.
*/

#include <stdio.h>

int main(void) {
    char *username = "%s%s%s%s%s%s%s%s%s%s%s";
    printf(username);
    return 0;
}

/*
As at the time of writing, `-Wformat=2` is equivalent to `-Wformat -Wformat-nonliteral -Wformat-security -Wformat-y2k`.

This was changed from `-Wformat -Wformat-nonliteral -Wformat-security` as of [GCC Version 3.4](https://gcc.gnu.org/onlinedocs/gcc-3.4.0/gcc/Warning-Options.html#Warning-Options).

As at the time of writing, `-Wformat-security` is a subset of `-Wformat-nonliteral`. As such, either option is sufficient to warn about the above code. However, future releases may perform additional checks under `-Wformat-security` in comparison to `-Wformat-nonliteral`.
*/
