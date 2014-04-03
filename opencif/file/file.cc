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

# include "file.h"

/*
 * Default constructor. Nothing to do.
 */
OpenCIF::File::File ( void )
{
}

/*
 * Destructor. Delete the commands stored (if any).
 */
OpenCIF::File::~File ( void )
{
   for ( int i = 0; i < file_commands.size (); i++ )
   {
      delete file_commands[ i ];
      file_commands[ i ] = 0;
   }
}

/*
 * Member function to return the commands vector.
 */
std::vector< OpenCIF::Command* > OpenCIF::File::getCommands ( void ) const
{
   return ( file_commands );
}

/*
 * Member function to return the file path.
 */
std::string OpenCIF::File::getPath ( void ) const
{
   return ( file_path );
}

/*
 * Member function to set a vector of commands.
 */
void OpenCIF::File::setCommands ( const std::vector< OpenCIF::Command* >& new_commands )
{
   file_commands = new_commands;
   
   return;
}

/*
 * Member function to set the path to the file.
 */
void OpenCIF::File::setPath ( const std::string& new_path )
{
   file_path = new_path;
   
   return;
}

/*
 * Member function to return the messages generated during the load of the file.
 */
std::vector< std::string > OpenCIF::File::getMessages ( void )
{
   return ( file_messages );
}

/*
 * Member function to load the input file. There is returned a LoadStatus
 * value that indicates the result of the process.
 */
OpenCIF::File::LoadStatus OpenCIF::File::loadFile ( const LoadMethod& load_method )
{
   LoadStatus end_status;
   
   file_messages.clear ();
   
   end_status = openFile ();
   
   if ( end_status != AllOk )
   {
      return ( end_status );
   }
   
   end_status = validateSyntax ( load_method );
   cleanCommands ();
   
   if ( end_status != AllOk && load_method != ContinueOnError )
   {
      return ( end_status );
   }
   
   convertCommands ();
   
   return ( end_status );
}

/*
 * This member function try to open the input file.
 */
OpenCIF::File::LoadStatus OpenCIF::File::openFile ( void )
{
   if ( file_input.is_open () )
   {
      file_messages.push_back ( std::string ( "File:openFile:Warning: Input file already opened. Closing." ) );
      file_input.close ();
   }
   
   file_input.open ( file_path.c_str () );
   
   if ( !file_input.is_open () )
   {
      file_messages.push_back ( std::string ( "File:openFile:Error: Can't open input file." ) );
      
      return ( CantOpenInputFile );
   }
   
   return ( AllOk );
}

/*
 * This member function validates the contents of the input file using
 * a finite state machine.
 */
