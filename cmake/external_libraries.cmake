# The MIT License (MIT)
#
# Copyright (c) 2016 Sławomir Cielepak
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

##
# Find for required libraries
##
macro( FindRequiredLibraries )

set(THREADS_PREFER_PTHREAD_FLAG ON)

# Workaround for ubuntu
set(CMAKE_MODULE_PATH /usr/share/SFML/cmake/Modules/)

find_package(Threads REQUIRED)
find_package(Boost 1.58 REQUIRED COMPONENTS system program_options)
find_package(SFML  2.4.2  REQUIRED system window graphics network audio)
find_package(X11   1.6  REQUIRED)
find_package(GTest 1.7 REQUIRED)

set(EXTERNAL_LIBRARIES
  Threads::Threads
  m
  ${SFML_LIBRARIES}
  ${Boost_LIBRARIES}
  ${X11_LIBRARIES}
)

set(TEST_LIBRARIES
  ${GTEST_LIBRARIES}
  pthread
)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

endmacro( FindRequiredLibraries )
