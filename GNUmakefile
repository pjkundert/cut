# 
# CUT		-- C++ Unit Test Framework
# 

VERSION		= 4.1.2
ARCH		= $(shell uname -m | sed -e s/i.86/i386/ -e s/9000.*/hppa/)
#DEBUG		= yes 		# anything turns on -g
#OPT		= 3		# defaults to 3
TARGET		= /usr/local/include

# We want to deduce these, unless they are explicitly set...
ifeq ($(origin CC),default)
    CC		=
endif
ifeq ($(origin CXX),default)
    CXX		=
endif

CXXFLAGS	+= -I.
LDFLAGS		+= -L.

# Default flags for building test executables.  Not required by
# default (only cut.H is required by client programs)!  Figure out
# deguggable vs. optimized, limit optimization level to practical limit
ifeq ($(ARCH),i386)
    ifneq ($(DEBUG),)
	CXXFLAGS	+= -g
    endif

    ifneq ($(OPT),)
	CXXFLAGS	+= -O$(OPT)
    else
	CXXFLAGS	+= -O3
    endif

    ifeq ($(CXX),icc)
        CXXFLAGS += -Wall
    else
        ifeq ($(CXX),)
            CXX	 = g++
        endif
        CXXFLAGS += -pipe		 		\
		   -Wall
    endif
endif
ifeq ($(ARCH),sun4v)
    ifeq ($(CXX),)
        CXX	 = CC
    endif
    CXXFLAGS 		+= +w
    ifneq ($(DEBUG),)
	CXXFLAGS	+= -g
    endif

    ifneq ($(OPT),)
	CXXFLAGS	+= -xO$(OPT)
    else
	CXXFLAGS	+= -xO4
    endif
endif
ifeq ($(ARCH),x86_64)
    ifneq ($(DEBUG),)
	CXXFLAGS	+= -g
    endif

    ifneq ($(OPT),)
	CXXFLAGS	+= -O$(OPT)
    else
	CXXFLAGS	+= -O3
    endif

    ifeq ($(CXX),icc)
        CXXFLAGS += -Wall
    else
        ifeq ($(CXX),)
            CXX	 = g++
        endif
        CXXFLAGS += -pipe		 		\
		   -Wall
    endif
endif
ifeq ($(ARCH),hppa)
    ifneq ($(DEBUG),)
	CXXFLAGS	+= -g
    else
	ifneq ($(OPT),)
	    # Opimisation level specified (incompatible with -g)...
	    ifneq ($(LWOPT),0)
	        # Specific (non-zero) optimisation level set; use it
		CXXFLAGS+= +O$(OPT)
            endif
	else
            CXXFLAGS	+= +O2
	endif
    endif

    ifeq ($(CXX),)
        CXX	= aCC
    endif
    CXXFLAGS   += -AA +p				\
		  +DAportable				 \
		  -D_HPUX_SOURCE			  \
		  -D_POSIX_C_SOURCE=199506L		   \
		  -D_RWSTD_MULTI_THREAD
    # 
    # on HP-UX aCC, the -mt flag sets the right -D... and -l... flags for thread-safety.
    # Even if -mt is used to compile all objects, if -mt isn't used to link the target,
    # most all 'pthread_...' functions will compile to stubs, which is most efficient
    # in single-threaded executables.
    # 
    CXXFLAGS	       += -mt
endif

# 
# Basic Targets
# 
#     The default target 'all' builds (optional) unit test object, and
# source distribution package.  Neither of these are necessary to use
# REF.  The cut-test.o object may optionally be linked into
# applications, if running CUT unit tests are desired
# 
.PHONY: all configure test install dist distclean clean

all:			cut-test.o

configure:

test:			configure cut-test.html cutone.html test-twofiles.html test-twofiles.text

install:
	cp cut cut.H $(TARGET)

dist:			distclean cut-$(VERSION).tgz

distclean:		clean

clean:			
	-rm -f	*.tgz					\
		*.html					 \
		*.text					 \
		*~ 					  \
		*.o 					   \
		core*					    \
		cut-test cutone test-twofiles


# 
# Unit Tests
# 
headers		=	cut				\
			cut.H

cut-test.o:		$(headers) cut-test.C
	$(CXX) $(CXXFLAGS) -c -DTEST cut-test.C -o $@

cut-test: 		$(headers) cut-test.C
	$(CXX) $(CXXFLAGS) -DTESTSTANDALONE -DTEST cut-test.C -o $@

cut-test.html: 		cut-test
	./cut-test > cut-test.html

cutone:			$(headers) cutone.C
	$(CXX) $(CXXFLAGS) -DTESTSTANDALONE -DTEST cutone.C -o $@

cutone.html: 		cutone
	./cutone > cutone.html || true			# This unit test fails (expectedly); ignore it


# 
# Test the optional inclusion of test functionality, depending on whether
# the compilation unit is linked into the final executable.
# 
test-twofiles-1.C:	$(headers)
test-twofiles-2.C:	$(headers)

libsomefiles.a:		test-twofiles-1.o	\
			test-twofiles-2.o
	rm -f $@
	ar rsv $@ $^

test-twofiles:		test-twofiles.C libsomefiles.a
	$(CXX) $(CXXFLAGS) $(LDFLAGS) test-twofiles.C -lsomefiles -o $@ 

test-twofiles.html:		test-twofiles
	REQUEST_METHOD=GET 				\
	./test-twofiles > test-twofiles.html || true	# This unit test fails (expectedly); ignore it

test-twofiles.text:		test-twofiles
	./test-twofiles > test-twofiles.text || true	# This unit test fails (expectedly); ignore it

# 
# Distribution
# 
cut-$(VERSION).tgz: 	configure		\
			GNUmakefile		 \
			cut			  \
			cut.H			   \
			COPYING			    \
			README			     \
	 		INSTALL			      \
			cut-test.C		       \
			cutone.C			\
			test-twofiles-1.C		 \
			test-twofiles-2.C
	rm -f   cut-$(VERSION)
	ln -s . cut-$(VERSION)
	tar czf $@ $(addprefix cut-$(VERSION)/,$^)
	rm -f   cut-$(VERSION)
