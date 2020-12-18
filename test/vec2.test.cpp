#include <catch2/catch.hpp>

#include "vec2.hpp"

SCENARIO( "", "" )
{
  GIVEN( "A an uninitialized vec2" )
  {
    osrl::vec2< int > v;

    THEN( "" )
    {
      CAPTURE( v );
      CAPTURE( v.x );
      CAPTURE( v.y );

      REQUIRE( v.x == 0 );
      REQUIRE( v.y == 0 );
    }

    THEN( "" )
    {
      CAPTURE( v );
      CAPTURE( v.x );
      CAPTURE( v.y );

      REQUIRE( v.is_zero() );
    }
  }
}
