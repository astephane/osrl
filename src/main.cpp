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
#include "game.hpp"
#include "memory.hpp"
#include "pp.hpp"
#include "vec2.hpp"

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>

/*
   _
 _/.\_
/.\_/.\
\_/.\_/
/.\_/.\
\_/.\_/
  \_/

   .   .
 .   .
   .   .
 .   .
   .   .

 . .
. . .
 . .

*/

#if USE_LIBTCOD

PRAGMA_WARNING_PUSH;
PRAGMA_WARNING_DISABLE_GCC_Wshadow;

#include <libtcod.hpp>

PRAGMA_WARNING_POP;

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

namespace osrl::tcode
{

  struct human_component : public osrl::human_component
  {
    void update( actor & actor_ )
    {
      actor::action_pointer a;

      switch( key.vk )
      {
      case TCODK_UP:
        a = std::make_unique< move_action >( vec2i::north() );
        break;

      case TCODK_DOWN:
        a = std::make_unique< move_action >( vec2i::south() );
        break;

      case TCODK_LEFT:
        a = std::make_unique< move_action >( vec2i::west() );
        break;

      case TCODK_RIGHT:
        a = std::make_unique< move_action >( vec2i::east() );
        break;

      default:
        break;
      }

      if( a )
        actor_.set_next_action( std::move( a ) );
    }

    TCOD_key_t key;
    TCOD_mouse_t mouse;
  };

} // tcode

int
libtcod_main( int unused( argc ), char * unused( argv )[] )
{
  TCODConsole::initRoot( width(), height(), "\"Blackhawk\" OSRogueL " OSRL_VERSION_STRING, false );

  // TCODConsole::root->setBackgroundFlag( TCOD_BKGND_COLOR_BURN );

  auto human_component = std::make_shared< osrl::tcode::human_component >();

  osrl::game game( human_component );

  // osrl::vec2< int > pos(
  //   width() / 2,
  //   height() / 2
  //   );

  while( !TCODConsole::isWindowClosed() )
  {
    TCODSystem::checkForEvent( TCOD_EVENT_KEY_PRESS, &human_component->key, &human_component->mouse );

#if 0
    switch( human_component->key.vk )
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

#else
    game.update_input();
    game.process();

#endif

    TCODConsole::root->clear();

    std::for_each(
      std::begin( game.actors ),
      std::end( game.actors ),
      []( auto const & a ) {

        assert( a );

        TCODConsole::root->putChar( a->pos.x, a->pos.y, a->get_body() );
      }
      );

    TCODConsole::flush();
  }

  // TCOD::quit();

  return EXIT_SUCCESS;
}

#endif // USE_LIBTCOD

void
display_extended_ascii_chart()
{
  for( std::int16_t i = 0; i < 256 ; ++i )
  {
    if( i % 16 == 0 )
      std::wcout << std::endl;

    std::wcout
      << std::showbase << std::hex << std::setw( 2 ) << i
      << ": " << static_cast< wchar_t >( i ) << " ";
  }
}

int
main( int argc, char * argv[] )
{
  std::cout
    << "Welcome to OSRogueL version " OSRL_VERSION_STRING " distributed under the terms of the " OSRL_LICENCE
    << std::endl;

  std::cout << std::endl;
  display_extended_ascii_chart();
  std::cout << std::endl;

#if USE_LIBTCOD
  return libtcod_main( argc, argv );

#else // USE_LIBTCOD
  return EXIT_SUCCESS;

#endif // USE_LIBTCOD
}
