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
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with OSRogueL (osrl).  If not, see <https://www.gnu.org/licenses/>.
#

cmake_minimum_required( VERSION 3.13 )

project( osrl VERSION 0.1.0 )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

configure_file( osrl_config.hpp.in osrl_config.hpp )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

include( cmake/options.cmake )

add_subdirectory( mod )
add_subdirectory( src )
add_subdirectory( test )
