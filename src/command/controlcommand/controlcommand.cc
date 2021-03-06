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

# include "controlcommand.hh"

/*
 * Default constuctor. Initialices the command ID with a value
 * of 1 and sets the needed Command Type.
 */
OpenCIF::ControlCommand::ControlCommand ( void )
   : Command ()
{
   command_id = 1;
   command_type = Control;
}

/*
 * Nothing to do.
 */
OpenCIF::ControlCommand::~ControlCommand ( void )
{
}

/*
 * Returns the ID of the command. For example, in a definition start
 * command, this returns the ID of the definition to create. In a call
 * command, this returns the ID of the definition to call.
 */
long unsigned int OpenCIF::ControlCommand::getID ( void ) const
{
   return ( command_id );
}

/*
 * Member function to set the ID of the definition specified. If the
 * command is a DefinitionStart, the ID will be the ID of the definition
 * to create. If the command is a Call, the ID will be the ID  of the
 * definition to call.
 */
void OpenCIF::ControlCommand::setID ( const long unsigned int& new_id )
{
   command_id = new_id;
   
   return;
}
