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

#ifndef OSRL_VEC2_HPP
#define OSRL_VEC2_HPP 0x54470000F233C0D3


// #include <type_traits>


namespace osrl
{

  template< typename T >
  struct vec2
  {
    // static_assert( std::is_pod_v< vec2 > );

    using value_type = T;

    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    /*
    using reference = std::add_lvalue_reference_t< T >;
    using const_reference = std::add_lvalue_reference_t< std::add_const_t< T > >;

    using pointer = std::add_pointer_t< T >;
    using const_pointer = std::add_pointer< std::add_const_t< T > >;
    */

    constexpr vec2( T x_ = T( 0 ), T y_ = T( 0 ) ) noexcept :
      x( x_ ),
      y( y_ ) {}

    bool
    is_zero() noexcept
    {
      return x == T( 0 ) && y == T( 0 );
    }

    vec2
    operator - () const
    {
      return vec2( -x, -y );
    }

    vec2
    operator + ( const T & rhs ) const
    {
      return vec2( x + rhs.x,
		   y + rhs.y );
    }


    value_type x;
    value_type y;
  };

  template< typename T >
  struct size
  {
  };

} // osrl


#endif // OSRL_VEC2_HPP
