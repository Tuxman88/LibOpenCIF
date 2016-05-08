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

# ifndef LIBOPENCIF_DEFINITIONDELETECOMMAND_HH_
# define LIBOPENCIF_DEFINITIONDELETECOMMAND_HH_

# include <iostream>
# include <sstream>
# include <string>

# include "../controlcommand.hh"

namespace OpenCIF { class DefinitionDeleteCommand; }
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionDeleteCommand& command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionDeleteCommand& command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::DefinitionDeleteCommand* command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::DefinitionDeleteCommand* command );

namespace OpenCIF
{
   class DefinitionDeleteCommand : public OpenCIF::ControlCommand
   {
      public:
         explicit DefinitionDeleteCommand ( void );
         explicit DefinitionDeleteCommand ( const std::string& str_command );
         virtual ~DefinitionDeleteCommand ( void );
         
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , DefinitionDeleteCommand& command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , DefinitionDeleteCommand& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , DefinitionDeleteCommand* command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , DefinitionDeleteCommand* command );
         
      protected:
         virtual void print ( std::ostream& output_stream );
         virtual void read ( std::istream& input_stream );
   };
}

# endif
