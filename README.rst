================================================================
Bayeux C++ Library Discovery Tour 
================================================================

:Authors: The BxCppDev_ group
:Date:    2018-09-11
:Contact: bayeux@lpccaen.in2p3.fr

.. contents::
   :depth: 3
..

.. _BxCppDev: https://github.com/BxCppDev

.. raw:: pdf

   PageBreak oneColumn

Introduction
============

The  purpose of  the BxTour  project is  to help  you to  discover the
Bayeux's C++ Library functionalities.  BxTour provides a collection of
programs that illustrates possible usages of Bayeux's components.

Requirements
============

You should have built and installed the Bayeux library before building
BxTour. Particularly, Linuxbrew's ``brew`` and  Bayeux's ``bxquery``
programs should be available on your system:

.. code:: bash

   $ which brew
   $ brew --prefix
   $ which bxbayeux
   $ bxbayeux --prefix
..

Installing BxTour
=================

.. code:: bash
	  
   $ cd {BxTour source directory}
   $ mkdir BxTour-build
   $ cd BxTour-build/
   $ cmake -GNinja \
           -DCMAKE_INSTALL_PREFIX=<where you want to install> \
	   -DCMAKE_PREFIX_PATH=$(brew --prefix) \
	   -DBayeux_DIR=$(bxquery --cmakedir} \
	  ..
   $ ninja -j
   $ ninja install
..


List of example programs
========================

* ``bxtour000.cxx`` : print Bayeux version and configuration.
* ``bxtour001.cxx`` : use the class ``datatools::integer_range``.
* ``bxtour002.cxx`` : use the class ``datatools::real_range``.
* ``bxtour003.cxx`` : use tools from the namespace ``datatools::units``.


.. end

