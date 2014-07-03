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

#include <cassert>
#include <cstring>
#include <algorithm>
#include <thrift/transport/TChannelsTransport.h>

using std::string;

namespace apache { namespace thrift { namespace transport {


TChannelsTransport::~TChannelsTransport() {
}

bool TChannelsTransport::isOpen() {
  return transport_read_->isOpen() && transport_write_->isOpen();
}

bool TChannelsTransport::peek() {
  return transport_read_->peek() && transport_write_->peek();
}

uint32_t TChannelsTransport::read(uint8_t* buf, uint32_t len) {
  return transport_read_->read(buf, len);
}

void TChannelsTransport::write(const uint8_t* buf, uint32_t len) {
    return transport_write_->write(buf, len);
}

void TChannelsTransport::flush()  {
  return transport_write_->flush();
}

}}} // apache::thrift::transport
