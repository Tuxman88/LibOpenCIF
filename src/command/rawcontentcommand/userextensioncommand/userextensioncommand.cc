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

# include "userextensioncommand.hh"

/*
 * Default constructor. Nothing to do.
 */
OpenCIF::UserExtensionCommand::UserExtensionCommand ( void )
   : RawContentCommand ()
{
   command_type = UserExtension;
}

OpenCIF::UserExtensionCommand::UserExtensionCommand ( const std::string& str_command )
   : RawContentCommand ()
{
   command_type = UserExtension;
   
   std::istringstream input_stream ( str_command );
   
   read ( input_stream );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::UserExtensionCommand::~UserExtensionCommand ( void )
{
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::UserExtensionCommand& command )
{
   command.read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::UserExtensionCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::UserExtensionCommand* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::UserExtensionCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

void OpenCIF::UserExtensionCommand::print ( std::ostream& output_stream )
{
   output_stream << getContent () << " ;";
   
   return;
}

void OpenCIF::UserExtensionCommand::read ( std::istream& input_stream )
{
   char character = ' ';
   std::string contents;
   
   while ( character == ' ' )
   {
      character = input_stream.get ();
   }
   
   contents = character;
   
   while ( character != ';' )
   {
      character = input_stream.get ();
      
      if ( character != ';' )
      {
         contents += character;
      }
   }
   
   while ( contents[ contents.size () - 1 ] == ' ' )
   {
      contents.erase ( contents.size () - 1 , 1 );
   }
   
   setContent ( contents );
   
   return;
}
