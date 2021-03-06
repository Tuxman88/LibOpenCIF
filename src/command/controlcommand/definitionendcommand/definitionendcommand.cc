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

# include "definitionendcommand.hh"

/*
 * Default constructor. Nothing to do.
 */
OpenCIF::DefinitionEndCommand::DefinitionEndCommand ( void )
   : ControlCommand ()
{
   command_type = DefinitionEnd;
}

/*
 * Non-Default constructor. Nothing to do.
 */
OpenCIF::DefinitionEndCommand::DefinitionEndCommand ( const std::string& str_command )
   : ControlCommand ()
{
   command_type = DefinitionEnd;
   str_command.size ();
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::DefinitionEndCommand::~DefinitionEndCommand ( void )
{
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionEndCommand& command )
{   
   command.print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionEndCommand& command )
{
   // Dummy call to prevent warnings about command not being used
   command.read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionEndCommand* command )
{   
   command->print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionEndCommand* command )
{
   // Dummy call to prevent warnings about command not being used
   if ( command == 0 )
   {
      return ( input_stream );
   }
   
   return ( input_stream );
}

void OpenCIF::DefinitionEndCommand::print ( std::ostream& output_stream )
{
   output_stream << "D F ;";
   
   // Since the command is not needed... well... do nothing...
   
   return;
}

void OpenCIF::DefinitionEndCommand::read ( std::istream& input_stream )
{
   input_stream.gcount ();
   
   return;
}
