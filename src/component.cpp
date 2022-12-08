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

#include "component.hpp"

#include "action.hpp"

#include <random>

namespace osrl
{

  namespace
  {
    static std::random_device device;
    static std::mt19937 rng;
    static std::uniform_int_distribution< vec2i::value_type > distribution( -1, 1 );
  } // anonymous

  component
  ::~component()
  {
  }

  void
  ai_component
  ::update( actor & actor_ )
  {
    // std::cout << "std::osrl::ai_component::update()" << std::endl;

    actor_.set_next_action(
      std::make_unique< move_action >(
        vec2i(
          distribution( rng ),
          distribution( rng )
          )
        )
      );
  }

} // osrl
