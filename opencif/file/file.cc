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

# include "file.h"

/*
 * Default constructor. Nothing to do.
 */
OpenCIF::File::File ( void )
{
}

/*
 * Destructor. Delete the commands stored (if any).
 */
OpenCIF::File::~File ( void )
{
   for ( int i = 0; i < file_commands.size (); i++ )
   {
      delete file_commands[ i ];
      file_commands[ i ] = 0;
   }
}

/*
 * Member function to return the commands vector.
 */
std::vector< OpenCIF::Command* > OpenCIF::File::getCommands ( void ) const
{
   return ( file_commands );
}

/*
 * Member function to return the file path.
 */
std::string OpenCIF::File::getPath ( void ) const
{
   return ( file_path );
}

/*
 * Member function to set a vector of commands.
 */
void OpenCIF::File::setCommands ( const std::vector< OpenCIF::Command* >& new_commands )
{
   file_commands = new_commands;
   
   return;
}

/*
 * Member function to set the path to the file.
 */
void OpenCIF::File::setPath ( const std::string& new_path )
{
   file_path = new_path;
   
   return;
}

/*
 * Member function to return the messages generated during the load of the file.
 */
std::vector< std::string > OpenCIF::File::getMessages ( void )
{
   return ( file_messages );
}

/*
 * Member function to load the input file. There is returned a LoadStatus
 * value that indicates the result of the process.
 */
OpenCIF::File::LoadStatus OpenCIF::File::loadFile ( void )
{
   LoadStatus end_status;
   
   file_messages.clear ();
   
   end_status = openFile ();
   
   if ( end_status != AllOk )
   {
      return ( end_status );
   }
   
   end_status = validateSintax ();
   
   if ( end_status != AllOk )
   {
      return ( end_status );
   }
   
   end_status = loadCommands ();
   
   if ( end_status != AllOk )
   {
      return ( end_status );
   }
   
   return ( AllOk );
}

/*
 * This member function try to open the input file.
 */
OpenCIF::File::LoadStatus OpenCIF::File::openFile ( void )
{
   if ( file_input.is_open () )
   {
      file_messages.push_back ( std::string ( "File:openFile:Warning: Input file already opened. Closing." ) );
      file_input.close ();
   }
   
   file_input.open ( file_path.c_str () );
   
   if ( !file_input.is_open () )
   {
      file_messages.push_back ( std::string ( "File:openFile:Error: Can't open input file." ) );
      
      return ( CantOpenInputFile );
   }
   
   return ( AllOk );
}

/*
 * This member function validates the contents of the input file using
 * a finite state machine.
 */
OpenCIF::File::LoadStatus OpenCIF::File::validateSintax ( void )
{
   return ( AllOk );
}

/*
 * This member function loads the contents of the input file and converts them
 * into Command instances.
 */
OpenCIF::File::LoadStatus OpenCIF::File::loadCommands ( void )
{
   return ( AllOk );
}
