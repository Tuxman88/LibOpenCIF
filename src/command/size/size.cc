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

# include "size.hh"

/*
 * Default constructor. Initialize the values of the size to a non-zero value.
 */
OpenCIF::Size::Size ( void )
{
   size_height = 1;
   size_width = 1;
}

/*
 * Non-Default constructor. Initialize the values of the size.
 */
OpenCIF::Size::Size ( const unsigned long int& new_width , const unsigned long int& new_height )
{
   set ( new_width , new_height );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::Size::~Size ( void )
{
}

/*
 * Member function to return the height of the size.
 */
long unsigned int OpenCIF::Size::getHeight ( void ) const
{
   return ( size_height );
}

/*
 * Member function to return the width of the size.
 */
long unsigned int OpenCIF::Size::getWidth ( void ) const
{
   return ( size_width );
}

/*
 * Member function to set both dimensions of the size at the same time.
 */
void OpenCIF::Size::set ( const long unsigned int& new_width , const long unsigned int& new_height )
{
   setWidth ( new_width );
   setHeight ( new_height );
   
   return;
}

/*
 * Member function to set the height of the size.
 */
void OpenCIF::Size::setHeight ( const long unsigned int& new_height )
{
   size_height = new_height;
   
   return;
}

/*
 * Member function to set the width of the size.
 */
void OpenCIF::Size::setWidth ( const long unsigned int& new_width )
{
   size_width = new_width;
   
   return;
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::Size& command )
{
   unsigned long int x , y;
   
   input_stream >> x >> y;
   command.size_height = y;
   command.size_width = x;
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , const OpenCIF::Size& command )
{
   output_stream << command.getWidth () << " " << command.getHeight ();
   
   return ( output_stream );
}