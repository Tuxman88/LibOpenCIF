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

# include "commentcommand.h"

/*
 * Default contructor. Nothing to do.
 */
OpenCIF::CommentCommand::CommentCommand ( void )
   : RawContentCommand ()
{
   command_type = Comment;
}

OpenCIF::CommentCommand::CommentCommand ( const std::string& str_command )
   : RawContentCommand ()
{
   command_type = Comment;
   
   std::istringstream input_stream ( str_command );
   
   read ( input_stream );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::CommentCommand::~CommentCommand ( void )
{
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::CommentCommand& command )
{
   command.read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::CommentCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::CommentCommand* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::CommentCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

void OpenCIF::CommentCommand::print ( std::ostream& output_stream )
{
   output_stream << getContent () << " ;";
   
   return;
}

void OpenCIF::CommentCommand::read ( std::istream& input_stream )
{
   // Read chars until the parentheses end and I read the semicolon.
   
   char character = '_';
   std::string content;
   
   while ( character != '(' )
   {
      character = input_stream.get ();
   }
   
   content = "(";
   
   unsigned long int parentheses = 1;
   
   while ( parentheses != 0 )
   {
      character = input_stream.get ();
      content += character;
      
      parentheses += ( character == '(' ) ? 1 : ( character == ')' ) ? -1 : 0;
   }
   
   // Ok, I have the last parentheses. Read and omit unti the semicolon
   
   while ( character != ';' )
   {
      character = input_stream.get ();
   }
   
   setContent ( content );
   
   return;
}
