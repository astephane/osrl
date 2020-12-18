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

#include <cassert>


namespace osrl
{

  game
  ::game( hero::input_pointer && in_ ) :
    monster_input( std::make_shared< monster::input_pointer::element_type >() )
  {
    actors.reserve( 2 );

    actors.push_back( std::make_unique< hero >( std::move( in_ ) ) );
    actors.push_back( std::make_unique< monster >( std::make_shared< ai_component >() ) );
  }

  void
  game
  ::process()
  {
    static_assert( std::is_unsigned_v< decltype( current ) > );

    assert( current < actors.size() );

    assert( actors[ current ] );

    auto a = actors[ current ]->get_action();

    if( !a )
      return;

    {
      cxx::raw_ptr< action > it = a.get();

      assert( it );

      while( it )
	if( it->perform() )
	  it = nullptr;
	else
	  it = it->alternate.get();
    }

    // Generator design-pattern
    current = ( current + 1 ) % actors.size();
  }

} // osrl
