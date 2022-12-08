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

namespace osrl::tcod
{

  struct human_component : public osrl::human_component
  {
    void update( actor & actor_ )
    {
      // std::cout << "std::osrl::tcode::human_component::update()" << std::endl;

      actor::action_pointer a;

      switch( key.vk )
      {
      case TCODK_UP:
        a = std::make_unique< move_action >( vec2i::south() );
        break;

      case TCODK_DOWN:
        a = std::make_unique< move_action >( vec2i::north() );
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

  void
  render( game const & game_ )
  {
    assert( TCODConsole::root );

    TCODConsole::root->clear();

    for( game::actor_pointer const & actor : game_.actors )
    {
        assert( actor );

        TCODConsole::root->putChar( actor->pos.x, actor->pos.y, actor->get_body() );
    }

    TCODConsole::flush();
  }

  int
  main( int unused( argc ), char * unused( argv )[] )
  {
    TCODConsole::initRoot( width(), height(), "\"Blackhawk\" OSRogueL " OSRL_VERSION_STRING, false );

    // TCODConsole::root->setBackgroundFlag( TCOD_BKGND_COLOR_BURN );

    auto human_input = std::make_shared< human_component >();

    osrl::game game( human_input );

    // osrl::vec2< int > pos(
    //   width() / 2,
    //   height() / 2
    //   );

    while( !TCODConsole::isWindowClosed() )
    {
      render( game );

      TCODSystem::waitForEvent( TCOD_EVENT_KEY_PRESS, &human_input->key, &human_input->mouse, false );

      game.update_input();
      game.process();
    }

    // TCOD::quit();

    return EXIT_SUCCESS;
  }

} // tcode

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
  std::cout << std::endl;
}

int
main( int argc, char * argv[] )
{
  std::cout
    << "Welcome to OSRogueL version " OSRL_VERSION_STRING " distributed under the terms of the " OSRL_LICENCE
    << std::endl;

#if 0
  display_extended_ascii_chart();
#endif

#if USE_LIBTCOD
  return osrl::tcod::main( argc, argv );

#else // USE_LIBTCOD
  return EXIT_SUCCESS;

#endif // USE_LIBTCOD
}
