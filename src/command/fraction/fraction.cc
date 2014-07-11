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

# include "fraction.h"

/*
 * Default constructor. Sets the default values of 1/1 (a neutral fraction).
 */
OpenCIF::Fraction::Fraction ( void )
{
   set ( 1 , 1 );
}

/*
 * Non-Default constructor.
 */
OpenCIF::Fraction::Fraction ( const unsigned long int& new_numerator , const unsigned long int& new_denominator )
{
   set ( new_numerator , new_denominator );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::Fraction::~Fraction(void)
{
}

/*
 * This member function returns the denominator of the fraction.
 */
unsigned long int OpenCIF::Fraction::getDenominator ( void ) const
{
   return ( fraction_denominator );
}

/*
 * This member function returns the numerator of the fraction.
 */
unsigned long int OpenCIF::Fraction::getNumerator ( void ) const
{
   return ( fraction_numerator );
}

/*
 * This member function sets the denominator of the fraction
 */
void OpenCIF::Fraction::setDenominator ( const unsigned long int& new_denominator )
{
   fraction_denominator = new_denominator;
   
   return;
}

/*
 * This member function sets the numerator of the fraction.
 */
void OpenCIF::Fraction::setNumerator ( const unsigned long int& new_numerator )
{
   fraction_numerator = new_numerator;
   
   return;
}

/*
 * This member functions helps to set the whole value of the fraction in a single call.
 */
void OpenCIF::Fraction::set ( const long unsigned int& new_numerator , const long unsigned int& new_denominator )
{
   setNumerator ( new_numerator );
   setDenominator ( new_denominator );
   
   return;
}

std::istream& operator>> ( std::istream& input_stream , OpenCIF::Fraction& command )
{
   unsigned long int numerator, denominator;
   
   input_stream >> numerator >> denominator;
   
   command.set ( numerator , denominator );
   
   return ( input_stream );
}

std::ostream& operator<< ( std::ostream& output_stream , const OpenCIF::Fraction& command )
{
   output_stream << command.getNumerator () << " " << command.getDenominator ();
   
   return ( output_stream );
}
