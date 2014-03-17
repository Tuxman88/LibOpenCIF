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

# ifndef LIBOPENCIF_FRACTION_H_
# define LIBOPENCIF_FRACTION_H_

# include <iostream>

namespace OpenCIF { class Fraction; }
std::istream& operator>> ( std::istream& input_stream , OpenCIF::Fraction& command );
std::ostream& operator<< ( std::ostream& output_stream , const OpenCIF::Fraction& command );

namespace OpenCIF
{
   class Fraction
   {
      public:
         explicit Fraction ( void );
         virtual ~Fraction ( void );
         
         void set ( const unsigned long int& new_numerator , const unsigned long int& new_denominator );
         
         void setNumerator ( const unsigned long int& new_numerator );
         unsigned long int getNumerator ( void ) const;
         
         void setDenominator ( const unsigned long int& new_denominator );
         unsigned long int getDenominator ( void ) const;
         
         friend std::istream& (::operator>>) ( std::istream& input_stream , Fraction& command );
         friend std::ostream& (::operator<<) ( std::ostream& output_stream , const Fraction& command );
         
      private:
         unsigned long int fraction_numerator;
         unsigned long int fraction_denominator;
   };
}

# endif
