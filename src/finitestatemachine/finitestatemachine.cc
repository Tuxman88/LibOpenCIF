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

# include "finitestatemachine.h"

/*
 * Constructor. Initialice the FSM.
 */
OpenCIF::FiniteStateMachine::FiniteStateMachine ( const int& state_account )
{
   for ( int i = 0; i < ( state_account + 1 ); i++ )
   {
      OpenCIF::State state;
      fsm_states.push_back ( state );
   }
   
   fsm_current_state = 1;
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::FiniteStateMachine::~FiniteStateMachine ( void )
{
}

/*
 * Member function to add a new state transition.
 */
void OpenCIF::FiniteStateMachine::add ( const int& input_state , const std::string& input_chars , const int& output_state )
{
   fsm_states[ input_state ].addOptions ( input_chars , output_state );
   
   return;
}

/*
 * Member function to get the new state of the FSM based in an input char.
 */
int OpenCIF::FiniteStateMachine::operator[] ( const char& input_char )
{
   return ( fsm_current_state = fsm_states[ fsm_current_state ][ input_char ] , fsm_current_state );
}

/*
 * Member function to reset the FSM.
 */
void OpenCIF::FiniteStateMachine::reset ( void )
{
   fsm_current_state = 1;
   
   return;
}
