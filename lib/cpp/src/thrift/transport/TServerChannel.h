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

#ifndef _THRIFT_TRANSPORT_TSERVERCHANNEL_H_
#define _THRIFT_TRANSPORT_TSERVERCHANNEL_H_ 1

#include "TServerTransport.h"
#include <boost/shared_ptr.hpp>

namespace apache { namespace thrift { namespace transport {

/**
 * ZeroVM channel implementation of TServerTransport.
 *
 */
class TServerChannel : public TServerTransport {
 public:
  TServerChannel(std::string input, std::string output);
  ~TServerChannel();

  void listen();
  void close();

  void interrupt();

 protected:
  boost::shared_ptr<TTransport> acceptImpl();
  boost::shared_ptr<TTransport> createTransport(int in_fd, int out_fd);

 private:
  std::string input_file_;
  std::string output_file_;
  int input_fd_;
  int output_fd_;
};

}}} // apache::thrift::transport

#endif // #ifndef _THRIFT_TRANSPORT_TSERVERCHANNEL_H_
