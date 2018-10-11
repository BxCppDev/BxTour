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

Installing BxTour
=================

.. code:: bash
	  
   $ cd {BxTour source directory}
   $ mkdir BxTour-build
   $ cd BxTour-build/
   $ cmake -GNinja \
           -DCMAKE_INSTALL_PREFIX=<where you want to install> \
	   -DCMAKE_PREFIX_PATH=<path to your Linuxbrew install> \
	   ..
   $ ninja -j
   $ ninja install
..


List of programs
================

* ``bxtour000.cxx`` : print Bayeux version and configuration.
* ``bxtour001.cxx`` : use the class ``datatools::integer\_range``.
* ``bxtour002.cxx`` : use the class ``datatools::real\_range``.
* ``bxtour003.cxx`` : use tools from the namespace ``datatools::units``.


.. end

