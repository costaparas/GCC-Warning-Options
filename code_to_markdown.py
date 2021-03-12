import sys

with open(sys.argv[1]) as f:
    lines = f.readlines()

keep_main = len(sys.argv) > 2

if not lines[1].startswith('//'):
    # file starts with a multi-line comment => turn next line into a sub-heading
    lines[1] = f'### {lines[1]}'
else:
    # file starts with a single-line comment => start code block straight away
    lines[0] = '```'

in_comment = False
skip_blanks = False
skipped_brace = False
in_switch = False
indent = 0
switch_indent = 0
output = []
blanks = []

for i, line in enumerate(lines):
    line = line.strip()

    # skip blank lines, `#include`s & main function + corresponding return statement when applicable
    if not keep_main and line in ('int main(void) {', 'return 0;'):
        continue
    elif skip_blanks and line.startswith('#include'):
        continue
    elif skip_blanks and line != '':
        skip_blanks = False
    elif skip_blanks:
        continue

    if line.endswith('*/'):
        # start a new code block after each multi-line comment terminates
        # skip blank lines at the start of code block & reset indentation
        in_comment = False
        output.extend(['', '```'])
        skip_blanks = True
        blanks = []
        indent = 0
    elif in_comment:
        # turn specific lines in multi-line comments into sub-headings; otherwise, copy verbatim
        if line.startswith('Example'):
            line = f'#### {line}'
            output.extend([line, ''])
        else:
            output.append(line)
    elif line.startswith('/*'):
        # terminate the previous code block when a new multi-line comment starts
        # except for the very first multi-line comment, for which there is no previous code block
        in_comment = True
        if i != 0:
            output.extend(['```', ''])
    else:
        # skip opening brace if the previous line contained a skipped closing brace
        # this eliminates blocks introduced for scoping, which are redundant for the output format
        if skipped_brace and line == '{':
            skipped_brace = False
            continue

        if line.startswith('}'):
            # reduce indent level when closing brace is encountered
            # but only if not inside a `switch` block
            if not in_switch:
                indent -= 1

            # if the indent level goes -ve, then reset and skip the current line
            # this happens either when encountering the closing brace of `main` and `keep_main` is `False`
            # or, when encountering the closing brace of a block introduced purely for scoping
            if indent == -1:
                indent = 0
                skipped_brace = True
                continue

        # handle `switch` statement indentation
        if in_switch and line.endswith(':'):
            switch_indent = 1
        elif in_switch and line.endswith('}'):
            in_switch = False
            switch_indent = 0

        # add regular indentation to line if the line is non-empty (avoids trailing whitespace)
        # offset by `switch`-specific indentation, but not on the `case` line itself
        line = ' ' * ((indent if line != '' else 0) + (switch_indent if not line.endswith(':') else 0)) * 4 + line

        # increase indent level or mark line as start of `switch` statement
        # this is used when processing the next line
        if line.endswith('{') and not line.startswith('switch'):
            indent += 1
        elif line.startswith('switch'):
            in_switch = True

        # gather blank lines & add to output on-demand
        # this avoids trailing blank lines in code blocks
        if line == '':
            blanks.append(line)
        else:
            output.extend(blanks)
            output.append(line)
            blanks = []

# if the file doesn't terminate with a multi-line comment, manually close the last code block
if lines[-1] != '*/':
    output.extend(['```', ''])

with open(sys.argv[1], 'w') as f:
    for line in output:
        f.write(f'{line}\n')
