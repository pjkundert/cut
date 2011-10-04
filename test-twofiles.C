
// 
// test-twofiles.C    -- CUT unit tests
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
#include <iostream>

#include <stdlib.h>

int				file1();
int				file2();

namespace cut {
    test                        root( "Two File Test" );
}

int
main( int, char ** ) {
    bool success;
    if ( getenv( "REQUEST_METHOD" )) {
        // 
        // Lets run our tests with CGI HTML output:
        // 
        //                            target  sparse  flat   cgi
        //                            ------  ------  ----   ---
        success = cut::htmlrunner( std::cout, false,  true,  true ).run();
    } else {
        // 
        // But, here's the (simpler) textual output:
        // 
        success = cut::runner( std::cout ).run();
    }

    file1();

#if ! defined( EXCLUDEFILE2 )
    // Optionally include some functionality from some compilation module
    file2();
#endif

    return ! success;
}
