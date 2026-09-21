#!/usr/bin/env bash

set -e

BINARY="./branch_test"
CFLAGS="-O2 -march=native"
PATTERNS=(always alt rand)

case "${1:-}" in
    build)
        echo "Compiling branch_test.c..."
        gcc $CFLAGS -o branch_test branch_test.c
        echo "Done: $BINARY"
        ;;

    stat)
        pattern="${2:-always}"
        if [ ! -x "$BINARY" ]; then
            echo "Binary not found. run: ./run.sh build"
            exit 1
        fi
        echo "Running perf stat for pattern='$pattern' (branches, branch-misses)"
        sudo perf stat -e branches,branch-misses -- "$BINARY" "$pattern"
        ;;

    stat-all)
        if [ ! -x "$BINARY" ]; then
            echo "Binary not found.. fun ./run.sh build"
            exit 1
        fi
        for p in "${PATTERNS[@]}"; do
            echo "----- pattern: $p -----"
            sudo perf stat -e branches,branch-misses -- "$BINARY" "$p"
            echo
        done
        ;;
    *)
        printf "Usage:\n %s build\n %s stat <always|alt|rand>\n %s stat-all\n" "$0" "$0" "$0"
        exit 1
        ;;
esac

