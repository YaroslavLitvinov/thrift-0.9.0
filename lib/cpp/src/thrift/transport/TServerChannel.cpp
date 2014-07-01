/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <cstring>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "TSocket.h"
#include "TServerChannel.h"
#include <thrift/transport/TTransportUtils.h>
#include <thrift/transport/TFDTransport.h>
#include <thrift/transport/TZlibTransport.h>

#include <boost/shared_ptr.hpp>

namespace apache { namespace thrift { namespace transport {

using namespace std;
using boost::shared_ptr;

TServerChannel::TServerChannel(std::string input, 
			       std::string output) :
  input_file_(input),
  output_file_(output),
  input_fd_(-1),
  output_fd_(-1)
 {}

TServerChannel::~TServerChannel() {
  close();
}

void TServerChannel::listen() {
  input_fd_  = open(input_file_.c_str(),  O_RDONLY);
  output_fd_ = open(output_file_.c_str(), O_WRONLY);

  if ( input_fd_==-1){
      int errno_copy = errno;
      GlobalOutput.perror("TServerChannel::listen() open() ", errno);
      close();
      throw TTransportException(TTransportException::NOT_OPEN, "Could not open input channel.", errno_copy);
  }

  if (output_fd_==-1){
      int errno_copy = errno;
      GlobalOutput.perror("TServerChannel::listen() open() ", errno);
      close();
      throw TTransportException(TTransportException::NOT_OPEN, "Could not open output channel.", errno_copy);
  }

  char errbuf[1024];
  sprintf(errbuf, "TServerChannel::listen() channels %s, %s", 
	  input_file_.c_str(), output_file_.c_str());
  GlobalOutput(errbuf);
  // ready to communicate
}
	    


shared_ptr<TTransport> TServerChannel::acceptImpl() {
    if (input_fd_ == -1 || output_fd_ == -1 ) {
	throw TTransportException(TTransportException::NOT_OPEN, "TServerChannel not listening");
    }
    char errbuf[1024];
    sprintf(errbuf, "TServerChannel::acceptImpl() channel fds: %d, %d", 
	    input_fd_, output_fd_);
    GlobalOutput(errbuf);
    return createTransport(input_fd_, output_fd_);
}

boost::shared_ptr<TTransport> TServerChannel::createTransport(int in_fd, int out_fd){
    shared_ptr<TTransport> in_trans(new TFDTransport(in_fd));
    shared_ptr<TTransport> out_trans(new TFDTransport(out_fd));
    boost::shared_ptr<TZlibTransport> in_ztrans(new TZlibTransport(in_trans));
    boost::shared_ptr<TZlibTransport> out_ztrans(new TZlibTransport(out_trans));

    boost::shared_ptr<TPipedTransport> transport(new TPipedTransport(in_ztrans, out_ztrans));
    return transport;    
}

void TServerChannel::interrupt() {
}

void TServerChannel::close() {
  if (input_fd_ != -1) {
      ::close(input_fd_);
  }
  if (output_fd_ != -1) {
      ::close(output_fd_);
  }
  input_fd_ = -1;
  output_fd_ = -1;
}

}}} // apache::thrift::transport
