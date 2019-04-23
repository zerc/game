# INSTALL (Windows)

1. https://mingw-w64.org/doku.php (Install to the path without spaces e.g. E:\mingw\ and add its bin folder to your PATH - helps avoid a lot of shit)
2. https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php (select mingw-makefiles), change prefix and other settings. Use mingw32-make.exe to build
3. Do not forget to include freshly built files to something where the compile and linker could find it e.g. I've added those folders manually via "-L" and "-I" flags
4. During the build do not forget to link against libs you are using: https://www.sfml-dev.org/faq.php#build-link