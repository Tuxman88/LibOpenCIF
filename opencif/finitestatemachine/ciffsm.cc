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

# include "ciffsm.h"

/*
 * Default contructor. This constructor prepares the FSM to have enough
 * states (constructor of the father class). After setting such things,
 * the constructor adds enough transitions to represent a valid FSM to
 * validate the contents of a CIF file.
 * 
 * Refer to the documentation to see a visual representation of the FSM.
 */
OpenCIF::CIFFSM::CIFFSM ( void )
   : FiniteStateMachine ( 92 ) ,// The finite state machine designed requires such amount of states to validate the contents of the CIF file.
     parentheses ( 0 )
{
   /*
    * The process to add states will be this:
    * 
    * For every state, there will be added every transition from such state.
    * After that, there will be added a new state.
    * 
    * To this point, thanks to the constructor of the father class,
    * the FSM is ready to be configured (there is enough transitions and states).
    * 
    * By default, every "jump" (transition) not configured is an invalid transition.
    * 
    * There are defined some strings and constants to ease the process of coding the transitions.
    * For example, there is a KeyValue named "LayerNameChar", that represents a digit (0 to 9) or
    * and upper char (A to Z).
    */
   
   add ( 1 , BlankChar , 1 );
   add ( 1 , "P" , 2 );
   add ( 1 , "B" , 14 );
   add ( 1 , "R" , 31 );
   add ( 1 , "W" , 40 );
   add ( 1 , "L" , 54 );
   add ( 1 , "D" , 57 );
   add ( 1 , "C" , 70 );
   add ( 1 , Digit , 88 );
   add ( 1 , "(" , 89 );
   add ( 1 , "E" , 91 );
   
   /*
    * POLYGON STATES
    */
   
   add ( 2 , BlankChar , 2 );
   add ( 2 , "-" , 3 );
   add ( 2 , Digit , 4 );
   
   add ( 3 , Digit , 4 );
   
   add ( 4 , Digit , 4 );
   add ( 4 , SeparatorChar , 5 );
   
   add ( 5 , SeparatorChar , 5 );
   add ( 5 , "-" , 6 );
   add ( 5 , Digit , 7 );
   
   add ( 6 , Digit , 7 );
   
   add ( 7 , Digit , 7 );
   add ( 7 , SeparatorChar , 8 );
   add ( 7 , ";" , 1 );
   
   add ( 8 , SeparatorChar , 8 );
   add ( 8 , "-" , 9 );
   add ( 8 , Digit , 10 );
   add ( 8 , ";" , 1 );
   
   add ( 9 , Digit , 10 );
   
   add ( 10 , Digit , 10 );
   add ( 10 , SeparatorChar , 11 );
   
   add ( 11 , SeparatorChar , 11 );
   add ( 11 , "-" , 12 );
   add ( 11 , Digit , 13 );
   
   add ( 12 , Digit , 13 );
   
   add ( 13 , SeparatorChar , 8 );
   add ( 13 , Digit , 13 );
   add ( 13 , ";" , 1 );
   
   /*
    * BOX STATES
    */
   
   add ( 14 , BlankChar , 14 );
   add ( 14 , Digit , 15 );
   
   add ( 15 , Digit , 15 );
   add ( 15 , SeparatorChar , 16 );

   add ( 16 , SeparatorChar , 16 );
   add ( 16 , Digit , 17 );
   
   add ( 17 , Digit , 17 );
   add ( 17 , SeparatorChar , 18 );
   
   add ( 18 , SeparatorChar , 18 );
   add ( 18 , "-" , 19 );
   add ( 18 , Digit , 20 );
   
   add ( 19 , Digit , 20 );
   
   add ( 20 , Digit , 20 );
   add ( 20 , SeparatorChar , 21 );
   
   add ( 21 , SeparatorChar , 21 );
   add ( 21 , "-" , 22 );
   add ( 21 , Digit , 23 );
   
   add ( 22 , Digit , 23 );
   
   add ( 23 , Digit , 23 );
   add ( 23 , SeparatorChar , 24 );
   add ( 23 , ";" , 1 );
   
   add ( 24 , SeparatorChar , 24 );
   add ( 24 , "-" , 25 );
   add ( 24 , Digit , 26 );
   add ( 24 , ";" , 1 );
   
   add ( 25 , Digit , 26 );
   
   add ( 26 , Digit , 26 );
   add ( 26 , SeparatorChar , 27 );
   
   add ( 27 , SeparatorChar , 27 );
   add ( 27 , "-" , 28 );
   add ( 27 , Digit , 29 );
   
   add ( 28 , Digit , 29 );
   
   add ( 29 , Digit , 29 );
   add ( 29 , SeparatorChar , 30 );
   add ( 29 , ";" , 1 );
   
   add ( 30 , SeparatorChar , 30 );
   add ( 30 , ";" , 1 );
   
   /*
    * ROUNDFLASH STATES
    */
   
   add ( 31 , BlankChar , 31 );
   add ( 31 , Digit , 32 );
   
   add ( 32 , Digit , 32 );
   add ( 32 , SeparatorChar , 33 );
   
   add ( 33 , SeparatorChar , 33 );
   add ( 33 , "-" , 34 );
   add ( 33 , Digit , 35 );
   
   add ( 34 , Digit , 35 );
   
   add ( 35 , Digit , 35 );
   add ( 35 , SeparatorChar , 36 );
   
   add ( 36 , SeparatorChar , 36 );
   add ( 36 , "-" , 37 );
   add ( 36 , Digit , 38 );
   
   add ( 37 , Digit , 38 );
   
   add ( 38 , Digit , 38 );
   add ( 38 , SeparatorChar , 39 );
   add ( 38 , ";" , 1 );
   
   add ( 39 , SeparatorChar , 39 );
   add ( 39 , ";" , 1 );
   
   /*
    * WIRE STATES
    */
   
   add ( 40 , BlankChar , 40 );
   add ( 40 , Digit , 41 );
   
   add ( 41 , Digit , 41 );
   add ( 41 , SeparatorChar , 42 );
   
   add ( 42 , SeparatorChar , 42 );
   add ( 42 , "-" , 43 );
   add ( 42 , Digit , 44 );
   
   add ( 43 , Digit , 44 );
   
   add ( 44 , Digit , 44 );
   add ( 44 , SeparatorChar , 45 );
   
   add ( 45 , SeparatorChar , 45 );
   add ( 45 , "-" , 46 );
   add ( 45 , Digit , 47 );
   
   add ( 46 , Digit , 47 );
   
   add ( 47 , Digit , 47 );
   add ( 47 , SeparatorChar , 48 );
   add ( 47 , ";" , 1 );
   
   add ( 48 , SeparatorChar , 48 );
   add ( 48 , "-" , 49 );
   add ( 48 , Digit , 50 );
   add ( 48 , ";" , 1 );
   
   add ( 49 , Digit , 50 );
   
   add ( 50 , Digit , 50 );
   add ( 50 , SeparatorChar , 51 );
   
   add ( 51 , SeparatorChar , 51 );
   add ( 51 , "-" , 52 );
   add ( 51 , Digit , 53 );
   
   add ( 52 , Digit , 53 );
   
   add ( 53 , SeparatorChar , 48 );
   add ( 53 , Digit , 53 );
   add ( 53 , ";" , 1 );
   
   /*
    * LAYER STATES
    */
   
   add ( 54 , BlankChar , 54 );
   add ( 54 , LayerNameChar , 55 );
   
   // Don't swap the order of this two lines, of the transition priorities are going to be broken
   // (the LayerNameChar set overwrites some BlankChar characters)
   add ( 55 , BlankChar , 56 );
   add ( 55 , LayerNameChar , 55 );
   add ( 55 , ";" , 1 );
   
   add ( 56 , BlankChar , 56 );
   add ( 56 , ";" , 1 );
   
   /*
    * DEFINITION COMMANDS (DELETE, START, END)
    */
   
   add ( 57 , BlankChar , 57 );
   add ( 57 , "S" , 58 );
   add ( 57 , "F" , 66 );
   add ( 57 , "D" , 67 );
   
   // Substates: Definition Start
   
   add ( 58 , SeparatorChar , 59 );
   add ( 58 , Digit , 60 );
   
   add ( 59 , SeparatorChar , 59 );
   add ( 59 , Digit , 60 );
   
   add ( 60 , Digit , 60 );
   add ( 60 , SeparatorChar , 61 );
   add ( 60 , ";" , 1 );
   
   add ( 61 , SeparatorChar , 61 );
   add ( 61 , Digit , 62 );
   add ( 61 , ";" , 1 );
   
   add ( 62 , Digit , 62 );
   add ( 62 , SeparatorChar , 63 );
   
   add ( 63 , SeparatorChar , 63 );
   add ( 63 , Digit , 64 );
   
   add ( 64 , Digit , 64 );
   add ( 64 , SeparatorChar , 65 );
   add ( 64 , ";" , 1 );
   
   add ( 65 , SeparatorChar , 65 );
   add ( 65 , ";" , 1 );
   
   // Substates: Definition Finish
   
   add ( 66 , SeparatorChar , 66 );
   add ( 66 , ";" , 1 );
   
   // Substates: Definition delete
   
   add ( 67 , BlankChar , 67 );
   add ( 67 , Digit , 68 );
   
   add ( 68 , Digit , 68 );
   add ( 68 , SeparatorChar , 69 );
   add ( 68 , ";" , 1 );
   
   add ( 69 , SeparatorChar , 69 );
   add ( 69 , ";" , 1 );
   
   /*
    * CALL COMMAND STATES
    */
   
   add ( 70 , BlankChar , 70 );
   add ( 70 , Digit , 71 );
   
   add ( 71 , Digit , 71 );
   add ( 71 , ";" , 1 );
   add ( 71 , BlankChar , 72 );
   add ( 71 , "T" , 73 );
   add ( 71 , "M" , 79 );
   add ( 71 , "R" , 82 );
   
   add ( 72 , BlankChar , 72 );
   add ( 72 , ";" , 1 );
   add ( 72 , "T" , 73 );
   add ( 72 , "M" , 79 );
   add ( 72 , "R" , 82 );
   
   add ( 73 , BlankChar , 73 );
   add ( 73 , "-" , 74 );
   add ( 73 , Digit , 75 );
   
   add ( 74 , Digit , 75 );
   
   add ( 75 , Digit , 75 );
   add ( 75 , SeparatorChar , 76 );
   
   add ( 76 , SeparatorChar , 76 );
   add ( 76 , "-" , 77 );
   add ( 76 , Digit , 78 );
   
   add ( 77 , Digit , 78 );
   
   add ( 78 , Digit , 78 );
   add ( 78 , BlankChar , 72 );
   add ( 78 , ";" , 1 );
   add ( 78 , "M" , 79 );
   add ( 78 , "R" , 82 );
   add ( 78 , "T" , 73 );
   
   add ( 79 , BlankChar , 79 );
   add ( 79 , "X" , 80 );
   add ( 79 , "Y" , 81 );
   
   add ( 80 , BlankChar , 72 );
   add ( 80 , ";" , 1 );
   add ( 80 , "T" , 73 );
   add ( 80 , "R" , 82 );
   add ( 80 , "M" , 79 );
   
   add ( 81 , BlankChar , 72 );
   add ( 81 , ";" , 1 );
   add ( 81 , "T" , 73 );
   add ( 81 , "R" , 82 );
   add ( 81 , "M" , 79 );
   
   add ( 82 , BlankChar , 82 );
   add ( 82 , "-" , 83 );
   add ( 82 , Digit , 84 );
   
   add ( 83 , Digit , 84 );
   
   add ( 84 , Digit , 84 );
   add ( 84 , SeparatorChar , 85 );
   
   add ( 85 , SeparatorChar , 85 );
   add ( 85 , "-" , 86 );
   add ( 85 , Digit , 87 );
   
   add ( 86 , Digit , 87 );
   
   add ( 87 , Digit , 87 );
   add ( 87 , BlankChar , 72 );
   add ( 87 , ";" , 1 );
   add ( 87 , "T" , 73 );
   add ( 87 , "M" , 79 );
   add ( 87 , "R" , 82 );
   
   /*
    * DELETE COMMAND STATES
    */
   
   add ( 88 , ExtentionChar , 88 );
   add ( 88 , ";" , 1 );
   
   /*
    * COMMENT STATES
    */
   
   add ( 89 , CommentChar , 89 );
   add ( 89 , ")" , 90 );
   
   add ( 90 , BlankChar , 90 );
   add ( 90 , ";" , 1 );
   
   /*
    * END COMMAND STATES
    */
   
   add ( 91 , SeparatorChar , 91 );
   add ( 91 , ";" , 92 );
   
   add ( 92 , SeparatorChar , 92 );
}

