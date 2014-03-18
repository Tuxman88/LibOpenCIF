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

# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <sstream>

# include "../command/command.h"
# include "../finitestatemachine/ciffsm.h"
# include "../command/controlcommand/callcommand/callcommand.h"
# include "../command/controlcommand/definitiondeletecommand/definitiondeletecommand.h"
# include "../command/controlcommand/definitionendcommand/definitionendcommand.h"
# include "../command/controlcommand/definitionstartcommand/definitionstartcommand.h"
# include "../command/layercommand/layercommand.h"
# include "../command/primitivecommand/pathbasedcommand/polygoncommand/polygoncommand.h"
# include "../command/primitivecommand/pathbasedcommand/wirecommand/wirecommand.h"
# include "../command/primitivecommand/positionbasedcommand/roundflashcommand.h"
# include "../command/primitivecommand/positionbasedcommand/boxcommand/boxcommand.h"
# include "../command/rawcontentcommand/commentcommand/commentcommand.h"
# include "../command/rawcontentcommand/userextentioncommand/userextentioncommand.h"
# include "../command/controlcommand/endcommand/endcommand.h"

namespace OpenCIF
{
   class File
   {
      public:
         enum LoadStatus
         {
            AllOk = 0 ,
            CantOpenInputFile ,
            IncompleteInputFile ,
            IncorrectInputFile
         };
      
      public:
         explicit File ( void );
         virtual ~File ( void );
         void setPath ( const std::string& new_path );
         std::string getPath ( void ) const;
         
         void setCommands ( const std::vector< OpenCIF::Command* >& new_commands );
         std::vector< OpenCIF::Command* > getCommands ( void ) const;
         
         LoadStatus loadFile ( void ); // Whole process of loading a CIF file, from opening the file
                                       // to converting the commands into instances.
         LoadStatus openFile ( void );
         LoadStatus validateSintax ( void );
         LoadStatus loadCommands ( void );
         
         std::vector< std::string > getMessages ( void );
         
         std::vector < std::string > getRawCommands ( void ) const;
         
      private:
         std::string cleanCommand ( std::string command );
         std::string clearNumericCommand ( std::string command );
         std::string cleanLayerCommand ( std::string command );
         std::string cleanCallCommand ( std::string command );
         std::string cleanDefinitionCommand ( std::string command );
         
      private:
         std::string file_path;
         std::ifstream file_input;
         std::vector< OpenCIF::Command* > file_commands;
         std::vector< std::string > file_raw_commands;
         std::vector< std::string > file_messages;
   };
}

# endif
