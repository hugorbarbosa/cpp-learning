# C++ development tooling

This document presents several development tools commonly utilized in a C++ software project, to enforce coding standards, improve code quality, detect defects, and generate documentation.

## Table of contents

- [Code formatting](#code-formatting)
    - [Clang-format](#clang-format)
    - [CMake-format](#cmake-format)
- [Linting](#linting)
    - [CMake-lint](#cmake-lint)
- [Static analysis](#static-analysis)
    - [Clang-tidy](#clang-tidy)
- [Runtime analysis](#runtime-analysis)
    - [Sanitizers](#sanitizers)
        - [Address sanitizer](#address-sanitizer)
        - [Leak sanitizer](#leak-sanitizer)
        - [Memory sanitizer](#memory-sanitizer)
        - [Thread sanitizer](#thread-sanitizer)
        - [Undefined behavior sanitizer](#undefined-behavior-sanitizer)
- [Documentation generation](#documentation-generation)
    - [Doxygen](#doxygen)
- [Build system](#build-system)
    - [CMake](#cmake)
    - [Bazel](#bazel)
- [Example Project](#example-project)
- [References](#references)

## Code formatting

Code formatting tools automatically enforce a consistent coding style across source code and build configuration files, improving readability and reducing formatting-related changes.

### Clang-format

Clang-format is a tool that can be used to format C++, C, C#, Java, JavaScript, JSON, Objective-C and Protobuf code. This tool can be utilized in a variety of ways, including as a standalone tool or integrated in a IDE/editor.

It allows you to directly apply a predefined code style, based on styles such as Google, Microsoft, among others. This base style can be adjusted to your needs or, if necessary, you can completely customize a style with your desired style options. All style options supported by clang-format can be found in [clang-format style options][ref-tool-clang-format-style-options].

To see an example of a clang-format configuration file, refer to the `.clang-format` file of the [C++ project template][ref-cpp-project-template], which includes the desired style options for that project, but can be used as a starting point and be adjusted to your needs.

Clang-format supports many options which can be found using the `--help` option:

```sh
$ clang-format --help
```

For example, to run clang-format on a file and apply the necessary changes:

```sh
$ clang-format --verbose -i <file>
```

To just check the file without modifying it:

```sh
$ clang-format --verbose -Werror --dry-run <file>
```

As previously mentioned, clang-format can be integrated in a IDE/editor, like Visual Studio Code. It is only necessary to install the [C/C++ extension][ref-vscode-cpp-extension], which allows configuring and using clang-format from the Visual Studio Code. Additionally, you can configure to automatically format the code when saving a file, adding `"editor.formatOnSave": true` to the `.vscode/settings.json` file of your workspace.

Please refer to the [clang-format page][ref-tool-clang-format] for more details regarding this tool.

### CMake-format

cmake-format is a tool that can be used to format CMake code.

This tool allows you to specify various options for formatting through a configuration file that can be in JSON, YAML or Python format.

To see an example of a cmake-format configuration file, refer to the `.cmake-format.py` file of the [C++ project template][ref-cpp-project-template], which includes the desired style options for that project, but can be used as starting point and be adjusted to your needs.

cmake-format supports many options which can be found using the `--help` option:

```sh
$ cmake-format --help
```

For example, to run cmake-format on a file and apply the necessary changes:

```sh
$ cmake-format -i <file>
```

To just check the file without modifying it:

```sh
$ cmake-format --check <file>
```

Please refer to the [cmake-format page][ref-tool-cmake-format] for more details regarding this tool.

## Linting

Linting tools analyze source and configuration files for style violations, common mistakes, and adherence to recommended coding practices.

### CMake-lint

cmake-lint is a tool that can be used to check CMake code problems and conventions.

This tool allows you to specify various options for linting through a configuration file that can be in JSON, YAML or Python format, and is used together with the cmake-format tool (configuration file is usually the same for both cmake-format and cmake-lint).

To see an example of a cmake-lint configuration file, refer to the `.cmake-format.py` file of the [C++ project template][ref-cpp-project-template] (the same used for cmake-format), which includes the desired options for that project, but can be used as a starting point and be adjusted to your needs.

cmake-lint supports many options which can be found using the `--help` option:

```sh
$ cmake-lint --help
```

For example, to run cmake-lint on a file:

```sh
$ cmake-lint <file>
```

Please refer to the [cmake-lint page][ref-tool-cmake-format] for more details regarding this tool.

## Static analysis

Static analysis tools examine the source code without executing it to detect potential bugs, code quality issues, and opportunities for improvement.

### Clang-tidy

Clang-tidy is a clang-based tool that provides an extensible framework for diagnosing and fixing typical programming errors, like interface misuse or bugs, that can be deduced via static analysis. It can be utilized as a standalone tool or integrated in a IDE/editor.

This tool allows you to specify various check options based on groups through a name prefix, such as `cppcoreguidelines-` that performs checks related to the C++ Core Guidelines. All check options supported by clang-tidy can be found in [clang-tidy checks][ref-tool-clang-tidy-checks].

To see an example of a clang-tidy configuration file, refer to the `.clang-tidy` file of the [C++ project template][ref-cpp-project-template], which includes the desired check options for that project, but can be used as a starting point and be adjusted to your needs.

Clang-tidy supports many options which can be found using the `--help` option:

```sh
$ clang-tidy --help
```

For example, to run clang-tidy on a file using a compile command database (e.g., `compile_commands.json` generated by CMake in a build directory, with `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON`):

```sh
$ clang-tidy -p <build_path> <file>
```

As previously mentioned, clang-tidy can be integrated in a IDE/editor, like Visual Studio Code. The [C/C++ extension][ref-vscode-cpp-extension] needs to be installed for configuring and using clang-tidy from the Visual Studio Code. Additionally, you can configure to automatically analyze the code when saving a file, adding code analysis settings to the `.vscode/settings.json` file of your workspace, like the ones listed below:

```json
{
    "C_Cpp.codeAnalysis.clangTidy.enabled": true,
    "C_Cpp.codeAnalysis.exclude": {
        "build/": true,
        "external/": true
    },
    "cmake.copyCompileCommands": "${workspaceFolder}/build/compile_commands.json",
    "C_Cpp.default.compileCommands": "${workspaceFolder}/build/compile_commands.json",
    "C_Cpp.codeAnalysis.clangTidy.useBuildPath": true,
}
```

Please refer to the [clang-tidy page][ref-tool-clang-tidy] for more details regarding this tool.

## Runtime analysis

Runtime analysis tools monitor the application during execution to detect memory errors, undefined behavior, concurrency issues, and other runtime defects.

### Sanitizers

Sanitizers are tools integrated into modern compilers, such as GCC and Clang, that help detect bugs in programs at runtime. These tools can be enabled for code compilation and are able to catch common but hard-to-find issues such as memory errors, undefined behavior, or thread race conditions. Therefore, sanitizers allow early bug detection and improve code reliability, stability, and security.

When the code is compiled with a sanitizer enabled:

- The compiler inserts special instrumented code.
- At runtime, this instrumentation monitors the behavior of the program.
- If an issue is detected, it halts the program execution, prints a diagnostic report with detailed information (type of issue, file, line number, etc), and exits with a non-zero exit code.

There are some types of sanitizers that can be used in a C++ project, some of them are described in the next sections.

#### Address sanitizer

AddressSanitizer (ASan) is a fast memory error detector, that instruments memory access instructions to detect issues such as:

- Out-of-bounds accesses to heap, stack and globals.
- Use-after-free bugs.
- Double-free and invalid free issues.

To enable AddressSanitizer, compile and link your program with `-fsanitize=address` option. To get a reasonable performance add `-O1` or higher, and to get nicer stack traces in error messages add `-fno-omit-frame-pointer`. Besides that, you should also use `-g` to produce more meaningful output. Note that the runtime behavior can be influenced by the `ASAN_OPTIONS` environment variable.

For example, the following code contains an *use after free* error that should be detected by this sanitizer:

```c++
// asan_example.cpp
int main(int argc, char* argv[])
{
    int* array = new int[42];
    delete [] array;
    return array[argc]; // Use after free.
}
```

Using the Clang compiler, the commands below can be utilized to compile and link with this sanitizer:

```sh
$ clang++ -fsanitize=address -O1 -g -fno-omit-frame-pointer asan_example.cpp
$ ./a.out
```

Please refer to the [AddressSanitizer][ref-tool-sanitizer-address] and [GCC program instrumentation options][ref-gcc-instrumentation-options] pages for more details regarding this tool.

**Notes:**

- AddressSanitizer cannot be combined with ThreadSanitizer.
- Typical slowdown introduced by AddressSanitizer is 2x.
- Supported by Clang, GCC and MSVC compilers.

#### Leak sanitizer

LeakSanitizer (LSan) is a runtime memory leak detector, that can be used "standalone" or combined with AddressSanitizer.

To enable LeakSanitizer, compile and link your program with `-fsanitize=leak` option. Additionally, `-g` should also be used to produce more meaningful output. Note that the runtime behavior can be influenced by the `LSAN_OPTIONS` environment variable.

For example, the following code contains a memory leak that should be detected by this sanitizer:

```c++
// lsan_example.cpp
int main()
{
    int* leaky_array = new int[100]; // Allocated memory.
    leaky_array[0] = 42; // Used but never deleted.
    return 0;
}
```

Using the Clang compiler, the commands below can be utilized to compile and link with this sanitizer:

```sh
$ clang -fsanitize=leak -g -fno-omit-frame-pointer lsan_example.cpp
$ ./a.out
# Or combined with AddressSanitizer.
$ clang -fsanitize=address -g -fno-omit-frame-pointer lsan_example.cpp ; ASAN_OPTIONS=detect_leaks=1 ./a.out
```

Please refer to the [LeakSanitizer][ref-tool-sanitizer-leak] and [GCC program instrumentation options][ref-gcc-instrumentation-options] pages for more details regarding this tool.

**Notes:**

- LeakSanitizer cannot be combined with ThreadSanitizer.
- Almost no performance overhead is added by the LeakSanitizer until the very end of the process, at which point there is an extra leak detection phase.
- Supported by Clang and GCC compilers.

#### Memory sanitizer

MemorySanitizer (MSan) is a detector of uninitialized memory use, that instruments the code to detect issues such as:

- Uninitialized value was used in a conditional branch.
- Uninitialized pointer was used for memory accesses.
- Uninitialized value was passed or returned from a function call, which is considered an undefined behavior.

To enable MemorySanitizer, compile and link your program with `-fsanitize=memory` option. To get a reasonable performance add `-O1` or higher, and to get nicer stack traces in error messages add `-fno-omit-frame-pointer`. Besides that, you should also use `-g` to produce more meaningful output. Note that the runtime behavior can be influenced by the `MSAN_OPTIONS` environment variable.

For example, the following code contains an *use of uninitialized value* error that should be detected by this sanitizer:

```c++
// msan_example.cpp
#include <iostream>
int main(int argc, char* argv[])
{
    int* a = new int[10];
    auto x = a[5]; // Use of uninitialized value.
    std::cout << "x = " << x << "\n";
    return 0;
}
```

Using the Clang compiler, the commands below can be utilized to compile and link with this sanitizer:

```sh
$ clang++ -fsanitize=memory -O1 -g -fno-omit-frame-pointer msan_example.cpp
$ ./a.out
```

Please refer to the [MemorySanitizer][ref-tool-sanitizer-memory] page for more details regarding this tool.

**Notes:**

- Typical slowdown introduced by MemorySanitizer is 3x.
- Supported by Clang compiler.
- MemorySanitizer requires that all program code is instrumented. This also includes any libraries that the program depends on, even libc. Failing to achieve this may result in false reports.

#### Thread sanitizer

ThreadSanitizer (TSan) is a data race detector, that instruments memory access instructions to detect data race bugs.

To enable ThreadSanitizer, compile and link your program with `-fsanitize=thread` option. To get a reasonable performance add `-O1` or higher, and use `-g` to produce more meaningful output. Note that the runtime behavior can be influenced by the `TSAN_OPTIONS` environment variable.

For example, the following code contains a data race that should be detected by this sanitizer:

```c++
// tsan_example.cpp
#include <iostream>
#include <thread>

int shared_data = 0;

void increment()
{
    for (int i = 0; i < 1000; ++i) {
        shared_data++; // Data race.
    }
}

int main()
{
    std::thread t1{increment};
    std::thread t2{increment};
    t1.join();
    t2.join();
    std::cout << "Final value: " << shared_data << "\n";
    return 0;
}
```

Using the Clang compiler, the commands below can be utilized to compile and link with this sanitizer:

```sh
$ clang++ -fsanitize=thread -O1 -g tsan_example.cpp
$ ./a.out
```

Please refer to the [ThreadSanitizer][ref-tool-sanitizer-thread] and [GCC program instrumentation options][ref-gcc-instrumentation-options] pages for more details regarding this tool.

**Notes:**

- ThreadSanitizer cannot be combined with AddressSanitizer and LeakSanitizer.
- Typical slowdown introduced by ThreadSanitizer is about 5x-15x.
- Typical memory overhead introduced by ThreadSanitizer is about 5x-10x.
- Supported by Clang and GCC compilers.

#### Undefined behavior sanitizer

UndefinedBehaviorSanitizer (UBSan) is a fast undefined behavior detector, that instruments the code to detect issues during program execution such as:

- Array subscript out of bounds, where the bounds can be statically determined.
- Bitwise shifts that are out of bounds for their data type.
- Dereferencing misaligned or null pointers.
- Signed integer overflow.
- Conversion to, from, or between floating-point types which would overflow the destination.

To enable UndefinedBehaviorSanitizer, compile and link your program with `-fsanitize=undefined` option. In addition, this sanitizer can be configured with a specific check or group of checks, allowing to enable or disable them, using `-fsanitize=...` and `-fno-sanitize=...`, respectively. All check options supported by UndefinedBehaviorSanitizer can be found in [UBSan checks][ref-tool-sanitizer-undefined-checks]. To get nicer stack traces in error messages add `-fno-omit-frame-pointer` and `-g`. Note that the runtime behavior can be influenced by the `UBSAN_OPTIONS` environment variable.

For example, the following code contains a *null pointer dereference* error that should be detected by this sanitizer:

```c++
// ubsan_example.cpp
int main(int argc, char* argv[])
{
    int* ptr = nullptr;
    int x = *ptr; // Null pointer dereference.
    return 0;
}
```

Using the Clang compiler, the commands below can be utilized to compile and link with this sanitizer:

```sh
$ clang++ -fsanitize=undefined -g -fno-omit-frame-pointer ubsan_example.cpp
$ ./a.out
```

Please refer to the [UndefinedBehaviorSanitizer][ref-tool-sanitizer-undefined] and [GCC program instrumentation options][ref-gcc-instrumentation-options] pages for more details regarding this tool.

**Notes:**

- UndefinedBehaviorSanitizer checks have small runtime cost and no impact on address space layout or ABI.
- Supported by Clang and GCC compilers.

## Documentation generation

Documentation generation tools produce API and project documentation directly from the source code, helping keep the documentation synchronized with the implementation.

### Doxygen

Doxygen is a documentation generator tool that automates the creation of documentation from source code comments, supporting C++, C, C#, Python, PHP, Java, Objective-C, Fortran, VHDL, Splice, IDL, and Lex code. The documentation can be generated in various output formats, such as HTML and PDF. Moreover, this tool is able to generate graphical representations of class hierarchies and collaboration diagrams, providing a visual overview of the relationships between classes and functions.

It utilizes a configuration file (*Doxyfile*) that permits users to customize the documentation generation process, like the input files and the output format. To see an example of a doxygen configuration file, refer to the `Doxyfile` file of the [C++ project template][ref-cpp-project-template], which includes the desired options for that project, but can be used as a starting point and be adjusted to your needs.

The format of the source code comments needs to follow some rules, in order to generate documentation from those comments by this tool.

Doxygen supports many options which can be found using the `--help` option:

```sh
$ doxygen --help
```

For example, to run doxygen to generate documentation using an existing configuration file:

```sh
$ doxygen <config_file>
```

Please refer to the [Doxygen page][ref-tool-doxygen] for more details regarding this tool.

## Build system

A build system provides a structured and automated way to compile, link, test, and package a C++ project. Some of the main benefits are:

- **Automation**: eliminates the need to manually invoke the compiler and linker with long command lines.
- **Incremental builds**: rebuilds only the files that have changed, significantly reducing build times.
- **Dependency management**: tracks source file dependencies (such as header files) and rebuilds affected targets automatically.
- **Cross-platform support**: makes it easier to build the same project on different operating systems and with different compilers.
- **Configuration management**: supports multiple build configurations, such as Debug, Release or coverage builds.
- **Project organization**: helps manage large projects with multiple libraries, executables, and external dependencies.
- **Reproducibility**: ensures every developer and CI system builds the project using the same rules and settings.
- **Integration with IDEs**: many build systems can generate project files or are directly supported by IDEs, improving the development experience.
- **Testing integration**: can automate the execution of unit tests and other validation steps as part of the build process.
- **Packaging and installation**: simplifies creating installable artifacts, packages, or distributable binaries.
- **Continuous Integration (CI)**: integrates naturally with CI/CD pipelines, enabling automated builds, testing, and deployment.
- **Maintainability**: centralizes build logic, making it easier to update compiler options, add new targets, or modify dependencies.

While small projects consisting of only a few source files can often be built manually (invoking simple compiler commands), a build system becomes increasingly important as a project grows. Build system tools automate the build process, improve maintainability, and provide a consistent and portable way to build software across different platforms and development environments.

### CMake

CMake is a build system that generates native build files (such as Makefiles or Ninja files) from a platform-independent description of the build, managing compiler settings, dependencies, and build targets in a portable way across operating systems and toolchains.

Please refer to the [C++ project template][ref-cpp-project-template] to see how CMake can be used in a C++ project, and to the [CMake page][ref-tool-cmake] for more details regarding this tool.

### Bazel

Bazel is a build system focused on high-performance, reproducible builds and large-scale codebases. It provides strict dependency tracking, remote caching, and parallel execution, making it well-suited for scalable and incremental builds in complex projects or monorepos.

Please refer to the [Bazel page][ref-tool-bazel] for more details regarding this tool.

## Example Project

To see how these tools can be used together in a real-world project, refer to the [C++ project template][ref-cpp-project-template]. It demonstrates a practical configuration and integration of several of the tools described in this document.

## References

- [Clang-format][ref-tool-clang-format]
- [Clang-format style options][ref-tool-clang-format-style-options]
- [cmake-format][ref-tool-cmake-format]
- [Clang-tidy][ref-tool-clang-tidy]
- [Clang-tidy checks][ref-tool-clang-tidy-checks]
- [Address sanitizer][ref-tool-sanitizer-address]
- [Leak sanitizer][ref-tool-sanitizer-leak]
- [Memory sanitizer][ref-tool-sanitizer-memory]
- [Thread sanitizer][ref-tool-sanitizer-thread]
- [Undefined behavior sanitizer][ref-tool-sanitizer-undefined]
- [Undefined behavior sanitizer checks][ref-tool-sanitizer-undefined-checks]
- [GCC program instrumentation options][ref-gcc-instrumentation-options]
- [Doxygen][ref-tool-doxygen]
- [CMake][ref-tool-cmake]
- [Visual Studio Code: C/C++ extension][ref-vscode-cpp-extension]
- [C++ project template][ref-cpp-project-template]

[ref-tool-clang-format]: https://clang.llvm.org/docs/ClangFormat.html "Clang-format"
[ref-tool-clang-format-style-options]: https://clang.llvm.org/docs/ClangFormatStyleOptions.html "Clang-format style options"
[ref-tool-cmake-format]: https://github.com/cheshirekow/cmake_format "cmake-format"
[ref-tool-clang-tidy]: https://clang.llvm.org/extra/clang-tidy/ "Clang-tidy"
[ref-tool-clang-tidy-checks]: https://clang.llvm.org/extra/clang-tidy/checks/list.html "Clang-tidy checks"
[ref-tool-sanitizer-address]: https://clang.llvm.org/docs/AddressSanitizer.html
[ref-tool-sanitizer-leak]: https://clang.llvm.org/docs/LeakSanitizer.html
[ref-tool-sanitizer-memory]: https://clang.llvm.org/docs/MemorySanitizer.html
[ref-tool-sanitizer-thread]: https://clang.llvm.org/docs/ThreadSanitizer.html
[ref-tool-sanitizer-undefined]: https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
[ref-tool-sanitizer-undefined-checks]: https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html#available-checks
[ref-gcc-instrumentation-options]: https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html
[ref-tool-doxygen]: https://www.doxygen.nl/ "Doxygen"
[ref-tool-cmake]: https://cmake.org/ "CMake"
[ref-tool-bazel]: https://bazel.build/ "Bazel"
[ref-vscode-cpp-extension]: https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools "Visual Studio Code: C/C++ extension"
[ref-cpp-project-template]: https://github.com/hugorbarbosa/cpp-project-template "C++ project template"
