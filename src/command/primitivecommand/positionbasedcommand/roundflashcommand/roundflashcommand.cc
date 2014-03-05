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

# include "roundflashcommand.h"

/*
 * Default constructor. Initialize the diameter to a non-zero value.
 */
OpenCIF::RoundFlashCommand::RoundFlashCommand ( void )
   : PositionBasedCommand ()
{
   command_type = RoundFlash;
   setDiameter ( 1 );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::RoundFlashCommand::~RoundFlashCommand ( void )
{
}

/*
 * Member function to return the actual diameter of the command.
 */
long unsigned int OpenCIF::RoundFlashCommand::getDiameter ( void ) const
{
   return ( round_diameter );
}

/*
 * Member function to set the command diameter.
 */
void OpenCIF::RoundFlashCommand::setDiameter ( const long unsigned int& new_diameter )
{
   round_diameter = new_diameter;
   
   return;
}
