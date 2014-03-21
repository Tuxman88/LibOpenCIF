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

# ifndef LIBOPENCIF_ROUNDFLASHCOMMAND_H_
# define LIBOPENCIF_ROUNDFLASHCOMMAND_H_

# include "positionbasedcommand.h"

namespace OpenCIF { class RoundFlashCommand; }
std::istream& operator>> ( std::istream& input_stream , OpenCIF::RoundFlashCommand& command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::RoundFlashCommand& command );
std::istream& operator>> ( std::istream& input_stream , OpenCIF::RoundFlashCommand* command );
std::ostream& operator<< ( std::ostream& output_stream , OpenCIF::RoundFlashCommand* command );

namespace OpenCIF
{
   class RoundFlashCommand : public OpenCIF::PositionBasedCommand
   {
      public:
         explicit RoundFlashCommand ( void );
         explicit RoundFlashCommand ( const std::string& str_command );
         virtual ~RoundFlashCommand ( void );
         void setDiameter ( const unsigned long int& new_diameter );
         unsigned long int getDiameter ( void ) const;
         
         friend std::istream& (::operator>>) ( std::istream& input_stream , RoundFlashCommand& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , RoundFlashCommand& command );
         friend std::istream& (::operator>>) ( std::istream& input_stream , RoundFlashCommand* command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , RoundFlashCommand* command );
         
      protected:
         virtual void print ( std::ostream& output_stream );
         virtual void read ( std::istream& input_stream );
         
      private:
         unsigned long int round_diameter;
   };
}

# endif


