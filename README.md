# cdecl - C Declarations Translator

`cdecl` translates C declarations to plain English.

Throughout the history of the C language, this program has been written many
times in different versions with varying levels of complexity and features.
This one in particular uses an algorithm developed by Peter van der Linden,
presented in his book *Expert C Programming*<sup>[1]</sup>. Writing the
program is given as an exercise in his book.

## Installing

#### On macOS with [Homebrew][brw]

    $ brew install tessarin/core/cdecl

#### Manual Installation

Run `make` to compile the program and generate the manual page. Then, move the
files to your desired and appropriate locations on your system:

    $ make
    $ mv cdecl ~/bin
    $ mv cdecl.1 ~/man/man1

## Usage

Call `cdecl` passing the declaration or write it directly in your terminal.
The program will process the declaration and exit at the end of the first
line.

    $ cdecl

For more information including the types and features recognized by the
program check the [manual][man].

## Examples

    $ cdecl
    long * const c
    c is readonly pointer to long

    $ cdecl
    int *(*fn())()
    fn is function returning pointer to function returning pointer to int

    $ cdecl
    short *(*(* const x)[3])()
    x is readonly pointer to array with size 3 of pointer to function returning pointer to short

---

<sup>[1]</sup> **Expert C Programming - Deep C Secrets**, 1st edition  
  Peter van der Linden  
  © 1994 Sun Microsystems, Inc.  
  ISBN 978-0-131-77429-2

 [brw]: https://brew.sh
 [man]: cdecl.pod
