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

# include "definitionstartcommand.h"

/*
 * Default constructor. Nothing to do.
 */
OpenCIF::DefinitionStartCommand::DefinitionStartCommand ( void )
   : ControlCommand ()
{
   command_type = DefinitionStart;
}

OpenCIF::DefinitionStartCommand::DefinitionStartCommand ( const std::string& str_command )
   : ControlCommand ()
{
   command_type = DefinitionStart;
   
   std::istringstream input_stream ( str_command );
   std::string word;
   unsigned long int id;
   
   input_stream >> word >> word >> id;
   
   setID ( id );
   
   // Read the next components. If is a semicolon, do nothing. Otherwise, is an AB value
   input_stream >> word;
   
   if ( word != ";" )
   {
      std::istringstream iss ( word );
      unsigned long int a , b;
      iss >> a;
      input_stream >> b;
      
      OpenCIF::Fraction fraction;
      fraction.set ( a , b );
      
      setAB ( fraction );
   }
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::DefinitionStartCommand::~DefinitionStartCommand ( void )
{
}

/*
 * This member function returns the AB value of this command.
 */
OpenCIF::Fraction OpenCIF::DefinitionStartCommand::getAB ( void ) const
{
   return ( command_ab );
}

/*
 * This member function sets the AB value of the command.
 */
void OpenCIF::DefinitionStartCommand::setAB ( const OpenCIF::Fraction& new_ab )
{
   command_ab = new_ab;
   
   return;
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionStartCommand& command )
{
   // Read the first two useless parts and the ID
   std::string word;
   unsigned long int id;
   
   input_stream >> word >> word >> id;
   
   command.setID ( id );
   
   // Read the next components. If is a semicolon, do nothing. Otherwise, is an AB value
   input_stream >> word;
   
   if ( word != ";" )
   {
      std::istringstream iss ( word );
      unsigned long int a , b;
      iss >> a;
      input_stream >> b;
      
      OpenCIF::Fraction fraction;
      fraction.set ( a , b );
      
      command.setAB ( fraction );
   }
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , const OpenCIF::DefinitionStartCommand& command )
{
   output_stream << "D S " << command.getID () << " " << command.getAB () << " ;";
   
   return ( output_stream );
}