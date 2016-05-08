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

# ifndef LIBOPENCIF_CALLCOMMAND_HH_
# define LIBOPENCIF_CALLCOMMAND_HH_

# include <iostream>
# include <vector>
# include <sstream>
# include <string>

# include "../controlcommand.hh"
# include "../../transformation/transformation.hh"

// Forward declarations
namespace OpenCIF { class CallCommand; }
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::CallCommand& command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::CallCommand& command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::CallCommand* command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::CallCommand* command );

namespace OpenCIF
{
   class CallCommand : public OpenCIF::ControlCommand
   {
      public:
         explicit CallCommand ( void );
         explicit CallCommand ( const std::string& str_command );
         virtual ~CallCommand ( void );
         
         void setTransformations ( const std::vector< OpenCIF::Transformation >& new_transformations );
         void addTransformation ( const OpenCIF::Transformation& new_transformation );
         std::vector< OpenCIF::Transformation >& getTransformations ( void );
         
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , CallCommand& command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , CallCommand& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , CallCommand* command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , CallCommand* command );
         
      protected:
         virtual void print ( std::ostream& output_stream );
         virtual void read ( std::istream& input_stream );
         
      private:
         std::vector< OpenCIF::Transformation > call_transformations;
   };
}

# endif
