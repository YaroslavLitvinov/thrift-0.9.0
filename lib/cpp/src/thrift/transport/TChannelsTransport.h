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

#ifndef _THRIFT_TRANSPORT_TCHANNELSTRANSPORT_H_
#define _THRIFT_TRANSPORT_TCHANNELSTRANSPORT_H_ 1

#include <boost/lexical_cast.hpp>
#include <thrift/transport/TTransport.h>
#include <thrift/transport/TVirtualTransport.h>

namespace apache { namespace thrift { namespace transport {

/**
 * This transport uses two omnidirectional files for i/o
 *
 */
class TChannelsTransport : public TVirtualTransport<TChannelsTransport> {
 public:

  /**
   * @param transport_read   Reader from channel.
   * @param transport_write  Writer to channel.
   *
   */
    TChannelsTransport(boost::shared_ptr<TTransport> transport_read,
		       boost::shared_ptr<TTransport> transport_write) :
    transport_read_(transport_read),
    transport_write_(transport_write)
  {
  }

  ~TChannelsTransport();

  bool isOpen();
  bool peek();

  void open() {
    transport_read_->open();
    transport_write_->open();
  }

  void close() {
    transport_read_->close();
    transport_write_->close();
  }

  uint32_t read(uint8_t* buf, uint32_t len);

  void write(const uint8_t* buf, uint32_t len);

  void flush();

 protected:
  boost::shared_ptr<TTransport> transport_read_;
  boost::shared_ptr<TTransport> transport_write_;
};


class TChannelsTransportFactory : public TTransportFactory {
 public:
  TChannelsTransportFactory() {}
};


}}} // apache::thrift::transport

#endif // #ifndef _THRIFT_TRANSPORT_TCHANNELSTRANSPORT_H_
