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

# ifndef LIBOPENCIF_SIZE_HH_
# define LIBOPENCIF_SIZE_HH_

# include <iostream>
# include <string>
# include <sstream>

namespace OpenCIF { class Size; }
std::istream& operator>> ( std::istream& input_stream , OpenCIF::Size& command );
std::ostream& operator<< ( std::ostream& output_stream , const OpenCIF::Size& command );

namespace OpenCIF
{
   class Size
   {
      public:
         explicit Size ( void );
         explicit Size ( const unsigned long int& new_width , const unsigned long int& new_height );
         virtual ~Size ( void );
         unsigned long int getWidth ( void ) const;
         unsigned long int getHeight ( void ) const;
         void setWidth ( const unsigned long int& new_width );
         void setHeight ( const unsigned long int& new_height );
         void set ( const unsigned long int& new_width , const unsigned long int& new_height );
         
         friend std::istream& (::operator>>) ( std::istream& input_stream , Size& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , const Size& command );
         
      private:
         unsigned long int size_width;
         unsigned long int size_height;
   };
}

# endif
