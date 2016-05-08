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

# include "wirecommand.hh"

/*
 * Default constructor. Initialize command. The wire must have a size not equal to 0.
 */
OpenCIF::WireCommand::WireCommand ( void )
   : PathBasedCommand ()
{
   command_type = Wire;
   wire_width = 1;
}

/*
 * Non-Default constructor. Initialize the command instance using a string representing the command itself.
 */
OpenCIF::WireCommand::WireCommand ( const std::string& str_command )
   : PathBasedCommand ()
{
   command_type = Wire;
   
   std::string word;
   std::istringstream input_stream ( str_command );
   unsigned long int width;
   
   // Read the W and ID parts
   input_stream >> word >> width;
   
   setWidth ( width );
   
   input_stream >> word;
   
   while ( word != ";" )
   {
      std::istringstream iss ( word );
      long int x , y;
      iss >> x;
      input_stream >> y;
      
      OpenCIF::Point point ( x , y );
      
      command_points.push_back ( point );
      
      input_stream >> word;
   }
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::WireCommand::~WireCommand ( void )
{
}

/*
 * Member function to return the width of the wire.
 */
long unsigned int OpenCIF::WireCommand::getWidth ( void ) const
{
   return ( wire_width );
}

/*
 * Member function to set the width of the command.
 */
void OpenCIF::WireCommand::setWidth ( const long unsigned int& new_width )
{
   wire_width = new_width;
   
   return;
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::WireCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::WireCommand& command )
{
   command.read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::WireCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::WireCommand* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

void OpenCIF::WireCommand::print ( std::ostream& output_stream )
{
   output_stream << "W " << wire_width << " ";
   
   for ( unsigned long int i = 0; i < command_points.size (); i++ )
   {
      output_stream << command_points.at ( i ) << " ";
   }
   
   output_stream << ";";
   
   return;
}

void OpenCIF::WireCommand::read ( std::istream& input_stream )
{
   std::string word;
   unsigned long int width;
   
   // Read the W and ID parts
   input_stream >> word >> width;
   
   setWidth ( width );
   
   input_stream >> word;
   
   while ( word != ";" )
   {
      std::istringstream iss ( word );
      long int x , y;
      iss >> x;
      input_stream >> y;
      
      OpenCIF::Point point ( x , y );
      
      command_points.push_back ( point );
      
      input_stream >> word;
   }
   
   return;
}
