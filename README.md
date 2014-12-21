LibOpenCIF
==========

A library to read the contents of CIF (Caltech Intermediate Form) files.

This library is writen in C++ using nothing more than the standard C++
components (so, no extra libs needed). This library can help the user to
read and validate the contents of a CIF file.

The latest release can be found in the [SourceForge] project page.

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

Version
=======

1.1.1 - 2014/12/20

* CMake: Fixed minor error in configuration.

1.1.0 - 2014/12/20

* Interface: Improved user interface.
* Documentation: Improved documentation.
* Code: Added a two-file version of the library for Microsoft Windows users.
* Examples: Added two basic examples of how to use the library.

1.0.2 - 2014/08/03

* CMake: The CMake targets where incomplete. The library header files not are beign correctly installed.
* CMake: Changed compression format, from bz2 to tar.gz.
* Documentation: Updated documentation in the doc/ folder.

1.0.1 - 2014/07/07

* General: Migration from Autotools to CMake.
* Files: Renamed "opencif" folder to "src".

1.0.0 - 2014/04/14

Tech
====

LibOpenCIF is using some open-source technology solutions to compile and work efficiently.

* [CMake] - Tool used to the compilation of the project.

Compilation
===========

Read the INSTALL file.

Dependencies
------------

- G++ (GCC) >= 4.8
- CMake >= 2.6
- Linux Kernel >= 3.0

Compiling
---------

Read the INSTALL file.

Installation
------------

Read the INSTALL file.

License
=======

GPLv3

[SourceForge]:https://sourceforge.net/projects/libopencif/