OpenCIF::File::LoadStatus OpenCIF::File::validateSyntax ( const LoadMethod& load_method )
{
   /*
    * The process of validation isn't that complex.
    * 
    * I need to create a CIFFSM class instance. Such instance will help me to validate
    * the file contents. The file is already opened. So, I'll read char by char and feed
    * them to the CIFFSM instance. The CIFFSM instance will start, by default, in state 1.
    * 
    * I'll feed the instance characters until the I reach end of file or the instance reports
    * an error (jump state equal to -1). After feeding the characters, if I finish feeding the
    * file and none error was reported, I will check the current state of the instance.
    * 
    * The instance should end in state 91 or 92. If the FSM is in such states, the file is 
    * correct and the format is supported.
    * 
    * If the FSM ends in any other state, the file is not neccessarally incorrect, but incomplete.
    * 
    * If there is a jump to a negative state, the file is invalid.
    */
   
   OpenCIF::CIFFSM* fsm;
   std::string command_buffer;
   int jump_state = 1; // By default, start in 1
   int previous_state; // Previous state.
   char input_char;
   char previous_char;
   bool errors_omited = false;
   
   fsm = new OpenCIF::CIFFSM ();
   
   file_raw_commands.clear ();
   
   // Iterate over the contents of the file, until the file end is
   // reached or the FSM reports a problem.
   
   while ( !file_input.eof () && jump_state != -1 )
   {
      previous_char = input_char;
      input_char = file_input.get ();
   
      if ( !file_input.eof () )
      {
         previous_state = jump_state;
         jump_state = fsm->operator[] ( input_char );
         
         if ( jump_state == 1 && previous_state != 1 ) // If I'm returning to the first state, the command
                                                       // is loaded. Just check the previous state. If the
                                                       // previous state is the state 1, then, do nothing,
                                                       // since those are characteres to skip.
         {
            std::string tmp;
            tmp = input_char;
            command_buffer += tmp;
            
            // I call the CleanCommand member function to remove unnecesary characters.
            file_raw_commands.push_back ( command_buffer );
            command_buffer = "";
         }
         else if ( jump_state != 1 && jump_state != -1 )
         {
            std::string tmp;
            tmp = input_char;
            command_buffer += tmp;
         }
         
         // Check if the current jump state is to an error. 
         // If so, and the load method indicates "ContinueOnError", reset the FSM
         // to state 1, reset the current jumps to 1, clean the command buffer and skip chars until a semicolon
         
         if ( jump_state == -1 && load_method == ContinueOnError )
         {
            fsm->reset ();
            jump_state = 1;
            errors_omited = true;
            command_buffer = "";
            
            file_input.putback ( input_char );
            file_raw_commands.push_back ( "(LibOpenCIF: Incorrect command here) ;" );
         }
      }
   }
   
   // File validated. What is the result?
   std::ostringstream oss;
   
   if ( jump_state == -1 )
   {
      std::string tmp;
      
      // There is an invalid input.
      file_messages.push_back ( std::string ( "File:validateSintax:Error: Error detected when validating contents of input file." ) );
      
      oss << previous_state;
      
      file_messages.push_back ( std::string ( "                           State: " ) + oss.str () );
      
      oss.str ( std::string ( "" ) );
      oss << (char)previous_char;
      
      tmp = tmp;
      
      file_messages.push_back ( std::string ( "                           Input char: \"" ) +
                                tmp +
                                std::string ( "\" (ASCII=" ) +
                                (
                                   ( oss.str ( std::string ( "" ) ) , oss << (int)previous_char ) ,
                                   oss.str ()
                                ) +
                                std::string ( ")" )
                              );
      
      file_messages.push_back ( std::string ( "                           Current command buffer: \"" ) + command_buffer + std::string ( "\"" ) );
      file_messages.push_back ( std::string ( "                           The loaded raw commands can be accessed to analize the error and locate the error." ) );
      
      return ( IncorrectInputFile );
   }
   
   if ( jump_state != 91 && jump_state != 92 )
   {
      file_messages.push_back ( std::string ( "File:validateSintax:Error: The file contents are incomplete (maybe a missing END command)." ) );
      
      return ( IncompleteInputFile );
   }
   
   // Everything Ok. Add last command (the END command)
   file_raw_commands.push_back ( cleanCommand ( command_buffer ) );
   
   return ( ( errors_omited) ? IncorrectInputFile : AllOk );
}

void OpenCIF::File::cleanCommands ( void )
{
   for ( unsigned long int i = 0; i < file_raw_commands.size (); i++ )
   {
      file_raw_commands[ i ] = cleanCommand ( file_raw_commands[ i ] );
   }
   
   return;
}

/*
 * This member function loads the contents of the input file and converts them
 * into Command instances.
 */
void OpenCIF::File::convertCommands ( void )
{
   /*
    * The raw commands are ready and validated. So, there is only left the process of
    * turning those strings into commands.
    */
   
   // First, delete and clear the current commands vector
   for ( int i = 0; i < file_commands.size (); i++ )
   {
      delete file_commands[ i ];
      file_commands[ i ] = 0;
   }
   
   file_commands.clear ();
   
   // Iterate over the raw commands. Check the first char of all. The first char will tell me exactly
   // wich command type is every one.
   
   for ( unsigned long int i = 0; i < file_raw_commands.size (); i++ )
   {
      std::string str_command;
      OpenCIF::Command* command;
      
      str_command = file_raw_commands[ i ];
      
      switch ( str_command[ 0 ] )
      {
         case 'B':
            command = new OpenCIF::BoxCommand ( str_command );
            file_commands.push_back ( command );
            break;
            
         case 'P':
            command = new OpenCIF::PolygonCommand ( str_command );
            file_commands.push_back ( command );
            break;
            
         case 'W':
            command = new OpenCIF::WireCommand ( str_command );
            file_commands.push_back ( command );
            break;
            
         case 'R':
            command = new OpenCIF::RoundFlashCommand ( str_command );
            file_commands.push_back ( command );
            break;
            
         case '(':
            command = new OpenCIF::CommentCommand ( str_command );
            file_commands.push_back ( command );
            break;
            
         case 'C':
            command = new OpenCIF::CallCommand ( str_command );
            file_commands.push_back ( command );
            break;
            
         case 'D':
            switch ( str_command[ 2 ] )
            {
               case 'D':
                  command = new OpenCIF::DefinitionDeleteCommand ( str_command );
                  file_commands.push_back ( command );
                  break;
                  
               case 'F':
                  command = new OpenCIF::DefinitionEndCommand ( str_command );
                  file_commands.push_back ( command );
                  break;
                  
               case 'S':
                  command = new OpenCIF::DefinitionStartCommand ( str_command );
                  file_commands.push_back ( command );
                  break;
            }
            break;
            
         case 'L':
            command = new OpenCIF::LayerCommand ( str_command );
            file_commands.push_back ( command );
            break;
            
         case 'E':
            command = new OpenCIF::EndCommand ();
            file_commands.push_back ( command );
            break;
            
         default:
            command = new OpenCIF::UserExtentionCommand ( str_command );
            file_commands.push_back ( command );
            break;
      }
   }
   
   return;
}

