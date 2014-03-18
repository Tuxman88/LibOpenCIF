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

# include "userextentioncommand.h"

/*
 * Default constructor. Nothing to do.
 */
OpenCIF::UserExtentionCommand::UserExtentionCommand ( void )
   : RawContentCommand ()
{
   command_type = UserExtention;
}

OpenCIF::UserExtentionCommand::UserExtentionCommand ( const std::string& str_command )
   : RawContentCommand ()
{
   command_type = UserExtention;
   
   char character = ' ';
   std::string contents;
   std::istringstream input_stream ( str_command );
   
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
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::UserExtentionCommand::~UserExtentionCommand ( void )
{
}


std::istream& operator>> ( std::istream& input_stream , OpenCIF::UserExtentionCommand& command )
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
   
   command.setContent ( contents );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , const OpenCIF::UserExtentionCommand& command )
{
   output_stream << command.getContent () << " ;";
   
   return ( output_stream );
}
