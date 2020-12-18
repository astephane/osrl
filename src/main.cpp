//
// Copyright 2020 Stéphane ALBERT
//
// This file is part of OSRogueL (osrl).
//
// OSRogueL (osrl) is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// OSRogueL (osrl) is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with OSRogueL (osrl).  If not, see <https://www.gnu.org/licenses/>.
//

#include "osrl_config.hpp"


#include "action.hpp"
#include "pp.hpp"
#include "vec2.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>

namespace osrl
{

  struct actor : public entity
  {
    virtual action get_action() = 0;
  };

  struct character : public actor
  {
  };

  struct hero : public character
  {
    component input;

    action get_action() override
    {
      return rest_action();
    }
  };

  struct npc : public character
  {
  };

  struct monster : public actor
  {
  };

  struct game
  {
#if 0
    void loop()
    {
      double elapsed = 1.0 / 25.0;

      std::for_each(
	std::begin( actors ),
	std::end( actors ),
	[ elapsed ]( auto * a ) {
	  assert( a );
	  a->update( elapsed );
	}
	);
    }
#endif

    void process()
    {
      auto action = actors[ current ]->get_action();

      if( action.perform() )
      {
	// Do something.
      }

      // Generator design-pattern
      current = ( current + 1 ) % actors.size();
    }

    using actor_pointer = std::unique_ptr< actor >;
    using actor_vector = std::vector< actor_pointer >;

    actor_vector actors;
    actor_vector::size_type current;
  };

} // osrl


#if USE_LIBTCOD

PRAGMA_WARNING_PUSH;
PRAGMA_WARNING_DISABLE_GCC_Wshadow;

#include <libtcod.hpp>

namespace
{
  constexpr int width() noexcept
  {
    return 80;
  }

  constexpr int height() noexcept
  {
    return 80;
  }
} // namespsace

int
libtcod_main( int unused( argc ), char * unused( argv )[] )
{
  TCODConsole::initRoot( width(), height(), "OSRogueL " OSRL_VERSION_STRING, false );

  // TCODConsole::root->setBackgroundFlag( TCOD_BKGND_COLOR_BURN );

  osrl::vec2< int > pos(
    width() / 2,
    height() / 2
    );

  while( !TCODConsole::isWindowClosed() )
  {
    TCOD_key_t key;

    TCODSystem::checkForEvent( TCOD_EVENT_KEY_PRESS, &key, nullptr );

    switch( key.vk )
    {
    case TCODK_UP:
      pos.y = std::max( 0, pos.y - 1 );
      break;

    case TCODK_DOWN:
      pos.y = std::min( height() - 1, pos.y + 1 );
      break;

    case TCODK_LEFT:
      pos.x = std::max( 0, pos.x - 1 );
      break;

    case TCODK_RIGHT:
      pos.x = std::min( width() - 1, pos.x + 1 );
      break;

    default:
      break;
    }

    TCODConsole::root->clear();

    TCODConsole::root->putChar( pos.x, pos.y, '@' );

    TCODConsole::flush();
   }

  // TCOD::quit();

  return EXIT_SUCCESS;
}

PRAGMA_WARNING_POP;

#endif // USE_LIBTCOD


int
main( int argc, char * argv[] )
{
  std::cout
    << "Welcome to OSRogueL version " OSRL_VERSION_STRING " distributed under the terms of the " OSRL_LICENCE
    << std::endl;

#if USE_LIBTCOD
  return libtcod_main( argc, argv );

#else // USE_LIBTCOD
  return EXIT_SUCCESS;

#endif // USE_LIBTCOD
}