/*
 * This member function returns the vector of the raw (string) commands of the file.
 */
std::vector< std::string > OpenCIF::File::getRawCommands ( void ) const
{
   return ( file_raw_commands );
}

/*
 * This member function takes as argument a command in string form. The command is "not clear". That means
 * that is in the same way it was readed from the file.
 * 
 * The process of cleaning is to delete anything that is not intented to exist and leave only that things that can make
 * the command easy to parse.
 * 
 * For example, from this: "P-100,10000thisisvalid-10000cuac,cuac,cuac,imaduck-20000yolo;"
 * To this:                "P -100 10000 -10000 -20000 ;"
 * 
 * So, such kind of string can be used as an input stream to read easily.
 * 
 * There are some commands that I can't clean, like the comment or user expansion commands. Those commands are just returned.
 * 
 * At least, I can know what kind of command I'm working with by it's first char.
 */
std::string OpenCIF::File::cleanCommand ( std::string command )
{
   std::string final_command;
   
   switch ( command[ 0 ] )
   {
      // All of these commands can be processed as the same, since they only need values.
      case 'P':
      case 'B':
      case 'W':
      case 'R':
         final_command = clearNumericCommand ( command );
         break;
         
      case 'L': // Layer command
         final_command = cleanLayerCommand ( command );
         break;
         
      case 'C': // Call command
         final_command = cleanCallCommand ( command );
         break;
         
      case 'D': // Definition {Start|End|Delete} command.
         final_command = cleanDefinitionCommand ( command );
         break;
         
      case 'E': // End command.
         final_command = "E ;";
         break;
         
      default:
         final_command = command.substr ( 0 , command.size () - 1 ) + " ;";
         break;
   }
   
   return ( final_command );
}

/*
 * This member function takes as argument a Definition command and returns it cleaned.
 * 
 * A definition command can be something like this:
 * 
 *      "DxxxxxSlol100im,totally,legal;"
 * 
 * So, the task of this member function is to turn it into like this:
 * 
 *      "D S 100 ;"
 * 
 * The process begins with the deletion of any non-digit and non-uppercase characters.
 * Such operation, is good, can leave a command like this:
 * 
 *      "DS100;"
 * 
 * To simplify the process of converting commands into instances, the commands must have
 * whitespaces to separate components (to use the strings as, for example, input streams).
 * 
 * So, the next process is to separate the components to turn the command into this:
 * 
 *      "D S 100 ;"
 */
std::string OpenCIF::File::cleanDefinitionCommand ( std::string command )
{
   std::string final_command;
   std::string tmp = " ";
            
   // There are only uppercase chars and digits
   final_command = command[ 0 ];
   final_command += tmp;
   
   // Remove not-necessary characters
   command[ 0 ] = ' ';
   for ( int i = 0; i < command.size (); i++ )
   {
      // If the current char is not a 'D', not a digit, not an 'S' and not an 'F'
      if ( !std::isdigit ( command[ i ] ) && !std::isupper ( command[ i ] ) )
      {
         command[ i ] = ' ';
      }
   }
   
   for ( int i = 1; i < command.size (); i++ )
   {
      if ( std::isdigit ( command[ i ] ) )
      {
         final_command += command[ i ];
      }
      else if ( command[ i ] != ' ' )
      {
         final_command += command[ i ];
         final_command += " ";
      }
      else if ( command[ i ] == ' ' && final_command[ final_command.size () - 1 ] != ' ' )
      {
         final_command += " ";
      }
   }
   
   ( final_command[ final_command.size () - 1 ] == ' ' )
   ? final_command += ";"
   : final_command += " ;";
   
   return ( final_command );
}

