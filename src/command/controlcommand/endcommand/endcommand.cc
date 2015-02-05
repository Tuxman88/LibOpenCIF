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

# include "endcommand.hh"

/*
 * Default constructor. Nothing to do.
 */
OpenCIF::EndCommand::EndCommand ( void )
   : ControlCommand ()
{
   command_type = End;
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::EndCommand::~EndCommand ( void )
{
}

unsigned long int OpenCIF::EndCommand::getID ( void ) const
{
   return ( ControlCommand::getID () );
}

void OpenCIF::EndCommand::setID ( const unsigned long int& new_id )
{
   ControlCommand::setID ( new_id );
   return;
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::EndCommand& command )
{
   // Dummy call to prevent warnings about command not being used
   command.getID ();
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::EndCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::EndCommand* command )
{
   // Dummy call to prevent warnings about command not being used
   command->getID ();
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::EndCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

void OpenCIF::EndCommand::print ( std::ostream& output_stream )
{
   output_stream << "E ;";
   
   return;
}

void OpenCIF::EndCommand::read ( std::istream& input_stream )
{
   // Dummy call to prevent warnings about input_stream not being used
   input_stream.gcount ();
   
   return;
}
