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


#include "actor.hpp"
#include "action.hpp"

#include <cassert>


namespace osrl
{

  void
  game
  ::process()
  {
    static_assert( std::is_unsigned_v< decltype( current ) > );

    assert( current < actors.size() );

    assert( actors[ current ] );

    auto action = actors[ current ]->get_action();

    if( !action )
      return;

    if( action->perform() )
    {
      // Do something.
    }

    // Generator design-pattern
    current = ( current + 1 ) % actors.size();
  }

} // osrl
