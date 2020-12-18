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
  ecs.cpp
  munificent_ecs.cpp
  osrl.cpp
  vec2.cpp
  )


add_executable( ${PROJECT_NAME} ${SOURCES} )

target_include_directories( ${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/mod/libascxx/src
  ${CMAKE_BINARY_DIR}
  # ${CMAKE_BINARY_DIR}/mod/libascxx
  $<$<BOOL:${USE_LIBTCOD}>:${LIBTCOD_INCLUDE_DIRS}>
  )

target_link_libraries( ${PROJECT_NAME} PRIVATE
  $<$<BOOL:${USE_LIBTCOD}>:${LIBTCOD_LIBRARIES}>
  )