/*
 * Destructor. Nothing to do.
 */
OpenCIF::CIFFSM::~CIFFSM ( void )
{
}

/* 
 * Member function to add a special group of transitions.
 */
void OpenCIF::CIFFSM::add ( const int& input_state , const OpenCIF::CIFFSM::Transition& input_chars , const int& output_state )
{
   std::string tmp;
   
   switch ( input_chars )
   {
      case Digit:
         for ( int i = '0'; i <= '9'; i++ )
         {
            tmp = (char)i;
            add ( input_state , tmp , output_state );
         }
         break;
         
      case UpperChar:
         for ( int i = 'A'; i <= 'Z'; i++ )
         {
            tmp = (char)i;
            add ( input_state , tmp , output_state );
         }
         break;
         
      case BlankChar:
         for ( int i = 0; i < 256; i++ )
         {
            if ( !( std::isdigit ( i ) ||
                    std::isupper ( i ) ||
                    i == '-' || 
                    i == '(' ||
                    i == ')' ||
                    i == ';' ) )
            {
               tmp = (char)i;
               add ( input_state , tmp , output_state );
            }
         }
         break;
         
      case UserChar:
         for ( int i = 0; i < 256; i++ )
         {
            if ( i != ';' )
            {
               tmp = (char)i;
               add ( input_state , tmp , output_state );
            }
         }
         break;
         
      case CommentChar:
         for ( int i = 0; i < 256; i++ )
         {
            tmp = (char)i;
            add ( input_state , tmp , output_state );
         }
         break;
         
      case SeparatorChar:
         add ( input_state , UpperChar , output_state );
         add ( input_state , BlankChar , output_state );
         break;
         
      case LayerNameChar:
         add ( input_state , Digit , output_state );
         add ( input_state , UpperChar , output_state );
         add ( input_state , "_" , output_state );
         break;
         
      case ExtentionChar:
         for ( int i = 0; i < 256; i++ )
         {
            if ( i != ';' )
            {
               tmp = (char)i;
               add ( input_state , tmp , output_state );
            }
         }
         break;
         
      default:
         std::cerr << "OpenCIF->CIFFSM->add: Logical error detected." << std::endl;
         std::cerr << "                      Adding a special group of input chars, detected an unknown group of values." << std::endl;
         std::cerr << "                      Such group will be skipped, but there can be errors validating files." << std::endl;
         break;
   }
   
   return;
}

