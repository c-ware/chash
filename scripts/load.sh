#!/bin/sh
# Process all files with m4 and output them to their respective directories.

# Process all manual pages
for manual in ./templates/doc/*.template; do
    manual_name=`basename $manual | cut -d '.' -f 1`
    upper_manual_name=`echo $manual_name | tr '[a-z]' '[A-Z]'`

    m4 $manual -I ./templates/doc/ | grep -v '^##' | sed "s/CWARE_MANUAL_NAME/$upper_manual_name/g" > ./doc/$manual_name.cware
done

# Process the Makefile
m4 ./templates/Makefile.template > ./Makefile
