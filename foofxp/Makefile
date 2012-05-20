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
BIN = ../../bin/foofxp

CXXFLAGS = -g -I$(BOOST_THREAD_SAFE_SIGNALS_INCLUDE_DIR) -I$(BOOST_INCLUDE_DIR) $(FLAGS)
LDFLAGS = -L$(BOOST_LIB_DIR) -lboost_system -lboost_thread -lssl -lcrypto -lncurses

OBJS = utility/format.o curses/terminal.o curses/terminal_impl.o curses/pen.o curses/detail/color.o curses/detail/attributes.o foofxp.o utility/lexical_cast/to_string.o utility/lexical_cast/from_string.o ftp_client.o ftp/response_handlers/generic_response_handler.o

#OBJS = curses/terminal.o curses/terminal_impl.o curses/pen.o curses/detail/color.o curses/detail/attributes.o foofxp.o client_factory.o utility/lexical_cast/to_string.o utility/lexical_cast/from_string.o ftp_client.o ftp/ftp_client_impl.o utility/asio.o ftp/ftp_client_tasks/connect_to_bouncer.o windows/client_status_line.o ftp/connect_planner.

all: $(OBJS)
	$(CXX) -o $(BIN) $(OBJS) $(DEPS) $(CXXFLAGS) $(LDFLAGS)

clean:
	@$(RM) $(OBJS) $(BIN)