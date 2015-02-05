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

# include "state.hh"

/*
 * Default constructor. Initialice the vector of states.
 */
OpenCIF::State::State ( void )
{
   reset ();
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::State::~State ( void )
{
}

/*
 * Member function to reset the transitions.
 */
void OpenCIF::State::reset ( void )
{
   for ( int i = 0; i < 256; i++ )
   {
      state_options[ i ] = -1;
   }
   
   return;
}

/*
 * Member function to add transitions based in some strings, to some state.
 */
void OpenCIF::State::addOptions ( const std::string& new_options , const int& exit_state )
{
   for ( unsigned int i = 0; i < new_options.size (); i++ )
   {
      state_options[ (int)(new_options[ i ]) ] = exit_state;
   }
   
   return;
}

/*
 * Overloaded operator to access the transition based on the input char.
 */
int OpenCIF::State::operator[] ( const char& input_char )
{
   return ( state_options[ (int)input_char ] );
}
