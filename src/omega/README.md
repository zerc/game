# Omega

Another one graphic "engine" for academic purposes.
In this work, I attempt to explore the underlying principles of 3D-graphic as well as C++ and its ecosystem.


## INSTALL (MacOS)

1. [Download SFML](https://www.sfml-dev.org/download/sfml/2.5.1/) and follow [the instructions](https://www.sfml-dev.org/tutorials/2.5/start-osx.php#installing-sfml)
2. Install Python's virtual environment and install dependecies:

```
python3.7 -m venv venv
. venv/bin/activate
pip install -r requirements.txt
```

3. The build system is [SCons](https://scons.org/):

```
scons
```

## INSTALL (Windows)

1. https://mingw-w64.org/doku.php (Install to the path without spaces e.g. E:\mingw\ and add its bin folder to your PATH - helps avoid a lot of shit)
2. https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php (select mingw-makefiles), change prefix and other settings. Use mingw32-make.exe to build
3. Do not forget to include freshly built files to something where the compile and linker could find it e.g. I've added those folders manually via "-L" and "-I" flags
4. During the build do not forget to link against libs you are using: https://www.sfml-dev.org/faq.php#build-link


## Package manager

I use [Conan][https://conan.io/] to manage dependencies. Quick cheatsheet:

```shell
$ conan search Package* --remote-conan-center
```

If you were able to find your package add it into `conanfile.txt` then 

```shell
$ cd build
$ conan install ..
```

If everything is alright (which would be miracle) you might need to update `SConstruct` file to include whatever you installed into the build process.


## Gotchas 

### Install SFML via Conan

Need to add Bintry to the remotes:

```shell
$ conan remote add public-conan https://api.bintray.com/conan/bincrafters/public-conan 
```
