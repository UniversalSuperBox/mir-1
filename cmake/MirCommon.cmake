# Copyright © 2012 Canonical Ltd.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Authored by: Thomas Voss <thomas.voss@canonical.com>,
#              Alan Griffiths <alan@octopull.co.uk>
cmake_minimum_required (VERSION 2.6)
# Create target to discover tests

option(
  DISABLE_GTEST_TEST_DISCOVERY
  "If set to ON, disables fancy test autodiscovery and switches back to classic add_test behavior"
  OFF
)

option(
  ENABLE_MEMCHECK_OPTION
  "If set to ON, enables automatic creation of memcheck targets"
  OFF
)

if(ENABLE_MEMCHECK_OPTION)
  find_program(
    VALGRIND_EXECUTABLE
    valgrind)

  if(VALGRIND_EXECUTABLE)
    set(VALGRIND_ARGS "--trace-children=yes")
    set(ENABLE_MEMCHECK_FLAG "--enable-memcheck")
  else(VALGRIND_EXECUTABLE)
    message("Not enabling memcheck as valgrind is missing on your system")
  endif(VALGRIND_EXECUTABLE)
endif(ENABLE_MEMCHECK_OPTION)

function (mir_discover_tests EXECUTABLE)

  if(BUILD_ANDROID OR DISABLE_GTEST_TEST_DISCOVERY)
    add_test(${EXECUTABLE} ${VALGRIND_EXECUTABLE} ${VALGRIND_ARGS} "${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE}")
  else()
    set(TEST_DISCOVERY_TARGET_NAME "discover_tests_in_${EXECUTABLE}")
    message(STATUS "Defining target ${TEST_DISCOVERY_TARGET_NAME}")

    # This target is always considered out-of-date, and is always run (at least for normal builds, except for make test/install).
    add_custom_target(
      ${TEST_DISCOVERY_TARGET_NAME} ALL
      ${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE} --gtest_list_tests | ${CMAKE_BINARY_DIR}/mir_gtest/mir_discover_gtest_tests ${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE} ${ENABLE_MEMCHECK_FLAG}      
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Discovering Tests in ${EXECUTABLE}" VERBATIM)

    add_dependencies(${TEST_DISCOVERY_TARGET_NAME} ${EXECUTABLE} mir_discover_gtest_tests)
  endif()
endfunction ()
