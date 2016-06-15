#!/bin/bash
echo "Running unit tests:"

VALGRIND="valgrind --quiet --show-leak-kinds=all --show-leak-kinds=all "

for i in tests/*_tests
do
    if test -f $i
    then
		if $VALGRIND ./$i 2>> tests/tests.log
        then
            echo $i PASS
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            exit 1
        fi
    fi
done

echo ""
