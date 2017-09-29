Dawn <br/> <a target="_blank" href="http://semver.org">![Version][Version.Badge]</a> <a target="_blank" href="https://travis-ci.org/thfabian/dawn">![Travis status][TravisCI.Badge]</a> <a target="_blank" href="https://opensource.org/licenses/MIT">![License: MIT][MIT.License]</a> <a target="_blank" href="https://thfabian.github.io/dawn">![Documentation][Documentation.Badge]</a>
====

## Introduction

Dawn is a compiler toolchain for developing high-level DSLs for geophysical fluid dynamics models. A tutorial and reference documentation is provided [here](https://thfabian.github.io/dawn).

### Motivation

Development productivity of large scientific codes, like geophysical fluid dynamics (GFD) models, decreased drastically in recent times due to the fact these community models often have to run efficiently on multiple computing architectures that impose the use of different programming models.
Embedded domain specific languages (EDSLs) in C ++ have been used successfully in the past to enable a clear separation of concerns between the domain algorithms and the implementation strategy, thus allowing a single source code which is performance portable across heterogeneous architectures.
Yet, using EDSLs in a correct and efficient manner often requires expert knowledge in high-performance computing.
In addition, current DSLs are usually designed and developed for a specific scientific model with little to no reusability among DSLs.

We introduce a new compiler framework, Dawn, that decouples optimization and code generation from high level DSLs.
By exposing a Stencil Intermediate Representation (SIR), we allow users to share the toolchain to optimize and generate code among several DSLs.
This allows the design of expressive, concise DSLs that can focus on applicability and don't need to bother with the aspect of high-performance computing.
Using Dawn as a common compiler infrastructure can drastically reduce development and maintenance effort, while increasing the performance of the generated code, for new and existing DSLs in the GFD model domain.

### Core Features

* Dawn allows the user to generate fast performing code for several back-ends from a relatively simple Stencil Intermediate Representation (SIR).
* Dawn exposes several APIs in different languages (C++, Java, Python) to parse and process the SIR. 
* Dawn is able to generate code to be run on Distributed Memory Machines based on MPI, Machines with access to GPUs based on CUDA as well as naive C++ code with close to no parallelism for debugging.
* Dawn offers a wide range of optimization and static analysis passes to guarantee correctness as well as performance of the generated parallel program.

## Building

Dawn has no external dependencies and only requires a C++11 compiler and [CMake](https://cmake.org/).

```bash
mkdir build && cd build
cmake ..
make
make install
```

This will install Dawn locally into `<dawn-dir>/install/`. For a more detailed guide on how to build Dawn, see [here](https://thfabian.github.io/dawn/basics.html).

## Continuous Integration

### Linux
|  Toolchain   | Config         |                                                     Status                                                   |
|:-------------|:---------------|-------------------------------------------------------------------------------------------------------------:|
| GCC 5.4      | Release        |  <a target="_blank" href="https://travis-ci.org/thfabian/dawn">![GCC 5.4][GCC_54_Release.Badge]</a>          |
| GCC 5.4      | RelWithDebInfo |  <a target="_blank" href="https://travis-ci.org/thfabian/dawn">![GCC 5.4][GCC_54_RelWithDebInfo.Badge]</a>   |
| GCC 6.3      | Release        |  <a target="_blank" href="https://travis-ci.org/thfabian/dawn">![GCC 6.3][GCC_63_Release.Badge]</a>          |
| GCC 6.3      | RelWithDebInfo |  <a target="_blank" href="https://travis-ci.org/thfabian/dawn">![GCC 6.3][GCC_63_RelWithDebInfo.Badge]</a>   |
| Clang 4.0    | Release        |  <a target="_blank" href="https://travis-ci.org/thfabian/dawn">![GCC 5.4][Clang_40_Release.Badge]</a>        |
| Clang 4.0    | RelWithDebInfo |  <a target="_blank" href="https://travis-ci.org/thfabian/dawn">![GCC 5.4][Clang_40_RelWithDebInfo.Badge]</a> |

## About

This project is funded by the [PASCHA](http://www.pasc-ch.org/projects/2017-2020/pascha) project and developed by ETH Zurich and MeteoSwiss.
Significant contributions were made by Fabian Thuering (Master Thesis), Carlos Osuna and Tobias Wicky. 

### License

> The full license can be found [here](https://opensource.org/licenses/MIT).

This project is licensed under the terms of the **MIT** license.

<!-- Links -->
[TravisCI]: https://travis-ci.org/thfabian/dawn
[TravisCI.Badge]: https://travis-ci.org/thfabian/dawn.svg?branch=master
[Documentation.Badge]: https://img.shields.io/badge/documentation-link-blue.svg
[MIT.License]: https://img.shields.io/badge/License-MIT-blue.svg
[Version.Badge]: https://badge.fury.io/gh/thfabian%2Fdawn.svg
[GCC_54_Release.Badge]: https://travis-matrix-badges.herokuapp.com/repos/thfabian/dawn/branches/master/3
[GCC_54_RelWithDebInfo.Badge]: https://travis-matrix-badges.herokuapp.com/repos/thfabian/dawn/branches/master/4
[GCC_63_Release.Badge]: https://travis-matrix-badges.herokuapp.com/repos/thfabian/dawn/branches/master/5
[GCC_63_RelWithDebInfo.Badge]: https://travis-matrix-badges.herokuapp.com/repos/thfabian/dawn/branches/master/6
[Clang_40_Release.Badge]: https://travis-matrix-badges.herokuapp.com/repos/thfabian/dawn/branches/master/7
[Clang_40_RelWithDebInfo.Badge]: https://travis-matrix-badges.herokuapp.com/repos/thfabian/dawn/branches/master/8