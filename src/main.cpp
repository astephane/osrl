//
// Copyright 2020 Stéphane ALBERT
//
// This file is part of OSRogueL (osrl).
//
// OSRogueL (osrl) is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// OSRogueL (osrl) is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with upicore.  If not, see <https://www.gnu.org/licenses/>.
//

#include "config.hpp"

#include <cstdlib>
#include <iostream>


#if USE_LIBTCOD

#include <libtcod.hpp>

int
libtcod_main( int unused( argc ), char * unused( argv )[] )
{
  TCODConsole::initRoot( 80, 50, "OSRogueL " OSRL_VERSION_STRING, false );

  while( !TCODConsole::isWindowClosed() )
  {
    TCOD_key_t key;

    TCODSystem::checkForEvent( TCOD_EVENT_KEY_PRESS, &key, nullptr );

    TCODConsole::root->clear();

    TCODConsole::root->putChar( 40, 25, '@' );

    TCODConsole::flush();
   }
}

#endif // USE_LIBTCOD


int
main( int argc, char * argv[] )
{
  std::cout
    << "Welcome to OSRogueL version " OSRL_VERSION_STRING " distributed under the terms of the " OSRL_LICENCE
    << std::endl;

#if USE_LIBTCOD
  std::cout << "USE_LIBTCOD" << std::endl;

  return libtcod_main( argc, argv );

#else // USE_LIBTCOD
  return EXIT_SUCCESS;

#endif // USE_LIBTCOD
}
