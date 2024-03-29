#
# Copyright 2020 Stéphane ALBERT
#
# This file is part of OSRogueL (osrl).
#
# OSRogueL (osrl) is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# OSRogueL (osrl) is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with OSRogueL (osrl).  If not, see <https://www.gnu.org/licenses/>.
#

set( SOURCES
  main.cpp
  vec2.test.cpp
  )

set( TARGET_NAME "test-${PROJECT_NAME}" )

# find_package( Cathc2 REQUIRED )

add_executable( ${TARGET_NAME} ${SOURCES} )

target_include_directories( ${TARGET_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/test
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}
  #
  ${CMAKE_SOURCE_DIR}/mod/libascxx/src
  ${CMAKE_SOURCE_DIR}/mod/libascxx
  ${CMAKE_SOURCE_DIR}/mod/catch2/single_include
  )

target_link_libraries( ${TARGET_NAME} PRIVATE
  # Catch2::Catch2
  # $<$<BOOL:${USE_LIBTCOD}>:${LIBTCOD_LIBRARIES}>
  )
