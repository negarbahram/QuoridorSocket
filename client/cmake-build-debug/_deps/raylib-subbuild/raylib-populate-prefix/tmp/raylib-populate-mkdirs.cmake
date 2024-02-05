# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/apple/Documents/uni_sem1/project/QuoridorSocket/client/cmake-build-debug/_deps/raylib-src"
  "/Users/apple/Documents/uni_sem1/project/QuoridorSocket/client/cmake-build-debug/_deps/raylib-build"
  "/Users/apple/Documents/uni_sem1/project/QuoridorSocket/client/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix"
  "/Users/apple/Documents/uni_sem1/project/QuoridorSocket/client/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/tmp"
  "/Users/apple/Documents/uni_sem1/project/QuoridorSocket/client/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp"
  "/Users/apple/Documents/uni_sem1/project/QuoridorSocket/client/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src"
  "/Users/apple/Documents/uni_sem1/project/QuoridorSocket/client/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/apple/Documents/uni_sem1/project/QuoridorSocket/client/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/apple/Documents/uni_sem1/project/QuoridorSocket/client/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
