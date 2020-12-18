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

#ifndef ECS_HPP
#define ECS_HPP 0x54470000F233C0D3


#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>


namespace osrl
{
  struct entity
  {
  };

  struct component
  {
  };

  struct system
  {
  };
} // osrl


//
// See Bob "munificent" Nystrom: https://www.youtube.com/watch?v=JxI3Eu5DPwE
// See Bob "munificent" Nystrom: http://gameprogrammingpatterns.com/
//
namespace munificent::ecs
{

  //
  // Patterns:
  // 1. Components:
  //	use components to represent capabilities
  // 2. Type Objects:
  //	define your own type where each instance represents a type
  // 3. Command Objects:
  //	when in doubt, try turning operation (verb) into an object
  //	(noun).
  //

  struct capability : public osrl::component
  {
  };

  struct attack : public capability
  {
    int min_dmg;
    int max_dmg;

    void hit();
  };

  struct defense : public capability
  {
    int armor;
    int dodge;

    void defend();
  };

/* abstract */
  struct use : public capability
  {
    virtual void operator () ();
  };

// struct hero;

  struct heal_use : public use
  {
    void operator () () override
    {
// hero->health += 20;
    }

// hero * hero_;
  };

  struct fireball_use : public use
  {
    void operator () () override
    {
// cast fireball
    }
  };

// Closure.
  struct action
  {
    using effect = void;

    effect perform()
    {
      // return {};
    }
  };


  struct drop_action : public action
  {
  };

  struct use_action : public action
  {
  };

  struct rest_action : public action
  {
  };

  struct item : public osrl::component
  {
    attack melee;
    attack ranged;
    defense d;
    std::map< action, use > u;
  };

  void items()
  {
#if 0
    item sword = {
      { 10, 20 },
      {},
      {},
      {},
    };

    item crossbow = {
      {},
      { 10, 20 },
      {},
      {},
    };

    item shield = {
      { 5, 8 },
      {},
      { 3, 0 },
      {},
    };

    item heal_potion = {
      {},
      {},
      {},
      { { quaff_action(), heal_use() }
      },
    };

    item fire_sword = {
      { 30, 40 },
      {},
      {},
      { { activate_action(), fireball_use() }
      },
    };
#endif
  }

  struct type_object
  {
  };

// type-object pattern.
  struct breed : public type_object
  {
    std::string name;
    int max_health;
// Factorize these ones in class
// {
    attack melee;
    attack ranged;
    attack defense;
// }
    std::list< use > moves;
    std::set< std::string > flags;
#if 0
    drop loot;
#endif
  };

// function-object (lambda + captures)
  struct actor : public osrl::entity
  {
    int x;
    int y;
    int speed;

    virtual action take_turn();

    void gain_energy( int )
    {
    }

    bool has_enough_energy()
    {
      return true;
    }

// Bad
// {
#if 0
    void walk();
    void attack();
    void open();
    void close();
    void eat();
    void quaff();
    void teleport();
    void fireball();
#endif
// }
  };

  struct monster : public actor
  {
    breed b;
    int health;

    action take_turn() override
    {
      // pathfinding, ai, etc.
      return {};
    }
  };

  struct hero_class : public type_object
  {
  };

  struct hero : public actor
  {
    hero_class class_;

    action take_turn( char key )
    {
      switch( key )
      {
      case 'd':
	return drop_action();
	break;

      case 'u':
	return use_action();
	break;

      case 'r':
	return rest_action();
	break;

      default:
	  break;
      }
    }
  };

  void game_loop()
  {
    std::vector< actor > actors;

    for( auto & a : actors )
    {
      a.gain_energy( a.speed );

      if( a.has_enough_energy() )
      {
	action act = a.take_turn();
	act.perform();
      }
    }
  }
} // munificent::ecs

#endif // ECS_HPP
