//! \file  bxtour002.cxx
//! \brief A BxTour program
//
// Copyright (c) 2018 by François Mauger <mauger@lpccaen.in2p3.fr>
// Copyright (c) 2018 by Université de Caen Normandie
//
// This file is part of BxTour.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// Standard libraries
#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include <vector>
#include <algorithm>

// Third Party
// - Bayeux:
#include <bayeux/bayeux.h>
#include <bayeux/datatools/real_range.h>
#include <bayeux/datatools/clhep_units.h>

void run1();
void run2();

int main(int argc_, char * argv_[])
{
  bayeux::initialize(argc_, argv_);
  int error_code = EXIT_SUCCESS;
  try {
    run1();
    run2();
  } catch (std::exception & error) {
    DT_LOG_ERROR(datatools::logger::PRIO_ERROR, error.what());
    error_code = EXIT_FAILURE;
  } catch (...) {
    DT_LOG_ERROR(datatools::logger::PRIO_ERROR, "Unexpected error !");
    error_code = EXIT_FAILURE;
  }
  bayeux::terminate();
  return error_code;
}

void run1()
{
  std::clog << "Class: 'datatools::real_range'" << std::endl;
  double tolerance = 0.02;
  double lower = 3.0;
  double upper = 4.0;
  datatools::real_range rrange(lower,
                               upper,
                               datatools::range_bound_included,
                               datatools::range_bound_excluded);
  std::cout.precision(7);
  double xmin = 2.75;
  double xmax = 4.25;
  double xstep = 0.012;
  for (double value = xmin; value < xmax; value += xstep) {
    if (rrange.has(value, tolerance)) {
      std::cout << "value=" << value << " belongs to " << rrange << std::endl;
    } else {
      std::cout << "value=" << value << " does not belong to " << rrange << std::endl;
    }
  }
  std::clog << std::endl;
  return;
}

void run2()
{
  std::clog << "Class: 'datatools::real_range'" << std::endl;
  double tolerance = 0.02 * CLHEP::m;
  double lower = 3.0 * CLHEP::m;
  double upper = 4.0 * CLHEP::m;
  datatools::real_range rrange(lower,
                               upper,
                               datatools::range_bound_included,
                               datatools::range_bound_excluded);
  rrange.set_preferred_unit("mm");
  std::cout.precision(7);
  double xmin = 2.75 * CLHEP::m;
  double xmax = 4.25 * CLHEP::m;
  double xstep = 12 * CLHEP::mm;
  for (double value = xmin; value < xmax; value += xstep) {
    if (rrange.has(value, tolerance)) {
      std::cout << "value=" << value / CLHEP::mm << " mm belongs to " << rrange << std::endl;
    } else {
      std::cout << "value=" << value / CLHEP::mm << " mm does not belong to " << rrange << std::endl;
    }
  }
  std::clog << std::endl;
  return;
}
