#!/bin/sh

target=article.md
cp doc/text.txt "$target"  # main article text

# replace [...] with a [filename.c]-style list of files to substitute
# based on the warning flags listed in doc/list.txt
sed -E 's/(=.*|$)/.c]/;s/-W/[/;s/-/_/' doc/list.txt |
sed -i -e '/^\[\.\.\.\]/r /dev/stdin' -e '//d' "$target"

for file in src/*.c
do
    tmp=$(mktemp -p /tmp)
    cp "$file" "$tmp"
    file=$(echo "$file" | sed 's#.*/##')

    keep_main=1  # "discard" `main` function in most cases
    echo "$file" | grep -Eq '^(fencepost|strict_prototypes|unused_macros)\.c$' || keep_main=''

    # convert comments to markdown, add sub-headings, re-indent code, etc
    python3 code_to_markdown.py "$tmp" $keep_main

    # substitute file contents into target file
    sed -i -e "/^\[$file\]/r $tmp" -e '//d' "$target"

    rm -f "$tmp"
done

# remove empty & brace-only blocks, squeeze blank lines
perl -0pe 's/```[{}\s\R]*```//g; s/\R{2,}/\n\n/g' -i "$target"
