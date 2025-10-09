# cookiecutters_cpp_test

To configure buildtype:

* `meson configure buildDir -Dbuildtype=debug`
* `meson configure buildDir -Dbuildtype=release`
* `meson configure buildDir -Dbuildtype=debugoptimized`
* `meson configure buildDir -Dbuildtype=minsize`
* `meson configure buildDir -Dbuildtype=plain`


To compile and run command-line interface:

* `meson compile -C buildDir cli`
* `./buildDir/cli`



To compile and run GUnit unittests:

* `meson compile -C buildDir gtest`
* `./buildDir/gtest`



To compile and run Python extension:

* `cd cookiecutters_cpp_test`
* `pip install .`
* `cd ..` (exit dir running the next command, otherwise python will look in current dir for cookiecutters_cpp_test)
* `python3 -c "import  cookiecutters_cpp_test.math.helpers as h; print(h.average([1,2,3,4,5]))"`
* `pip uninstall cookiecutters_cpp_test`

To build Python wheel:

* `pip install build`
* `python3 -m build --wheel` (builds wheel for the OS/arch that's running the command)
