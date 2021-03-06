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

# include "polygoncommand.hh"

/*
 * Default constructor. Nothing to do.
 */
OpenCIF::PolygonCommand::PolygonCommand ( void )
   : PathBasedCommand ()
{
   command_type = Polygon;
}

OpenCIF::PolygonCommand::PolygonCommand ( const std::string& str_command )
   : PathBasedCommand ()
{
   command_type = Polygon;
   
   std::istringstream input_stream ( str_command );
   std::string word;
   
   input_stream >> word >> word;
   
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
OpenCIF::PolygonCommand::~PolygonCommand ( void )
{
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::PolygonCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::PolygonCommand& command )
{
   command.read ( input_stream );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::PolygonCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::PolygonCommand* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

void OpenCIF::PolygonCommand::print ( std::ostream& output_stream )
{
   output_stream << "P ";
   
   for ( unsigned long int i = 0; i < getPoints ().size (); i++ )
   {
      output_stream << getPoints ()[ i ] << " ";
   }
   
   output_stream << ";";
   
   return;
}

void OpenCIF::PolygonCommand::read ( std::istream& input_stream )
{
   std::string word;
   
   input_stream >> word >> word;
   
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
