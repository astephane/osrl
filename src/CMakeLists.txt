#
# Copyright 2020 Stéphane ALBERT
#
# This file is part of OSRogueL (osrl).
#
# OSRogueL (osrl) is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# OSRogueL (osrl) is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with OSRogueL (osrl).  If not, see <https://www.gnu.org/licenses/>.
#

set( SOURCES
  main.cpp
  osrl.hpp
  osrl.cpp
  )


add_executable( ${PROJECT_NAME} ${SOURCES} )

message( "CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}" )
message( "CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}" )

target_include_directories( ${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}
  )
