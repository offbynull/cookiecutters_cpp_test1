project(
        'cookiecutters_cpp_test',
        'cpp',
        version : '1.0.0',
        default_options : ['warning_level=everything', 'cpp_std=c++20']
)

# Configuration variables
# -----------------------
cc = meson.get_compiler('cpp')
dependencies = []
include_dirs = []
override_options = []
cpp_args = []
link_args = []

# Include Python dependency
# -------------------------
py = import('python')
py_installation = py.find_installation(
        pure: false,
        modules: ['numpy']
)
# NOTE: Do not add dependency to dependencies list until building the target. Some targets may not need boost.
py_dependencies = [py_installation.dependency()]
py_include_dirs = []
py_numpy_include_dir = run_command(
        py_installation.full_path(),
        ['-c', 'import numpy; print(numpy.get_include())'],
        check: true
).stdout().strip()
py_include_dirs += [include_directories(py_numpy_include_dir)]

# Include boost dependency
# ------------------------
# NOTE: Do not add dependency to dependencies list until building the target. Some targets may not need boost.
boost_static = true
boost_modules = [
        'container',
        'filesystem',
        'iostreams'
]
boost_dep = dependency(
        'boost',
        version : '=1.89.0',
        modules : boost_modules,
        static : boost_static
)


# Load source checker target
# --------------------------
source_checker = custom_target(
        'source_checker',
        command: [py_installation.full_path(), meson.current_source_dir() + '/source_checker.py'],
        output: ['unused'],
        build_always_stale: true
)

# Load doxygen target
# -------------------
dot = find_program('dot', required: true)
doxygen = find_program('doxygen', required: true)
doc_generator = custom_target(
        'doc_generator',
        command: [py_installation.full_path(), meson.current_source_dir() + '/source_doxygen_runner.py'],
        output : ['docs'],
        build_always_stale: true
)

# Configure options
# -----------------
base_cpp_args = []
base_link_args = []
base_override_options = []
base_debug_override_options = base_override_options + ['b_lto=false', 'b_ndebug=false', 'debug=true', 'cpp_debugstl=true'] # + ['optimization=0', 'buildtype=debug']
base_release_override_options = base_override_options + ['b_lto=true', 'b_ndebug=true', 'debug=false', 'cpp_debugstl=false'] # + ['optimization=3', 'buildtype=release']
cc = meson.get_compiler('cpp')
if cc.get_id() == 'gcc' or cc.get_id() == 'clang'
        # Configure base arguments for compiling / linking
        # ------------------------------------------------
        # Disable padding notification warning: Don't care about the compiler padding a struct.
        base_cpp_args += ['-Wno-padded']
        # Disable missing noexcept warning: Don't care that functions can be marked with noexcept.
        base_cpp_args += ['-Wno-noexcept']
        # Disable ignoring inline warning: When function implementations are placed inside of class definitions, it's a hint to the
        # compiler to inline the function. If it can't inline the function (or it doesn't inline it because it seems like a bad idea), it
        # puts out a -Winline warning. This only shows up when compiling at higher optimization levels.
        base_cpp_args += ['-Wno-inline']
        # Disable superfluous packing warning: When packing a struct, the compiler issues a warning if the struct is exactly the same
        # size in its packed form vs its padded form (because all members are already aligned). These warnings are being supressed because
        # the intention is for these structs to be packed, even if packing does nothing. In the future, should such a struct ever change
        # such that members are no longer aligned, the packing will ensure padding stays out.
        base_cpp_args += ['-Wno-packed']
        # Disable warnings specific to g++ extensions: These warnings are about applying extensions specific to g++. It doesn't apply to
        # portable C++ code. As such, don't care about them.
        base_cpp_args += ['-Wno-suggest-attribute=pure', '-Wno-suggest-attribute=const']
        # Unsure how to handle this, but it seems safe to ignore as this library requires a relatively new version of g++ and STL.
        base_cpp_args += ['-Wno-abi-tag']
        # Enable more robust compiler diagnostics
        base_cpp_args += ['-fconcepts-diagnostics-depth=9999', '-ftemplate-backtrace-limit=0']
        # Configure debug arguments for compiling / linking
        # ------------------------------------------------
        base_debug_cpp_args = base_cpp_args
        base_debug_link_args = base_link_args      
        # Enable standard library debugging.
        base_debug_cpp_args += ['-D_GLIBCXX_DEBUG']
        # Enable Google sanititzers.
        # DON'T USE THIS? MESON HAS b_sanitize OPTION?
        # san_args = ['-fsanitize=undefined', '-fsanitize=thread']
        # if cc.get_id() == 'clang'
        #         # Only available in clang -- doesn't really matter because I use valgrind for these.
        #         san_args += ['-fsanitize=memory']
        #         san_args += ['-fsanitize=leak']
        #         san_args += ['-fsanitize=address']
        # endif
        # debug_cpp_args += san_args
        # debug_link_args += san_args
        # Configure release arguments for compiling / linking
        # ---------------------------------------------------
        base_release_cpp_args = base_cpp_args
        base_release_link_args = base_link_args
