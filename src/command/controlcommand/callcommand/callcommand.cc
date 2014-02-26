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

# include "callcommand.h"

/*
 * Default constructor. Nothing to do.
 */
OpenCIF::CallCommand::CallCommand ( void )
   : ControlCommand ()
{
   command_type = Call;
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
std::vector< OpenCIF::Transformation > OpenCIF::CallCommand::getTransformations ( void ) const
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
