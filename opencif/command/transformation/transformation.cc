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

# include "transformation.h"

/*
 * Constructor. Initialices the instance as a Displacement transformation,
 * with a displacement value of 0,0 (neutral movement).
 */
OpenCIF::Transformation::Transformation ( void )
{
   transformation_point.set ( 0 , 0 );
   setType ( Displacement );
}

/*
 * Nothing to do.
 */
OpenCIF::Transformation::~Transformation ( void )
{
}

/*
 * This member function returns the point stored in the instance. The point is the same
 * for the displacements and rotations, so, since the transformation can only be one or
 * another (but not both at the same time), there is only one point.
 */
OpenCIF::Point OpenCIF::Transformation::getDisplacement ( void ) const
{
   return ( transformation_point );
}

/*
 * This member function returns the point stored in the instance. The point is the same
 * for the displacements and rotations, so, since the transformation can only be one or
 * another (but not both at the same time), there is only one point.
 */
OpenCIF::Point OpenCIF::Transformation::getRotation ( void ) const
{
   return ( transformation_point );
}

/*
 * This member function returns the type of the current instance.
 */
OpenCIF::Transformation::TransformationType OpenCIF::Transformation::getType ( void ) const
{
   return ( transformation_type );
}

/*
 * This member function accepts a new point. Such point represents the displacement
 * to perform.
 */
void OpenCIF::Transformation::setDisplacement ( const OpenCIF::Point& new_displacement )
{
   transformation_point = new_displacement;
   
   return;
}

/*
 * This member function accepts a new point. Such point represents the rotation to
 * perform.
 */
void OpenCIF::Transformation::setRotation ( const OpenCIF::Point& new_rotation )
{
   transformation_point = new_rotation;
   
   return;
}

/*
 * This member function sets the type of the transformation.
 */
void OpenCIF::Transformation::setType ( const OpenCIF::Transformation::TransformationType& new_type )
{
   transformation_type = new_type;
   
   return;
}

/*
 * This overloaded operator writes a transformation instance into an output stream.
 */
std::ostream& operator<< ( std::ostream& output_stream , const OpenCIF::Transformation& transformation )
{
   switch ( transformation.getType () )
   {
      case OpenCIF::Transformation::Displacement:
         output_stream << "T ";
         output_stream << transformation.getDisplacement ();
         break;
         
      case OpenCIF::Transformation::Rotation:
         output_stream << "R ";
         output_stream << transformation.getRotation ();
         break;
         
      case OpenCIF::Transformation::VerticalMirroring:
         output_stream << "M Y";
         break;
         
      case OpenCIF::Transformation::HorizontalMirroring:
         output_stream << "M X";
         break;
   }
   
   return ( output_stream );
}

/*
 * This overloaded operator loads a transformation instance from an input stream.
 */
std::istream& operator>> ( std::istream& input_stream , OpenCIF::Transformation& transformation )
{
   std::string type;
   OpenCIF::Point point;
   
   input_stream >> type;
   
   switch ( type[ 0 ] )
   {
      case 'T':
         input_stream >> point;
         transformation.setDisplacement ( point );
         transformation.setType ( OpenCIF::Transformation::Displacement );
         break;
         
      case 'R':
         input_stream >> point;
         transformation.setRotation ( point );
         transformation.setType ( OpenCIF::Transformation::Rotation );
         break;
         
      case 'M':
         input_stream >> type;
         transformation.setType ( ( type == "X" ) ? OpenCIF::Transformation::HorizontalMirroring : OpenCIF::Transformation::VerticalMirroring );
         break;
   }
   
   return ( input_stream );
}
