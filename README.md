LibOpenCIF
==========

A library to read the contents of CIF (Caltech Intermediate Form) files.

This library is writen in C++ using nothing more than the standard C++
components (so, no extra libs needed). This library can help the user to
read and validate the contents of a CIF file.

The latest release can be found in the SourceForge project page:

https://sourceforge.net/projects/libopencif/

The idea of this library is to be used as a building block for larger
projects, where the reading and validation of the input files can take
a lot of time.

The validation of the file is done using a finite state machine, based on
the specification of the format dating to february 11, 1980 (CIF version
2).

The result of the library, once readed the contents, is a C++ vector
containing pointers to Command instances. Since the convertion of the
values of the contents of the files (integers to float values) can be a
little bit tricky, all the values are left as integers (of long long
type, so there can be stored greater values). The conversion to float
values (if needed) is left to the user.