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

# include "callcommand.hh"

/*
 * Default constructor. Nothing to do.
 */
OpenCIF::CallCommand::CallCommand ( void )
   : ControlCommand ()
{
   command_type = Call;
}

/*
 * Specialized constructor. Takes as argument a command in string form.
 * The commas must be clean. That means that, a command like this:
 * 
 *      C100muajajajaja,R100,-100T100,900MXMY;
 * 
 * Is correct, but is not supported. The correct format must be this:
 * 
 *      C 100 R 100 -100 T 100 900 M X M Y ;
 * 
 * That is neccesary since the command will used as the input of an
 * input stream, and the components will be loaded as individual strings.
 * 
 * Take in consideraton the previous indication, since the constructor
 * DONESN'T CHECK the command format.
 */
OpenCIF::CallCommand::CallCommand ( const std::string& str_command )
   : ControlCommand ()
{
   command_type = Call;
   
   std::istringstream input_stream ( str_command );
   read ( input_stream );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::CallCommand::~CallCommand ( void )
{
}

/*
 * This member function returns a copy of the vector with the transformations.
 */
std::vector< OpenCIF::Transformation >& OpenCIF::CallCommand::getTransformations ( void )
{
   return ( call_transformations );
}

/*
 * This member function adds a single transformation to the transformation vector.
 */
void OpenCIF::CallCommand::addTransformation ( const OpenCIF::Transformation& new_transformation )
{
   call_transformations.push_back ( new_transformation );
   
   return;
}

/*
 * This member functions receives a new vector of transformations, and stores it.
 */
void OpenCIF::CallCommand::setTransformations ( const std::vector< OpenCIF::Transformation >& new_transformations )
{
   call_transformations.clear ();
   call_transformations = new_transformations;
   
   return;
}

/*
 * This overloaded operator helps to write a call command to a output stream.
 */
std::ostream& operator << ( std::ostream& output_stream , OpenCIF::CallCommand& command )
{
   command.print ( output_stream );
   
   return ( output_stream );
}

/*
 * This overloaed operator helps to read a call command from an input stream.
 */
std::istream& operator >> ( std::istream& input_stream , OpenCIF::CallCommand& command )
{
   command.read ( input_stream );
   
   return ( input_stream );
}

/*
 * This overloaded operator helps to write a call command to a output stream.
 */
std::ostream& operator << ( std::ostream& output_stream , OpenCIF::CallCommand* command )
{
   command->print ( output_stream );
   
   return ( output_stream );
}

/*
 * This overloaed operator helps to read a call command from an input stream.
 */
std::istream& operator >> ( std::istream& input_stream , OpenCIF::CallCommand* command )
{
   command->read ( input_stream );
   
   return ( input_stream );
}

void OpenCIF::CallCommand::print ( std::ostream& output_stream )
{
   output_stream << "C "; // Start of the command
   output_stream << getID () << " "; // ID of the call command.
   
   for ( unsigned int i = 0; i < call_transformations.size (); i++ )
   {
      output_stream << call_transformations.at ( i ) << " ";
   }
   
   output_stream << ";";
   
   return;
}

void OpenCIF::CallCommand::read ( std::istream& input_stream )
{
   std::string word;
   unsigned long int value;
   
   // Extract the "C", and then the ID
   
   input_stream >> word >> value;
   
   setID ( value );
   
   // Extract next part. It can be a semicolon (end of all) or transformations
   input_stream >> word;
   
   while ( word != ";" )
   {
      OpenCIF::Transformation new_transformation;
      
      if ( word == "R" )
      {
         OpenCIF::Point point;
         input_stream >> point;
         new_transformation.setType ( OpenCIF::Transformation::Rotation );
         new_transformation.setRotation ( point );
      }
      else if ( word == "T" )
      {
         OpenCIF::Point point;
         input_stream >> point;
         new_transformation.setType ( OpenCIF::Transformation::Displacement );
         new_transformation.setDisplacement ( point );
      }
      else
      {
         // Mirroring
         input_stream >> word;
         new_transformation.setType ( ( word == "X" ) ? OpenCIF::Transformation::HorizontalMirroring : OpenCIF::Transformation::VerticalMirroring );
      }
      
      addTransformation ( new_transformation );
      input_stream >> word;
   }
   
   return;
}
