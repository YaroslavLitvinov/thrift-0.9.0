#include "./gen-cpp/testa_constants.h"
#include "./gen-cpp/testa_constants.cpp"
#include "./gen-cpp/testa_types.tcc"
#include "./gen-cpp/testa_types.h"
#include "./gen-cpp/testa_types.cpp"

#include <boost/shared_ptr.hpp>
#include <thrift/transport/TFDTransport.h>
#include <thrift/protocol/TDebugProtocol.h>

using namespace boost;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;


int main(){
    testa aa;
    aa.integer=1;

    boost::shared_ptr<TTransport> transport(new TFDTransport(0));
    boost::shared_ptr<TDebugProtocol> protocol(new TDebugProtocol(transport));

    aa.read(protocol.get());
    
    return 0;
}
