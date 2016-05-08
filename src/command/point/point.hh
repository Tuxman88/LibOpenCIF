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

# ifndef LIBOPENCIF_POINT_HH_
# define LIBOPENCIF_POINT_HH_

# include <iostream>

namespace OpenCIF { class Point; }
std::istream& operator>> ( std::istream& input_stream , OpenCIF::Point& point );
std::ostream& operator<< ( std::ostream& output_stream , const OpenCIF::Point& point );

namespace OpenCIF
{
   class Point
   {
      public:
         explicit Point ( void );
         explicit Point ( const long int& new_x , const long int& new_y );
         virtual ~Point ( void );
         void setX ( const long int& new_x );
         void setY ( const long int& new_y );
         void set ( const long int& new_x , const long int& new_y );
         long int getX ( void ) const;
         long int getY ( void ) const;
         
         friend std::istream& (::operator>>) ( std::istream& input_stream , Point& point );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , const Point& point );
         
      private:
         long int point_x;
         long int point_y;
   };
}

# endif
