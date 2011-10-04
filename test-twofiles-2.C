
// 
// test-twofiles-2.C	-- CUT unit tests
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

#include <math.h>
#include <cut>

int				file2()
{
    return 2;
}

namespace cut {
    CUT( cut::root, SecondSuite, "The Second Suite" ) {
	assert.out() << "Failure: " << name() << std::endl;
	assert.ISTRUE( false );
    }

    CUT( SecondSuite, Test_file2, "file2" ) {
	assert.ISEQUAL( file2(), 2 );
    }

    CUT( cut::root, ThirdSuite, "The Third Suite" ) {
	std::cout << "Unknown: " << name() << std::endl;
	assert.ISUNKNOWN( sqrt( 2 ) );
    }
}
