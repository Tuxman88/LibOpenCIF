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

# ifndef LIBOPENCIF_COMMAND_H_
# define LIBOPENCIF_COMMAND_H_

// General namespace for all the library contents.
namespace OpenCIF
{     
   /*
    * Main class. Base for a lot of classes. Gives the powers needed
    * to store all the commands from the CIF file into a single list
    * using pointers to the base class (this class).
    * 
    * To detect the type of the classes once the list is filled, the
    * class contains a member function to return the type of every
    * instance (every class changes the value of such value, so, once
    * created, every instance has a different type).
    */
   
   class Command
   {
      public:
         explicit Command ( void ); // Main constructor.
         virtual ~Command ( void ); // Destructor
         virtual CommandType type (); // Returns the type of the instance. In this case, should return "PlainCommand"
         
      protected:
         CommandType command_type;
      
      public:
         // Enumeration for this class and child classes.
         enum CommandType
         {
            PlainCommand = 0 ,
            Primitive ,
            Control ,
            RawContent ,
            PathBased ,
            PositionBased ,
            DefinitionStart ,
            DefinitionDelete ,
            Call ,
            DefinitionEnd ,
            Comment ,
            UserExtention , 
            Polygon ,
            Wire ,
            Box ,
            RoundFlash
         };
   };
}

# endif
