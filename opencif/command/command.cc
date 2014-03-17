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

# include "command.h"

/*
 * This constructor initialice the "command_type" attribute.
 */
OpenCIF::Command::Command ( void )
{
   command_type = PlainCommand;
}

/*
 * Nothing to do.
 */
OpenCIF::Command::~Command ( void )
{
}

/*
 * This member function return the type of the current command type.
 */
OpenCIF::Command::CommandType OpenCIF::Command::type ( void )
{
   return ( command_type );
}

/*
 * This member function converts a string into a long int value.
 */
long int OpenCIF::Command::toLInt ( const std::string& value )
{
   long int converted;
   std::istringstream iss ( value );
   iss >> converted;
   
   return ( converted );
}

/*
 * This member function converts a string into a unsigned long int value.
 */
unsigned long int OpenCIF::Command::toULInt ( const std::string& value )
{
   unsigned long int converted;
   std::istringstream iss ( value );
   iss >> converted;
   
   return ( converted );
}
