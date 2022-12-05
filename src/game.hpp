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

#pragma once

#ifndef OSRL_GAME_HPP
#define OSRL_GAME_HPP 0x54470000F233C0D3


#include "actor.hpp"

#include <memory>
#include <vector>


namespace osrl
{

  // Command design-pattern.
  // Closure concept.
  struct game
  {
    game( hero::input_pointer && );

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

    void update_input();
    void process();

    using actor_pointer = std::unique_ptr< actor >;
    using actor_vector = std::vector< actor_pointer >;

    std::shared_ptr< ai_component > monster_input;
    actor_vector actors;
    actor_vector::size_type current;
  };

} // osrl


#endif // OSRL_GAME_HPP
