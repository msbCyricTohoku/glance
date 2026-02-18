# GLANCE(1)                         User Commands                        GLANCE(1)

## NAME
    glance - a high-performance directory lister

## SYNOPSIS
    glance [DIRECTORY] [OPTION]

## DESCRIPTION
    GLANCE is a minimalist, high-performance alternative to the standard 'ls' command. 
    It is designed to be faster and less cluttered, adhering strictly to the Unix 
    philosophy.

## PERFORMANCE
    Glance is optimized for speed. Below is a benchmark comparison against GNU `ls` 
    executed on `/usr/bin` (containing thousands of files).

    ![Benchmark Comparison](benchmark_result.png)
    *Fig 1. Execution time comparison (lower is better). Glance demonstrates significantly lower latency and tighter consistency.*

## INSTALLATION
    To build the program from source:

    ```bash
    $ make
    ```

## USAGE
    Run glance from the current directory or specify a path:

    ```bash
    $ ./glance            # List current directory
    $ ./glance ~/         # List home directory
    $ ./glance ~/ h       # List home directory (including hidden files)
    ```

## AUTHOR
    Written by msb.

## LICENSE
    GPLv3.

---
> "The Unix philosophy: Write programs that do one thing and do it well."
---
