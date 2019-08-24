This is a handy C algorithms and data structures library that is
designed to be shared among both the libc implementation and any
useful C software you would like to write.  Please use it as it means
that you get the code size consumed by the library for free, since it
is already used in the libc implementation.

Since this algorithms library must be functional without libc, that
means some useful functions like dynamic memory allocation are not
available.  For more advanced algorithms and data structures, see the
algos2 library.
