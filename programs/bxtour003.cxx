//! \file  bxtour003.cxx
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
#include <bayeux/datatools/units.h>
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
  std::clog << "Namespace: 'datatools::units'" << std::endl;

  std::cout.precision(10);
  
  std::vector<std::string> dimension_labels;
  datatools::units::registered_unit_dimension_labels(dimension_labels);
  std::cout << "List of unit dimensions : " << std::endl;
  for (const auto dim_label : dimension_labels) {
    std::cout << " - Dimension : '" << dim_label << "'" << std::endl;
  }
  std::cout << std::endl;
  
  std::vector<std::string> unit_names;
  datatools::units::registered_unit_names(unit_names);
  std::cout << "List of units : " << std::endl;
  for (const auto unit_name : unit_names) {
    std::cout << " - Unit : '" << unit_name << "'";
    double unit_value = 1.0;
    std::string unit_dim;
    if (datatools::units::find_unit(unit_name, unit_value, unit_dim)) {
      std::cout << " (value=" << unit_value << ", dimension='" << unit_dim << "')"; 
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
 
  std::vector<std::string> unit_symbols;
  datatools::units::registered_unit_symbols(unit_symbols);
  std::cout << "List of unit symbols : " << std::endl;
  for (const auto unit_symbol : unit_symbols) {
    std::cout << " - Unit symbol : '" << unit_symbol << "'" << std::endl;
  }
  std::cout << std::endl;

  double cm = datatools::units::get_unit("cm");
  std::cout << "Centimeter unit     : " << cm << std::endl;

  std::string def_length_unit
    = datatools::units::get_default_unit_symbol_from_label("length");
  std::cout << "Default length unit : '" << def_length_unit << "'" << std::endl;

  std::string token = "2.54 cm";
  double width = datatools::units::get_value_with_unit(token);
  std::cout << "Token : '" << token << "'" << std::endl;
  std::cout << " -> Width : " << width / CLHEP::mm << " mm" << std::endl;

  token = "12.34 us";
  double time;
  std::string unit_symbol;
  std::string unit_label;
  bool ok = datatools::units::parse_value_with_unit(token,
                                                    time,
                                                    unit_symbol,
                                                    unit_label);
  if (ok) {
    std::cout << "Token     : '" << token << "'" << std::endl;
    std::cout << " -> Time      : " << time / CLHEP::second << " s" << std::endl;
    std::cout << " -> Unit      : '" << unit_symbol << "'" << std::endl;
    std::cout << " -> Dimension : '" << unit_label << "'" << std::endl;
  }
  
  std::clog << std::endl;
  return;
}

void run2()
{
  std::clog << "Namespace: 'datatools::units'" << std::endl;

  double l = datatools::units::get_value_with_unit("5.25 m");
  double t = datatools::units::get_value_with_unit("0.75 s");
  double v = l / t;
  double velocity_unit = datatools::units::get_value_with_unit("1 mm/us");
  std::cout << "v = " << v / velocity_unit  << " mm/us" << std::endl;
  
  std::clog << std::endl;
  return;
}
