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

# ifndef LIBOPENCIF_TRANSFORMATION_H_
# define LIBOPENCIF_TRANSFORMATION_H_

# include "../point/point.h"

namespace OpenCIF
{
   class Transformation
   {
      public:
         explicit Transformation ( void );
         virtual ~Transformation ( void );
         
         void setType ( const TransformationType& new_type );
         TransformationType getType ( void ) const;
         
         void setRotation ( const OpenCIF::Point& new_rotation );
         OpenCIF::Point getRotation ( void ) const;
         
         void setDisplacement ( const OpenCIF::Point& new_displacement );
         OpenCIF::Point getDisplacement ( void ) const;
         
      private:
         TransformationType transformation_type;
         OpenCIF::Point transformation_point;
         
      public:
         enum TransformationType
         {
            Displacement = 0 ,
            Rotation ,
            HorizontalMirroring ,
            VerticalMirroring
         };
   };
}

# endif
