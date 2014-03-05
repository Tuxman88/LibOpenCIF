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

# ifndef LIBOPENCIF_FILE_H_
# define LIBOPENCIF_FILE_H_

# include <string>
# include <vector>

# include "../command/command.h"

namespace OpenCIF
{
   class File
   {
      public:
         explicit File ( void );
         virtual ~File ( void );
         void setPath ( const std::string& new_path );
         void setCommands ( const std::vector< OpenCIF::Command* >& new_commands );
         std::string getPath ( void ) const;
         std::vector< OpenCIF::Command* > getCommands ( void ) const;
         
      private:
         std::string file_path;
         std::vector< OpenCIF::Command* > file_commands;
   };
}

# endif
