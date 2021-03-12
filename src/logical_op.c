/*
`-Wlogical-op`

This warns about suspicious uses of logical operators in expressions, and cases
where operands of a logical operator are the same.
*/

int main(void) {
    {
        /*
        Example 1:
        The comparison `x > 0` is used twice as an operand to the same logical operator.
        Such a scenario would trigger a warning, usually identifying either a redundant check or likely typo.
        */
        int x = 0;
        if (x > 0 && x > 0) {

        }
    }
    {
        /*
        Example 2:
        The logical `&&` operator is applied to a variable and a non-boolean constant.
        This would trigger a warning with `-Wlogical-op`, given that it is more likely a bitwise `&` was intended.
        */
        int x = 0;
        if (x && 0x00042) {

        }
    }
    return 0;
}
