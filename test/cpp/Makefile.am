#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements. See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership. The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License. You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied. See the License for the
# specific language governing permissions and limitations
# under the License.
#
noinst_LTLIBRARIES = libtestgencpp.la libstresstestgencpp.la
nodist_libtestgencpp_la_SOURCES = \
	gen-cpp/ThriftTest_constants.cpp \
	gen-cpp/ThriftTest_types.cpp \
	gen-cpp/ThriftTest_constants.h \
	gen-cpp/ThriftTest_types.h \
	gen-cpp/ThriftTest_types.tcc \
	gen-cpp/ThriftTest.tcc

libtestgencpp_la_LIBADD = $(top_builddir)/lib/cpp/libthrift.la

nodist_libstresstestgencpp_la_SOURCES = \
	gen-cpp/StressTest_constants.cpp \
	gen-cpp/StressTest_types.cpp \
	gen-cpp/StressTest_constants.h \
	gen-cpp/StressTest_types.h \
	gen-cpp/Service.cpp \
	gen-cpp/Service.h

libstresstestgencpp_la_LIBADD = $(top_builddir)/lib/cpp/libthrift.la

check_PROGRAMS = \
	TestServer \
	TestClient \
	StressTest \
	StressTestNonBlocking

# we currently do not run the testsuite, stop c++ server issue
# TESTS = \
#	$(check_PROGRAMS)

TestServer_SOURCES = \
	src/TestServer.cpp

TestServer_LDADD = \
	libtestgencpp.la \
	$(top_builddir)/lib/cpp/libthrift.la \
	$(top_builddir)/lib/cpp/libthriftz.la \
	$(top_builddir)/lib/cpp/libthriftnb.la \
	-levent -lboost_program_options

TestClient_SOURCES = \
	src/TestClient.cpp

TestClient_LDADD = \
	libtestgencpp.la \
	$(top_builddir)/lib/cpp/libthrift.la \
	$(top_builddir)/lib/cpp/libthriftz.la \
	$(top_builddir)/lib/cpp/libthriftnb.la \
	-levent -lboost_program_options

StressTest_SOURCES = \
	src/StressTest.cpp

StressTest_LDADD = \
	libstresstestgencpp.la \
	$(top_builddir)/lib/cpp/libthrift.la

StressTestNonBlocking_SOURCES = \
	src/StressTestNonBlocking.cpp

StressTestNonBlocking_LDADD = \
	libstresstestgencpp.la \
	$(top_builddir)/lib/cpp/libthriftnb.la \
	-levent
#
# Common thrift code generation rules
#
THRIFT = $(top_builddir)/compiler/cpp/thrift

TMPTAR=export.tar
TMPTAR=export.tar
ZRUN=zvsh --zvm-save-dir zvsh-temp --zvm-debug --zvm-image $(TMPTAR) --zvm-image $(TMPTAR),/,wo --zvm-verbosity 4 

gen-cpp/ThriftTest.cpp gen-cpp/ThriftTest_types.cpp gen-cpp/ThriftTest_constants.cpp: $(top_srcdir)/test/ThriftTest.thrift
	mkdir gen-cpp -p
	tar -cf $(TMPTAR) gen-cpp $< ~/Pictures/magic5555550.png ~/Downloads/18052014017.mp4
	$(ZRUN) $(THRIFT) --gen cpp:templates,cob_style -r $<
	tar xvf $(TMPTAR) -C . > /dev/null 2>&1

gen-cpp/ThriftTest.cpp gen-cpp/StressTest_types.cpp gen-cpp/StressTest_constants.cpp: $(top_srcdir)/test/StressTest.thrift
	mkdir gen-cpp -p
	tar -cf $(TMPTAR) gen-cpp $< ~/Pictures/magic5555550.png ~/Downloads/18052014017.mp4
	$(ZRUN) $(THRIFT) --gen cpp $<
	tar xvf $(TMPTAR) -C . > /dev/null 2>&1

INCLUDES = \
	-I$(top_srcdir)/lib/cpp/src -Igen-cpp

AM_CPPFLAGS = $(BOOST_CPPFLAGS) $(LIBEVENT_CPPFLAGS)
AM_CXXFLAGS = -Wall
AM_LDFLAGS = $(BOOST_LDFLAGS) $(LIBEVENT_LDFLAGS)

clean-local:
	$(RM) -r gen-cpp

EXTRA_DIST = \
	src/TestClient.cpp \
	src/TestServer.cpp \
	src/StressTest.cpp \
	src/StressTestNonBlocking.cpp \
	realloc/realloc_test.c \
	realloc/Makefile
