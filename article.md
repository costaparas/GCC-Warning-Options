# The GCC warning flags every C programmer should know about

Any C programmer who has used [GCC](https://gcc.gnu.org/) would be familiar with at least some basic compilation flags designed to help them write correct and robust code.

For decades, many have used warning options such as `-Wall`, `-Wextra` and even `-Wpedantic` to help identify trivial and not-so-trivial problems in their programs. But this isn't the full story...

GGC is very powerful, and offers a [wide range](https://gcc.gnu.org/onlinedocs/gcc/#toc-GCC-Command-Options) of compilation options. An understanding of GCC's vast range of options enables a programmer to tailor their debugging experience, customize the optimization of their code on a granular level, adjust low-level machine-specific features and a whole lot more.

But my focus will be on the [warning options](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html) that GCC provides, of which there are many. And so, to limit the scope, some of the familiar "mainstream" options will be explored only at a high-level, while the less-known ones will be given their chance to shine.

## What are the essentials?

Good C programmers would be aware of (and hopefully use) at least `-Wall` and `-Wextra`, as well as specify an appropriate level of optimization (such as `-O2` or `-O3`) to further expand the range of warnings reported.

[Optimization](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#Optimize-Options) is quite an interesting topic in its own right, and the reason its relevant for generating compiler warnings at all is made explicit in GCC's own manual page:

> The effectiveness of some warnings depends on optimizations also being enabled.

### Sidetrack on Optimization

If the importance of optimization to generating useful warnings is not clear, then consider the following very simple C program containing an obvious fencepost error.

```
// fencepost.c

int main(void) {
    int x[10];
    for (int i = 0; i <= 10; ++i) {
        x[i] = i;
    }
    return 0;
}
```

Regardless of the warning options enabled, unless the code is run through optimization, there will be absolutely no warning issued about the fencepost error.

Compiling with:

```
gcc -O2 fencepost.c
```

would generate a warning thanks to GCC's loop optimizations, which would otherwise not have been performed.

### `-Wall`, `-Wextra` and `-Werror`

The naming of `-Wall` always seemed misleading to me. It certainly does not enable "all" warnings, but rather, a large selection of useful ones. From GCC's own manual page, `-Wall` "enables all the warnings about constructions that some users consider questionable, and that are easy to avoid." So in other words, `-Wall` enables warnings which *good* programmers would consider useful in identifying likely problems in their code.

I won't delve deeper into the warnings enabled by `-Wall`, since there are quite a few, and it would be counter-productive given that many are surely accustomed to these warnings.

Meanwhile, `-Wextra` (formerly `-W`) will enable several additional warnings, not enabled by `-Wall`. For example, `-Wunused-parameter`, `-Wsign-compare`, `-Wtype-limits` and `-Wmissing-field-initializers` to name a few. Though perfectly valid code may fail to compile under `-Wextra` (the same can actually be said for `-Wall`), well-written code should generally not have a problem.

Let us explore one such warning option enabled by `-Wextra` in-depth, the well-known `-Wunused-parameter`.

### `-Wunused-parameter`

This warns whenever a function parameter is unused aside from its declaration, and is enabled by `-Wextra` but not by `-Wall`.

Such a warning would be triggered for the following function, since the parameter `a` is unused in the function body.

```
void foo(int a) {

}
```

This option has the drawback that perfectly valid code which contains one or more functions not using all of their parameters would fail to compile.

However, well-designed code should generally avoid this altogether, and having an unused parameter can often be a sign of a code smell. This is not unlike the other options in the "`-Wunused` family", such as `-Wunused-function` and `-Wunused-variable`---both of which *are* enabled by `-Wall`.

In any case, the GCC maintainers decided for `-Wall` not to request `-Wunused-parameter`.

Having `-Wunused-parameter` enabled is quite useful to help avoid code smells. It is also trivial to suppress the warning for specific parameters, should it become necessary.

GCC's own manual page suggests:

> To suppress this warning use the "unused" attribute.

Doing so would look like the following:

```
void bar(__attribute__((unused)) int a) {

}
```

This has two drawbacks:
1. It is a verbose syntax.
2. It is compiler-specific, which makes the code non-portable.

A much more obvious way to suppress the warning would be a dummy cast to a `void` type, typically done at the very beginning of the function body for readability:

```
void foobar(int a) {
    (void)a;
}
```

This makes the code more portable, less verbose and easier to understand.

I'd personally recommend `-Werror` as well. Something about turning all warnings into "errors" tends to be more convincing that something is definitely wrong. It of course has the effect of preventing a buggy binary from being created altogether. Suffice it to say, if the code can't compile under `-Wall` and `-Wextra`, then you are probably doing something very wrong.

## What if you want to be pedantic?

Somewhat more controversial is the `-Wpedantic` (equivalently, `-pedantic`) option. If portability is essential (in my opinion, this should always be the case), then so too is `-Wpedantic`. There are of course additional diagnostics reported due to `-Wpedantic`---things that simply would not be detected with `-Wall` and `-Wextra`, and this can be helpful for catching more subtle problems.

The true purpose of `-Wpedantic` has always been to issue all warnings demanded by strict ISO C. The caveat however, is that it does not guarantee strict ISO C compliance. From GCC's own manual page `-Wpedantic` "finds some non-ISO practices, but not all---only those for which ISO C *requires* a diagnostic, and some others for which diagnostics have been added."

Frequently, warnings reported by `-Wpedantic` are turned into errors under `-Werror`, but this is not always the case. As explained in GCC's own manual page, the use of `-pedantic-errors` does do this, but it "is not equivalent to `-Werror=pedantic`, since there are errors enabled by this option and not enabled by the latter and vice versa."

## Compiling against a standard

In the context of warning options, it is relevant to mention GCC's `-std=` flag for specifying a C standard. If unspecified, the *default standard used will vary* depending on the compiler's version. In [GCC Version 5](https://gcc.gnu.org/onlinedocs/gcc-5.1.0/gcc/C-Dialect-Options.html#C-Dialect-Options), the default standard used was changed from `-std=gnu90` to `-std=gnu11`. The default then changed to `-std=gnu17` with the release of [GCC Version 8](https://gcc.gnu.org/onlinedocs/gcc-8.1.0/gcc/C-Dialect-Options.html#C-Dialect-Options). Since the default may change as new standards emerge, it is therefore advisable to *always specify a standard* when compiling.

Notice also, that the default standard used by GCC is the GNU dialect of the corresponding ISO C standard. Such standards support GNU extensions, which are not ISO-conformant. Compiling with a corresponding *base standard*, such as `-std=c99` or `-std=c11` would avoid GNU extensions altogether. In particular, `-Wpedantic` and `-pedantic-errors` will use the *base standard* to determine which warnings/errors ought to be issued.

## What other warning flags exist?

Anyone who has seen GCC's manual page will be aware of its length and will have noticed the plethora of available options.

Even with all of the above-mentioned flags, not all available warnings would be triggered. On the other hand, to issue all possible warnings would probably not be particularly practical to attempt. There are indeed valid and correct C programs that would fail to compile with certain options enabled---indeed, even some well-known libraries.

However, it is worth considering some additional warning flags that GCC has to offer, and enabling them alongside those already mentioned.

After all, the primary goal of these warning flags is to help you write better programs.

What follows is an exploration of a selection of less-commonly known warning options available in GCC---those which are not enabled by any of the above-mentioned options.

Their purpose is explained, along with corresponding example(s).

### `-Walloc-zero`

This warns about calls to allocation functions decorated
with attribute `alloc_size` that specify zero bytes, e.g. `malloc(0)`.

The behavior in such a case is implementation-defined and relying on
it may result in subtle portability bugs.

Compiling with `-Walloc-zero` will generate a warning on both of these lines:

```
int *x = malloc(0);
x = realloc(x, 0);
```

### `-Wcast-qual`

This warns in two distinct cases:
* Whenever a pointer is cast so as to *remove* a type qualifier from the target type.
* When making a cast that *introduces* a type qualifier in an unsafe way.

Compiling with `-Wcast-qual` will generate such a warning in both of the following cases.

#### Example 1:

The casting of `y` to `char *` discards the `const` qualifier.
Declaring `x` as `char *` would silence the warning.

```
const char *x = "x";
char *y = (char *)x;
```

#### Example 2:

The casting of `y` to `const char **` is unsafe.
To be safe, all intermediate pointers in cast from `char **` to `const char **` must be `const` qualified.
If `y` is declared as `const char **` (and `x` as `const char *`), this would be safe, and the warning would be silenced.

```
char *x = malloc(sizeof *x);
char **y = &x;
const char **z = (const char **)y;
```

### `-Wconversion`

This warns about implicit conversions that may alter a value.
In turn, it enables both `-Wsign-conversion` and `-Wfloat-conversion`.

For integers, `-Wsign-conversion` ensures a warning is generated if the sign of an integer may change.

For reals, `-Wfloat-conversion` ensures a warning is generated if the precision of a value may change.

#### Example 1:

A signed value is converted into an unsigned value, triggering a warning.
An explicit cast of the form `(unsigned int)-1` would silence the warning.

```
unsigned int x = -1;
```

#### Example 2:

The precision of a `double` may be reduced when converted into a `float`.
An explicit cast like `(float)x` would silence the generated warning.

```
double x = 3.14;
float y = x;
```

#### Example 3:

The conversion of a real value to an integer may alter its value.
An explicit cast like `(int)x` would silence the generated warning.

```
float x = 42;
int y = x;
```

Enabling `-Wconversion` *mandates* the use of an explicit cast in cases such as those above.
This is advantageous since it *forces* the programmer to be explicit about their intention.

### `-Wdouble-promotion`

This warns when a `float` is implicitly promoted to a `double`.

It often arises when performing computations involving floating-point literals,
which are implicitly of type `double`.

When `float` values are used in such computations, a warning would be triggered, since the entire
computation is performed using `double` values through type promotion.

Compiling with `-Wdouble-promotion` will generate such a warning for the following code:

```
float radius = 5;
float area = radius * radius * 3.14; // this line generates a warning
```

Compiling alongside `-Wconversion` or `-Wfloat-conversion` would generate a warning on the same line,
since the resulting `double` from the computation would be converted back into a `float`, resulting in a possible loss of precision.

An explicit cast of the literal `3.14` as in `(float)3.14` would silence both warnings, since the computation would be performed using `float` values.

### `-Wduplicated-branches`

This warns when an `if`-`else` statement has identical branches.

No warning is generated in the case both branches have a null statement.

This option is able to detect trivial cases, like the following.
It can be effective in preventing simple typos that could cause bugs.

```
int x = 0;
if (x == 0) {
    return x;
} else {
    return x;
}
```

### `-Wduplicated-cond`

This warns about duplicated conditions in an `if`-`else if` chain.

Trivial cases, like the following are easily detected and can help
prevent simple typos in code.

```
int x = 0;
if (x == 0) {

} else if (x == 1) {

} else if (x == 0) {

}
```

### `-Wfloat-equal`

This will warn when floating-point values are used in equality comparisons.

Doing so is usually considered unsafe since floating-point values are essentially
approximations to infinitely precise real numbers.

Compiling with `-Wfloat-equal` will generate a warning in both of the following cases.

#### Example 1:

Two `double` variables are compared for equality.

```
double x = 3.14;
double y = 3.14;
if (x == y) {
    printf("Equal\n");
}
```

#### Example 2:

A `double` variable is compared against a float-point literal for equality.

```
double x = 3.14;
if (x == 3.14) {
    printf("Equal\n");
}
```

In such cases, to more reliably compare floating-point values, it is often convenient
to check whether the absolute value of their difference is below some acceptable threshold.
The exact tolerance would be decided upon in the context of the computations taking place.
Here is an example using `fabs` to take the absolute value of the difference and comparing that against some small `EPSILON`:

```
#define EPSILON 0.00001
double x = 3.14;
double y = 3.14;
if (fabs(x - y) < EPSILON) {
    printf("Equal\n");
}
```

### `-Wformat=2`

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

```
char *username = "%s%s%s%s%s%s%s%s%s%s%s";
printf(username);
```

As at the time of writing, `-Wformat=2` is equivalent to `-Wformat -Wformat-nonliteral -Wformat-security -Wformat-y2k`.

This was changed from `-Wformat -Wformat-nonliteral -Wformat-security` as of [GCC Version 3.4](https://gcc.gnu.org/onlinedocs/gcc-3.4.0/gcc/Warning-Options.html#Warning-Options).

As at the time of writing, `-Wformat-security` is a subset of `-Wformat-nonliteral`. As such, either option is sufficient to warn about the above code. However, future releases may perform additional checks under `-Wformat-security` in comparison to `-Wformat-nonliteral`.

### `-Wformat-signedness`

This warns when a format string requires an unsigned argument but the argument is signed, and vice versa.

It is not enabled by `-Wformat=1` or `-Wformat=2`, and is useful to specify alongside `-Wformat=2`.

Compiling with `-Wformat-signedness` will generate such a warning for the following code:

```
int x = -1;
printf("%u", x);
```

### `-Winit-self`

This warns about uninitialized variables that are initialized with themselves.

It must be used alongside `-Wuninitialized`, which is enabled by `-Wall` and `-Wextra`.

This scenario is explicitly ignored by `-Wuninitialized` by default; `-Winit-self` turns on
this check.

The following minimal example would trigger such a warning:

```
int x = x;
```

### `-Wlogical-op`

This warns about suspicious uses of logical operators in expressions, and cases
where operands of a logical operator are the same.

#### Example 1:

The comparison `x > 0` is used twice as an operand to the same logical operator.
Such a scenario would trigger a warning, usually identifying either a redundant check or likely typo.

```
int x = 0;
if (x > 0 && x > 0) {

}
```

#### Example 2:

The logical `&&` operator is applied to a variable and a non-boolean constant.
This would trigger a warning with `-Wlogical-op`, given that it is more likely a bitwise `&` was intended.

```
int x = 0;
if (x && 0x00042) {

}
```

### `-Wmissing-declarations`

This warns whenever a global function is defined without a previous declaration.

As pointed out by GCC's own manual page, it can be used "to detect global functions that are not declared in header files."

For example, this function:

```
int foo(int i) {
    return i;
}
```

would require *at least* a declaration such as:

```
int foo();
```

to prevent a warning being triggered.

If compiling alongside `-Wstrict-prototypes`, a *prototype declaration* such as:

```
int foo(int i);
```

would be necessary. But, from `-Wmissing-declaration`'s perspective, both would be acceptable declarations.

### `-Wmissing-prototypes`

This warns whenever a global function is defined without a previous prototype declaration.

As pointed out by GCC's own manual page, it can be used "to detect global functions that do not have a matching prototype declaration in a header file."

For example, this function:

```
int foo(int i) {
    return i;
}
```

would require a prototype declaration such as:

```
int foo(int i);
```

to prevent a warning being triggered.

This is in contrast to `-Wmissing-declarations`, which does not require the declaration to be a prototype. Hence,

```
int foo();
```

would not be sufficient to suppress the warning under `-Wmissing-prototypes`.

### `-Wpadded`

This warns whenever padding is added to a structure, which can be an indication of non-optimal storage.

Simple rearrangement of the `struct` fields can potentially reduce and/or eliminate the padding.

However, it may not always be trivially possible to do so.

Consider the following contrived structure containing two `int` variables and one `double`.

Under `-Wpadded`, the code would trigger two warnings---once for having to align the `double` and once for having to align the whole structure.

```
struct foo {
    int int1;
    double double1;
    int int2;
};
```

The more obvious arrangement of the fields eliminates the need for padding altogether, thereby suppressing the warning.

```
struct foo {
    int int1;
    int int2;
    double double1;
};
```

### `-Wshadow`

This warns whenever a local variable or type declaration shadows
another variable, parameter, type, or whenever a built-in
function is shadowed.

In the following simple example, `x` is redeclared in a new scope,
which shadows the original definition of `x`, triggering a warning with `-Wshadow` enabled.

Though not erroneous, such code can signal a code smell. It is usually best to use a different name in the inner scope.

```
int x = 0;
{
    int x = 1;
}
```

### `-Wstrict-prototypes`

This warns if a function is declared or defined without specifying the argument types.

#### Example 1:

The `main` function is defined without argument types.
In C, the `main` function shall either be `void` as in `int main(void)` or have 2 arguments as in `int main(int argc, char *argv[])`.

```
int main() {
    return 0;
}
```

#### Example 2:

The `return_number` function is defined without argument types.
It should be `void`, but without specifying this, user code can inadvertently pass arguments, as shown.

```
int return_number() {
    return 42;
}

int main(void) {
    return_number("foobar");
    return 0;
}
```

### `-Wswitch-default`

This warns whenever a `switch` statement does not have a `default` case.

Compiling with `-Wswitch-default` will generate such a warning for the following code:

```
int i = 0;
switch (i) {
case 0:
    printf("Zero\n");
    break;
case 1:
    printf("One\n");
    break;
}
```

This option can be "noisy", since valid code need not have a `default` case for all `switch` statements.

### `-Wswitch-enum`

This warns whenever a `switch` statement has an index of enumerated type and lacks a `case` for one or more of the named codes of
that enumeration.

This is distinct from the `-Wswitch` option enabled by `-Wall` in that this option will issue a warning independent of the presence of a `default` label.

To better-distinguish between these two similar options, let us consider three related examples making use of the `enum EXAMPLE` shown:

```
enum EXAMPLE {
    FOO,
    BAR,
    FOOBAR
};

enum EXAMPLE foo = FOO;
```

This `switch` would generate a warning with either option enabled, since it has neither a `case` for `FOOBAR`, nor a `default`.

```
switch (foo) {
case FOO:
    printf("foo\n");
    break;
case BAR:
    printf("bar\n");
    break;
}
```

This `switch` would generate a warning only with `-Wswitch-enum`, since the `default` case is enough to satisfy `-Wswitch`'s requirements.

```
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
```

This `switch` would not generate a warning from either option, since there is an explicit `case` for all three enumeration codes.

```
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
```

### `-Wundef`

This warns if an undefined identifier is evaluated in a `#if`
directive. Such identifiers are replaced with zero.

A warning about an undefined identifier could likely point to a typo
or other problem with the code, as in the following case.

```
#define M 42

#if N

#endif
```

If the intention is to check whether the identifier is defined, then it should be
explicitly checked using the `defined` operator, as shown here.

```
#if defined N

#endif
```

### `-Wunused-macros`

This warns about macros defined in the main file that are unused.

What is meant by "main file" is the `.c` file in which the macro is defined.

Built-in macros, macros defined on the command line, and
macros defined in include files are not warned about.

In the following program, the constant `X` is defined, but never used.

This is not unlike the familiar `-Wall`-enabled `-Wunused-variable` option for local and static variables.

```
#define X 42

int main(void) {
    return 0;
}
```

### `-Wwrite-strings`

This gives string constants the type `const
char[length]` so that copying the address of one into a
non-`const char *` pointer produces a warning.

The theory behind enabling this warning is that it can assist
with finding at compile time, code that can try to
write into a string constant.

At the same time, it forces the programmer to always use `const` in
declarations of string literals, so can be a nuisance.

In the following case, a warning is triggered since `x` is not explicitly declared as `const`.

```
char *x = "foobar";
```

---

The content on this page applies to [GCC Version 7](https://gcc.gnu.org/gcc-7/) and above. Earlier versions do not support all the mentioned options, and there may be slight variations with some of those that are supported.

---

The original sources are available on [GitHub](https://github.com/costaparas/GCC-Warning-Options).

*Please consider the environment before printing.*
