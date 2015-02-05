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

# ifndef LIBOPENCIF_H_
# define LIBOPENCIF_H_

# include "command/command.hh"
# include "command/transformation/transformation.hh"
# include "command/point/point.hh"
# include "command/size/size.hh"
# include "command/fraction/fraction.hh"
# include "command/controlcommand/controlcommand.hh"
# include "command/controlcommand/callcommand/callcommand.hh"
# include "command/controlcommand/definitiondeletecommand/definitiondeletecommand.hh"
# include "command/controlcommand/definitionendcommand/definitionendcommand.hh"
# include "command/controlcommand/definitionstartcommand/definitionstartcommand.hh"
# include "command/controlcommand/endcommand/endcommand.hh"
# include "command/rawcontentcommand/rawcontentcommand.hh"
# include "command/rawcontentcommand/commentcommand/commentcommand.hh"
# include "command/rawcontentcommand/userextensioncommand/userextensioncommand.hh"
# include "command/primitivecommand/primitivecommand.hh"
# include "command/primitivecommand/pathbasedcommand/pathbasedcommand.hh"
# include "command/primitivecommand/pathbasedcommand/polygoncommand/polygoncommand.hh"
# include "command/primitivecommand/pathbasedcommand/wirecommand/wirecommand.hh"
# include "command/primitivecommand/positionbasedcommand/positionbasedcommand.hh"
# include "command/primitivecommand/positionbasedcommand/boxcommand/boxcommand.hh"
# include "command/primitivecommand/positionbasedcommand/roundflashcommand/roundflashcommand.hh"
# include "command/layercommand/layercommand.hh"
# include "file/file.hh"
# include "finitestatemachine/finitestatemachine.hh"
# include "finitestatemachine/state.hh"
# include "finitestatemachine/ciffsm.hh"

# include <string>

namespace OpenCIF
{
   const std::string LibraryVersion = "1.2.0";
   const std::string LibraryVersionMajor = "1";
   const std::string LibraryVersionMinor = "2";
   const std::string LibraryVersionPatch = "0";
   const std::string LibraryName = "LibOpenCIF";
   const std::string LibraryAuthor = "Moises Chavez-Martinez";
   const std::string LibrarySupport = "moises.chavez.martinez@gmail.com";
   const std::string LibraryCIFVersion = "2.0";
}


# endif