/*
 * Member function to return the next state of the FSM based in an input char.
 * 
 * This member function takes the input char. If the current state is other but those
 * ones for the comment command, only passes to the member of the parent class.
 * 
 * If the current state if one of those ones for the comment command, there is needed
 * to take care of he parentheses that open and closes.
 * 
 * The CIF file format stablish that there should be a balanced amount of them in a
 * command.
 * 
 * Something like this:
 * 
 *      ( This is a valid comment );
 *      ((This is also a valid comment));
 *      (This a (valid) (comment) ((because is balanced))());
 * 
 *      (( This comment is invalid);
 *      (This other ()()()(())) is also invalid);
 * 
 * So, internally, the CIFFSM should have a control of the parentheses that
 * opens and those that close.
 */

int OpenCIF::CIFFSM::operator[] ( const char& input_char )
{
   int new_state = -1;
   
   // Ok. If I'm at state 1 AND the input char is a parentheses '(', then, increase
   // the parentheses counter by 1 and do the jump.
   
   // If the current state is 89 AND the input char is a parentheses '(', then,
   // increase the parentheses counter by 1, but don't perform the jump.
   
   // If the current state is 89 AND the input char is a parentheses ')' AND
   // the parentheses counter is more than 1, substract 1 from it but don't
   // perform the jump.
   
   // If the current state is 89 AND the input char is a parentheses ')' AND
   // the parentheses counter is equal to 1, substract 1 from it AND perform
   // the jump.
   
   if ( currentState () == 1 && input_char == '(' )
   {
      new_state = FiniteStateMachine::operator[] ( input_char );
      parentheses++;
   }
   else if ( currentState () == 89 )
   {
      if ( input_char == '(' )
      {
         parentheses++;
         new_state = currentState ();
      }
      else if ( input_char == ')' )
      {
         if ( parentheses > 1 )
         {
            parentheses--;
            new_state = currentState ();
         }
         else if ( parentheses == 1 )
         {
            parentheses = 0;
            new_state = FiniteStateMachine::operator[] ( input_char );
         }
         else
         {
            new_state = -1;
         }
      }
      else
      {
         new_state = FiniteStateMachine::operator[] ( input_char );
      }
   }
   else
   {
      new_state = FiniteStateMachine::operator[] ( input_char );
   }
    
   return ( new_state );
}

void OpenCIF::CIFFSM::add ( const int& input_state, const std::string& input_chars, const int& output_state )
{
   FiniteStateMachine::add ( input_state , input_chars , output_state );
   
   return;
}