/*
 * This member function takes as argument a call command and returns it cleaned.
 * 
 * A call command can be something like this:
 * 
 *      "C1T20000 -20000R1000000 -59999MXlololololololololMY MXMXMXMYMXR100 100R100 100;"
 * 
 * So, the task of this member function is to turn it into like this:
 * 
 *      "C 1 T 20000 -20000 R 1000000 -59999 M X M Y M X M X M X M Y M X R 100 100 R 100 100;"
 * 
 * The process begins with the deletion of any non-digit, non-dash ('-') and non-uppercase characters.
 * Such operation, is good, can leave a command like this:
 * 
 *      "C 1 T 20000 -20000 R 1000000 -59999 MX MY MXMXMXMYMXR100 100R100 100;"
 * 
 * To simplify the process of converting commands into instances, the commands must have
 * whitespaces to separate components (to use the strings as, for example, input streams).
 * 
 * So, the next process is to separate the components to turn the command into this:
 * 
 *      "C 1 T 20000 -20000 R 1000000 -59999 M X M Y M X M X M X M Y M X R 100 100 R 100 100;"
 */
std::string OpenCIF::File::cleanCallCommand ( std::string command )
{
   std::string final_command;
   std::string tmp = " ";
            
   // There are only uppercase chars
   final_command = command[ 0 ];
   final_command += tmp;
   
   // Remove not-necessary characters
   command[ 0 ] = ' ';
   for ( int i = 0; i < command.size (); i++ )
   {
      if ( !std::isdigit ( command[ i ] ) && !std::isupper( command[ i ] ) && command[ i ] != '-' )
      {
         command[ i ] = ' ';
      }
   }
   
   for ( int i = 1; i < command.size (); i++ )
   {
      tmp = command[ i ];
      
      if ( std::isdigit ( command[ i ] ) )
      {
         final_command += tmp;
      }
      else if ( command[ i ] != ' ' )
      {
         if ( final_command[ final_command.size () - 1 ] != ' ' )
         {
            final_command += " ";
         }
         
         final_command += tmp;
         
         if ( std::isupper ( command[ i ] ) )
         {
            final_command += " ";
         }
      }
      else if ( final_command[ final_command.size () - 1 ] != ' ' )
      {
         final_command += " ";
      }
   }
   
   ( final_command[ final_command.size () - 1 ] == ' ' ) ? final_command += ";" : final_command += " ;";
   
   return ( final_command );
}

/*
 * This member function takes as argument a Layer camand and removes any unnecesary character.
 */
std::string OpenCIF::File::cleanLayerCommand ( std::string command )
{
   std::string tmp = " ";
   std::string final_command;
            
   final_command = command[ 0 ];
   final_command += tmp;
   
   // Remove not-necessary characters
   command[ 0 ] = ' ';
   for ( int i = 0; i < command.size (); i++ )
   {
      if ( !std::isupper ( command[ i ] ) && command[ i ] != '_' && ! std::isdigit ( command[ i ] ) )
      {
         command[ i ] = ' ';
      }
   }
   
   std::istringstream iss ( command );
   
   while ( !iss.eof () )
   {
      iss >> tmp;
      
      if ( !iss.eof () )
      {
         final_command += tmp;
         tmp = " ";
         final_command += tmp;
      }
   }
   
   final_command += ";";
            
   return ( final_command );
}

/*
 * This member function takes as argument a numeric command (like a Polygon or Box command)
 * and cleans it.
 * 
 * A numeric command can be something like this:
 * 
 *      "W1000,muajajajajaja20000,,,this,is,valid20000twerking,so,hard,,,,,,xoxoxoxoxox-10000,-10000,-500 juar juar juarX-4000;"
 * 
 * So, the task of this member function is to turn it into like this:
 * 
 *      "W 1000 20000 20000 -10000 -10000 -500 -4000 ;"
 * 
 * The process begins with the deletion of any non-digit and non-dash ('-') characters.
 * Such operation, is good, can leave a command like this:
 * 
 *      "W1000              20000                20000                                 -10000 -10000 -500                -4000;"
 * 
 * To simplify the process of converting commands into instances, the commands must have
 * whitespaces to separate components (to use the strings as, for example, input streams).
 * 
 * So, the next process is to separate the components to turn the command into this:
 * 
 *      "W 1000 20000 20000 -10000 -10000 -500 -4000 ;"
 */
std::string OpenCIF::File::clearNumericCommand ( std::string command )
{
   std::string tmp = " ";
   std::string final_command;
            
   // There are only numbers and guides ("-")
   final_command = command[ 0 ];
   final_command += tmp;
   
   // Remove not-necessary characters
   for ( int i = 0; i < command.size (); i++ )
   {
      if ( !std::isdigit ( command[ i ] ) && command[ i ] != '-' )
      {
         command[ i ] = ' ';
      }
   }
   
   std::istringstream iss ( command );
   
   while ( !iss.eof () )
   {
      iss >> tmp;
      
      if ( !iss.eof () )
      {
         final_command += tmp;
         tmp = " ";
         final_command += tmp;
      }
   }
   
   final_command += ";";
   
   return ( final_command );
}
