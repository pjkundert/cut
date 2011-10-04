
// 
// cutone.C		-- CUT unit tests
// 
// Copyright (C) 2004 Enbridge Inc.
// 
// This file is part of the Enbridge CUT Library
// 
// CUT is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2, or (at your option) any later
// version.
// 
// CUT is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
// 
// You should have received a copy of the GNU General Public License
// along with CUT; see the file COPYING.  If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
// 

#include <cut>
#include <math.h>
namespace cut {
    //
    // Create a test suite, which chains itself automatically
    // beneath cut::root.  Don't clutter up your own namespace!
    // 
    test			root( "Simple C++ Unit Test" );

    //
    // Create class derived from cut::test, and defines its run() method. The
    // instance chains itself automatically beneath the given cut::test.
    // 
    CUT( cut::root, SqrtTest, "Simple sqrt() Test" ) {
	assert.out() << "tests sqrt(2) == 1.4 +/- 0.1" << std::endl;
	assert.ISEQUALDELTA( sqrt( 2.0 ), 1.4, 0.01 );
    }
}

int
main(
    int				argc,
    char 	       	      **argv )
{
    // 
    // Create cut::runner instances, and run all tests, with HTML output.
    // Return 0 on success, ! 0 on failure. 
    // 
    cut::htmlrunner 		html( std::cout );	// use cut::runner for textual output
    return ! html.run();
}
 
