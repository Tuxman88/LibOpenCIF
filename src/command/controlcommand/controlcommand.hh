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

# ifndef LIBOPENCIF_CONTROLCOMMAND_HH_
# define LIBOPENCIF_CONTROLCOMMAND_HH_

# include "../command.hh"

namespace OpenCIF
{
   /*
    * This class has the objective to work as a base for the control
    * commands (DefinitionStart, DefinitionDelete, DefinitionEnd and Call).
    */
   class ControlCommand : public OpenCIF::Command
   {
      public:
         explicit ControlCommand ( void ); // Default constructor
         virtual ~ControlCommand ( void ); // Destructor
         void setID ( const unsigned long int& new_id );
         unsigned long int getID ( void ) const;
         
      protected:
         unsigned long int command_id; // Unsigned long int since the value lenght is unexpected (but must be non-negative)
   };
}

# endif
