//! \file  bxtour001.cxx
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
#include <bayeux/datatools/integer_range.h>

void run1();

int main(int argc_, char * argv_[])
{
  bayeux::initialize(argc_, argv_);
  int error_code = EXIT_SUCCESS;
  try {
    run1();
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
  std::clog << "Class: 'datatools::integer_range'" << std::endl;
  int32_t lower = 3;
  int32_t upper = 10;
  datatools::integer_range irange(lower,
                                  upper,
                                  datatools::range_bound_included,
                                  datatools::range_bound_excluded);
  for (int32_t value = 0; value < 15; value++) {
    if (irange.has(value)) {
      std::cout << "value=" << value << " belongs to " << irange << std::endl;
    } else {
      std::cout << "value=" << value << " does not belong to " << irange << std::endl;
    }
  }
  std::clog << std::endl;
  return;
}
