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

  game
  ::game( hero::input_pointer && in_ ) :
    monster_input( std::make_shared< monster::input_pointer::element_type >() )
  {
    actors.reserve( 2 );

    actors.push_back( std::make_unique< hero >( std::move( in_ ) ) );
    // actors.push_back( std::make_unique< monster >( monster_input ) );

    actors.front()->pos = vec2i( 40, 40 );
  }

  void
  game
  ::update_input()
  {
    std::for_each(
      std::begin( actors ),
      std::end( actors ),
      []( auto & a ) {

	assert( a );

	auto in = a->in.lock();

	assert( in );

	in->update( *a );
      }
      );
  }

  void
  game
  ::process()
  {
    static_assert( std::is_unsigned_v< decltype( current ) > );

    assert( current < actors.size() );
    assert( actors[ current ] );

    auto a = actors[ current ]->get_next_action();

    if( !a )
      return;

#if 0
    {
      cxx::raw_ptr< action > it = a.get();

      assert( it );

      while( it )
	if( it->perform() )
	  it = nullptr;
	else
	  it = it->alternate.get();
    }

#else
    while( a )
    {
      // std::cout << typeid( *a ).name() << std::endl;

      if( a->perform( *actors[ current ] ) )
	a = nullptr;
      else
	a = std::move( a->alternate );
    }

#endif

    // Generator design-pattern
    current = ( current + 1 ) % actors.size();
  }

} // osrl
