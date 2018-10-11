//! \file  bxtour000.cxx
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
#include <bayeux/bayeux_config.h>
#include <bayeux/version.h>

struct params_type {
  bool interactive = false;
};

int hello_bayeux(std::ostream & out_);

int main(int argc_, char * argv_[])
{
  bayeux::initialize(argc_, argv_);
  int error_code = EXIT_SUCCESS;
  params_type params;
  
  try {
    std::clog << "Welcome to Bayeux Discovery Tour !" << std::endl;

    std::vector<std::string> args;
    for (int i =1; i < argc_; i++) {
      args.push_back(std::string(argv_[i]));
    }
    if (std::find(args.begin(), args.end(), "--interactive") != args.end()) {
      params.interactive = true;
    }

    hello_bayeux(std::cout);
      
    std::clog << "The end." << std::endl;
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

int hello_bayeux(std::ostream & out_)
{
  out_ << "Hello, Bayeux " << bayeux::version::get_version() << '!' << std::endl;
  out_ << std::endl;
  out_ << "Bayeux is built with : " << std::endl;
  out_ << " - cuts       : " << BAYEUX_WITH_CUTS << std::endl;
  out_ << " - materials  : " << BAYEUX_WITH_MATERIALS << std::endl;
  out_ << " - mygsl      : " << BAYEUX_WITH_MYGSL << std::endl;
  out_ << " - brio       : " << BAYEUX_WITH_BRIO << std::endl;
  out_ << " - dpp        : " << BAYEUX_WITH_DPP << std::endl;
  out_ << " - geomtools  : " << BAYEUX_WITH_GEOMTOOLS << std::endl;
  out_ << " - emfield    : " << BAYEUX_WITH_EMFIELD << std::endl;
  out_ << " - genbb      : " << BAYEUX_WITH_GENBB << std::endl;
  out_ << " - genvtx     : " << BAYEUX_WITH_GENVTX << std::endl;
  out_ << " - mctools    : " << BAYEUX_WITH_MCTOOLS << std::endl;
  out_ << " - Geant4     : " << BAYEUX_WITH_GEANT4_MODULE << std::endl;
  out_ << " - LaHague    : " << BAYEUX_WITH_LAHAGUE << std::endl;
  out_ << "Bayeux uses : " << std::endl;
  out_ << " -  Qt        : " << BAYEUX_WITH_QT << std::endl;
  out_ << std::endl;
  return 0;
}
