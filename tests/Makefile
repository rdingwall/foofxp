#  Copyright (c) 2007, Richard Dingwall
#  All rights reserved.
# 
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are met:
# 
#      * Redistributions of source code must retain the above copyright notice,
#        this list of conditions and the following disclaimer.
#      * Redistributions in binary form must reproduce the above copyright
#        notice, this list of conditions and the following disclaimer in the
#        documentation and/or other materials provided with the distribution.
#      * Neither the name of the organization nor the names of its contributors
#        may be used to endorse or promote products derived from this software
#        without specific prior written permission.
# 
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
#  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
#  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
#  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
#  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
#  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
#  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
#  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
#  POSSIBILITY OF SUCH DAMAGE.

include ../common.in

# Executable that will be produced.
BIN = ../../bin/all_tests

# FooFXP source dir.
FOOFXP_SRC_DIR = ../foofxp

# FooFXP objs dir.
FOOFXP_OBJS_DIR = ../foofxp

CXXFLAGS = -I$(FOOFXP_SRC_DIR) -g -I$(BOOST_INCLUDE_DIR) $(FLAGS) -DBOOST_TEST_DYN_LINK
LDFLAGS = -L$(BOOST_LIB_DIR) -L$(FOOFXP_OBJS_DIR) -lboost_system -lboost_unit_test_framework

TESTS = all_tests.o from_string_tests.o to_string_tests.o enforce_tests.o

#TESTS = basic_file_tests.o file_tests.o all_tests.o bouncer_tests.o ftp_bookmark_tests.o from_string_tests.o to_string_tests.o enforce_tests.o section_tests.o

OBJS = $(FOOFXP_OBJS_DIR)/utility/lexical_cast/to_string.o $(FOOFXP_OBJS_DIR)/utility/lexical_cast/from_string.o

all: $(TESTS)
	$(CXX) -o $(BIN) $(TESTS) $(OBJS) $(CXXFLAGS) $(LDFLAGS)

clean:
	@$(RM) $(TESTS) $(BIN)
