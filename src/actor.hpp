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

#include "action.hpp"

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

} // osrl


#endif // OSRL_ACTOR_HPP
