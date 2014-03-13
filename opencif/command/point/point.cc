/*
 * LibOpenCIF, a library to read the contents of a CIF (Caltech Intermediate
 * Form) file. The library also includes a finite state machine to validate
 * the contents, acording to the specifications found in the technical
 * report 2686, from february 11, 1980.
 * 
 * Copyright (C) 2014, Moises Chavez Martinez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */   

# include "point.h"

/*
 * Default constructor. Initialices the point with a 0,0 value.
 */
OpenCIF::Point::Point ( void )
{
   set ( 0 , 0 );
}

/*
 * Specialized constructor. Initialices a point with the values specified.
 */
OpenCIF::Point::Point ( const long int& new_x , const long int& new_y )
{
   set ( new_x , new_y );
}

/*
 * Nothing to do.
 */
OpenCIF::Point::~Point ( void )
{
}

/*
 * Returns the X position value of the actual point.
 */
long int OpenCIF::Point::getX ( void ) const
{
   return ( point_x );
}

/*
 * Returns the Y position value of the actual point.
 */
long int OpenCIF::Point::getY ( void ) const
{
   return ( point_y );
}

/*
 * This member function let the user to set a point in a single call.
 * The first argument is the X position value, the second is the Y position value.
 * Internally are called the member functions to set X and Y, indpendently. This
 * behavior is intended in case of adding some kind of checking for the values.
 */
void OpenCIF::Point::set ( const long int& new_x , const long int& new_y )
{
   setX ( new_x );
   setY ( new_y );
   
   return;
}

/*
 * This member functions receives the X position value and sets it to
 * the attribute "point_x".
 */
void OpenCIF::Point::setX ( const long int& new_x )
{
   point_x = new_x;
   
   return;
}

/*
 * This member functions receives the Y position value and sets it to
 * the attribute "point_y".
 */
void OpenCIF::Point::setY ( const long int& new_y )
{
   point_y = new_y;
   
   return;
}
