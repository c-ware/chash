#!/bin/sh
# Run tests in the tests/ directory, if one exists.
#
# $1: the debugger to run the file on

if [ ! -d tests ]; then
    echo 'check.sh: could not find tests directory'

    exit 1
fi

if [ "`find tests/ -type f -name '*.out'`" = "" ]; then
    echo 'check.sh: no tests to run'

    exit 1
fi

for test_file in tests/*.out; do
    printf "Test '%s' starting.\n" $test_file
    $1 ./$test_file
    printf "Test '%s' completed.\n" $test_file
done
