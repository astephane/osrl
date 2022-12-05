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
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with OSRogueL (osrl).	If not, see <https://www.gnu.org/licenses/>.
//

#pragma once

#ifndef OSRL_ACTOR_HPP
#define OSRL_ACTOR_HPP 0x54470000F233C0D3


#include "component.hpp"
#include "entity.hpp"
#include "vec2.hpp"

#include <cassert>
#include <memory>


namespace osrl
{

  struct action;


  struct actor : public entity
  {
    using action_pointer = std::unique_ptr< action >;
    using input_pointer = std::weak_ptr< in_component >;

    actor( char c, input_pointer && in_ ) noexcept :
      body( c ),
      in( std::move( in_ ) )
      {}

    char get_body() const noexcept
    {
      return body;
    }

    void set_next_action( action_pointer && a ) noexcept
    {
      assert( a );
      assert( !next_action );

      next_action = std::move( a );
    }

    action_pointer get_next_action()
    {
      return std::move( next_action );
    }

    input_pointer in;
    action_pointer next_action;
    vec2i pos;

  private:
    char body;
  };


  struct character : public actor
  {
    character( char body, input_pointer && in_ ) : actor( body, std::move( in_ ) ) {}
  };


  struct hero : public character
  {
    using input_pointer = std::weak_ptr< human_component >;

    hero( input_pointer && in_ ) : character( '@', std::move( in_ ) ) {}
  };


  struct monster : public character
  {
    using input_pointer = std::weak_ptr< ai_component >;

    monster( input_pointer && in_ ) : character( 'M', std::move( in_ ) ) {}
  };


  struct npc : public monster
  {
    npc( input_pointer && in_ ) : monster( std::move( in_ ) ) {}
  };

} // osrl


#endif // OSRL_ACTOR_HPP
