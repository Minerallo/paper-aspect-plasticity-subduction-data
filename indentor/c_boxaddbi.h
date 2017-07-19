/*
  Copyright (C) 2011-2017 by the authors of the ASPECT code.

  This file is part of ASPECT.

  ASPECT is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2, or (at your option)
  any later version.

  ASPECT is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with ASPECT; see the file doc/COPYING.  If not see
  <http://www.gnu.org/licenses/>.
*/


#ifndef __aspect__boundary_composition_boxaddbi_h
#define __aspect__boundary_composition_boxaddbi_h

#include <aspect/boundary_composition/interface.h>
#include <aspect/simulator_access.h>


namespace aspect
{
  namespace BoundaryComposition
  {
    /**
     * A class that implements a composition boundary condition for a box
     * geometry with an additional boundary indicator. Only use in combination
     * with Geometry Model BoxAddBI.
     *
     * @ingroup BoundaryCompositions
     */
    template <int dim>
    class BoxAddBI : public Interface<dim>,
      public SimulatorAccess<dim>
    {
      public:
        /**
         * Return the composition that is to hold at a particular location on the
         * boundary of the domain. This function returns constant compositions
         * at the left and right boundaries.
         *
         * @param boundary_indicator The boundary indicator of the part of the boundary
         *   of the domain on which the point is located at which we are requesting the
         *   composition.
         * @param location The location of the point at which we ask for the composition.
         * @param compositional_field The number of the compositional field for which
         * the boundary composition is queried.
         **/
        virtual
        double boundary_composition (const types::boundary_id             boundary_indicator,
                                     const Point<dim>                    &location,
                                     const unsigned int                   compositional_field) const;

        /**
         * Declare the parameters this class takes through input files.
         * This class declares the inner and outer boundary compositions.
         */
        static
        void
        declare_parameters (ParameterHandler &prm);

        /**
         * Read the parameters this class declares from the parameter
         * file.
         */
        virtual
        void
        parse_parameters (ParameterHandler &prm);

        /**
         * Initialize this class for a given simulator. This function
         * overloads that of the SimulatorAccess base class. It calls
         * the respective function of the base class and then performs
         * some basic sanity checks on the parameter values previously
         * read from the input file.
         *
         * @param simulator A reference to the main simulator object.
         **/
        virtual void initialize (const Simulator<dim> &simulator);

      private:
        /**
         * The values of the various composition variables on each of the 2*dim+1
         * boundaries of the box.
         */
        std::vector<double> composition_values[2*dim+1];
    };
  }
}


#endif
