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

# include "layercommand.h"

/*
 * Default constructor. Nothing to do.
 */
OpenCIF::LayerCommand::LayerCommand ( void )
   : Command ()
{
   command_type = Layer;
}

OpenCIF::LayerCommand::LayerCommand ( const std::string& str_command )
   : Command ()
{
   command_type = Layer;
   
   std::istringstream input_stream ( str_command );
   std::string word;
   
   // Read the "L" section of the command and the layer name
   input_stream >> word >> word;
   
   setName ( word );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::LayerCommand::~LayerCommand ( void )
{
}

/*
 * Member function that returns the name of the layer.
 */
std::string OpenCIF::LayerCommand::getName ( void ) const
{
   return ( layer_name );
}

/*
 * Member function to set the name of the layer.
 */
void OpenCIF::LayerCommand::setName ( const std::string& new_name )
{
   layer_name = new_name;
   
   return;
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::LayerCommand& command )
{
   std::string word;
   
   // Read the "L" section of the command and the layer name
   input_stream >> word >> word;
   
   command.setName ( word );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , const OpenCIF::LayerCommand& command )
{
   output_stream << "L " << command.getName () << " ;";
   
   return ( output_stream );
}