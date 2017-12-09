#include <iostream>
#include <memory>
#include <string>
#include <cxxabi.h>
#include <grpc++/grpc++.h>
#include "sl_global.grpc.pb.h" 
#include "sl_global.pb.h"
#include "sl_common_types.pb.h"
#include "sl_version.pb.h"
#include <thread>
#include <typeinfo>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc:: CompletionQueue;
using grpc::Status;
using service_layer::SLInitMsg;
using service_layer::SLVersion;
using service_layer::SLGlobal;

void AsyncInit(std::shared_ptr<Channel> channel, grpc::CompletionQueue* cq_) {

  std::cout << "Started Thread";
  auto stub_ = service_layer::SLGlobal::NewStub(channel);

  service_layer::SLInitMsg init_msg;
  init_msg.set_majorver(service_layer::SL_MAJOR_VERSION);
  init_msg.set_minorver(service_layer::SL_MINOR_VERSION);
  init_msg.set_subver(service_layer::SL_SUB_VERSION);

  unsigned int timeout = 365*24*60*60;
  // Set timeout for API
  std::chrono::system_clock::time_point deadline =
    std::chrono::system_clock::now() + std::chrono::seconds(timeout);

  grpc::ClientContext context;
  context.set_deadline(deadline);

  std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::service_layer::SLGlobalNotif>> response_reader;

  response_reader = stub_->AsyncSLGlobalInitNotif(&context, init_msg, cq_, (void *)1);

}

int main(int argc, char** argv) {
  std::cout << "Modified Channel to grpc::Channel";
  //std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel("10.0.2.2:57345", grpc::InsecureChannelCredentials());

  auto channel = grpc::CreateChannel("10.0.2.2:57345", grpc::InsecureChannelCredentials());
  //std::unique_ptr<service_layer::SLGlobal::Stub> stub_ = service_layer::SLGlobal::NewStub(channel);

  std::unique_ptr<service_layer::SLGlobal::Stub> stub_;
  stub_ = service_layer::SLGlobal::NewStub(channel);
  grpc::CompletionQueue cq_;

  std::cout << "\n";
  std::cout << typeid(stub_).name();
  std::cout << "\n";


  // unmangled
  int status = 0;
  char* demangled = abi::__cxa_demangle(typeid(stub_).name(), 0, 0, &status);

  switch (status) {
    case -1: {
      // could not allocate memory
      std::cout << "Could not allocate memory" << std::endl;
      return -1;
    } break;
    case -2: {
      // invalid name under the C++ ABI mangling rules
      std::cout << "Invalid name" << std::endl;
      return -1;
    } break;
    case -3: {
      // invalid argument
      std::cout << "Invalid argument to demangle()" << std::endl;
      return -1;
    } break;
 }
 std::cout << demangled << std::endl;

 free(demangled);

  std::thread thread_ = std::thread(&AsyncInit, channel, &cq_);  

  service_layer::SLGlobalNotif notif;
  void* got_tag;
  bool ok = false;


//  while (cq_.Next(&got_tag, &ok)) {
//    std::cout << "Inside";
//    if (ok && got_tag == (void *)1) {
//      response_reader->Read(&notif, got_tag);
//      if (got_tag == (void *)1) {
         std::cout << "Received a response";
//      }
//    }
//  }




  thread_.join(); 
  std::cout << "Modified Channel to grpc::Channel"; 
  return 0;
}
