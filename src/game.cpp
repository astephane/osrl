//
// Copyright 2020 Stéphane ALBERT
//
// This file is part of OSRogueL (osrl).
//
// OSRogueL (osrl) is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// OSRogueL (osrl) is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public
// License along with racatoma.  If not, see
// <https://www.gnu.org/licenses/>.
//
#include "game.hpp"


#include "action.hpp"
#include "memory.hpp"

#include <algorithm>
#include <cassert>

// #include <iostream>
// #include <typeinfo>


namespace osrl
{

  /***************************************************************************/
  game
  ::game( hero::input_pointer && in_ ) :
    monster_input( std::make_shared< monster::input_pointer::element_type >() ),
    current( 0 )
  {
    actors.reserve( 2 );

    actors.push_back( std::make_unique< hero >( std::move( in_ ) ) );
    actors.push_back( std::make_unique< monster >( monster_input ) );

    actors.front()->pos = vec2i( 40, 40 );
    actors.back()->pos = vec2i( 20, 20 );
  }

  /***************************************************************************/
  void
  game
  ::update_input()
  {
    std::for_each(
      std::begin( actors ),
      std::end( actors ),
      []( actor_pointer & a ) {

        assert( a );

        auto in = a->in.lock();

        assert( in );

        in->update( *a );
      }
      );
  }

  /***************************************************************************/
  void
  game
  ::process()
  {
    static_assert( std::is_unsigned_v< decltype( current ) > );

    for( actor_pointer & actor : actors )
    {
      assert( actor );

      auto action = actor->get_next_action();

      while( action )
      {
        if( action->perform( *actor ) )
          action.reset();
        else
          action = std::move( action->alternate );
      }
    }
  }

} // osrl