else
        base_debug_cpp_args = base_cpp_args + []
        base_debug_link_args = base_link_args + []
        base_release_cpp_args = base_cpp_args + []
        base_release_link_args = base_link_args + []
endif
# Set configuration options based on build type
# ---------------------------------------------
buildtype = get_option('buildtype')
if buildtype in ['debug', 'debugoptimized', 'minsize']  # Meson claims these profiles all have debugging info turned on, so enable debugging features
        override_options += base_debug_override_options
        cpp_args += base_debug_cpp_args
        link_args += base_debug_link_args
elif buildtype == 'release'
        override_options += base_release_override_options
        cpp_args += base_release_cpp_args
        link_args += base_release_link_args
elif buildtype == 'plain'  # Unsure about what to do for plain - keep as-is for now.
        override_options += []
        cpp_args += []
        link_args += []
else
        error('Unknown buildtype: ' + buildtype)
endif

# Create CLI executables
# ----------------------
cli = executable(
        'cli',
        [
                'cookiecutters_cpp_test/cli/cli.cpp'  # Needs to be cpp (h/hpp files are silently ignored)
        ],
        source_checker,
        dependencies: dependencies+ [boost_dep],
        include_directories: include_dirs,
        override_options: override_options,
        cpp_args: cpp_args,
        link_args: link_args
)

# Create unittest executables
# ---------------------------
gtest = subproject('gtest')
gtest_dependency = gtest.get_variable('gtest_dep')
gmock_dependency = gtest.get_variable('gmock_dep')
gtest = executable(
        'gtest',
        [
                'cookiecutters_cpp_test/gtest/gtest-all.cpp',  # Needs to be cpp (h/hpp files are silently ignored)
                'cookiecutters_cpp_test/math/helpers_test.cpp'
        ],
        source_checker,
        dependencies: dependencies + [gtest_dependency]+ [boost_dep],
        include_directories: include_dirs,
        override_options: override_options,
        cpp_args: cpp_args,
        link_args: link_args
)
test('gtest', gtest)

# Create python extension
# -----------------------
# Include python files must be listed here for inclusion into generated Python package (py and pyi - will non-python files like JSON also work?).
py_installation.install_sources(
        [
                'cookiecutters_cpp_test/__init__.py',
                'cookiecutters_cpp_test/math/__init__.py',
                'cookiecutters_cpp_test/math/helpers.py',
                'cookiecutters_cpp_test/math/helpers_python_extension.pyi',
        ],
        preserve_path: true
)
# Compile and include python C extension

pybind11 = subproject('pybind11')
pybind11_dependency = pybind11.get_variable('pybind11_dep')
py_dependencies += [pybind11_dependency]
py_sources = [
        'cookiecutters_cpp_test/math/helpers_python_extension.cpp'  # Needs to be cpp (h/hpp files are silently ignored)
]
py_release = py_installation.extension_module(
        'helpers_python_extension',  # Must match name module name in 'cookiecutters_cpp_test/math/helpers_python_extension.h'
        py_sources,
        source_checker,
        install: true,
        subdir: 'cookiecutters_cpp_test/math',  # Must package path in 'cookiecutters_cpp_test/math/helpers_python_extension.h'
        dependencies: dependencies + py_dependencies,
        include_directories: include_dirs + py_include_dirs,
        override_options: base_release_override_options,
        cpp_args: base_release_cpp_args,
        link_args: base_release_link_args
)
# For auto-complete to work in IDEs like CLion, the target being built needs to reference the appropriate header files / libraries. Use
# this target when working on the python extension so you get full IDE support.
#
# WARNING: To prevent linker errors when building this, an "embedded" version of the python dependency is being used. Note that
#          py_dependencies already has the normal non-embedded python dependency in it, and so adding the embedded version means that the
#          python dependency is now being fed twice (once in non-embedded form and once in embedded form). This doesn't seem to be causing
#          any issues so far, but if it does remove the non-embedded version before continuing.
#
# WARNING: Note that what's being built is a *static* library. It seems that on some platforms, *shared* libraries (not static, but shared)
#          require that whatever they're linking against have PIC turned on? When boost is built as a static library, it doesn't have PIC
#          turned on, and so using static boost from a shared library seems tocause the linker to blow up. It seems b2 does provide a
#          "-pic" option but it's disabled by default when building as a static library.
#
#          Since this target isn't being used for anything other than making it easier to work in an IDE, keep it as a static library.
py_dependencies_embedded = py_dependencies + [py_installation.dependency(embed: true)]
helpers_python_extension_mock = static_library(
        'helpers_python_extension_mock',
        py_sources,
        source_checker,
        dependencies: dependencies + py_dependencies_embedded,
        include_directories: include_dirs + py_include_dirs,
        override_options: override_options,
        cpp_args: cpp_args,
        link_args: link_args
)
