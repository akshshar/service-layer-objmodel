#include <iostream>
#include <memory>
#include <string>

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

class AsyncNotifChannel {
public:
    explicit AsyncNotifChannel(std::shared_ptr<Channel> channel)
        : stub_(service_layer::SLGlobal::NewStub(channel)) {}

    // Assembles the client's payload and sends it to the server.
    void SendInitMsg(const service_layer::SLInitMsg init_msg) {
        // Call object to store rpc data
        AsyncClientCall* call = new AsyncClientCall;

        // stub_->AsyncSayHello() performs the RPC call, returning an instance to
        // store in "call". Because we are using the asynchronous API, we need to
        // hold on to the "call" instance in order to get updates on the ongoing RPC.

        std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::service_layer::SLGlobalNotif>> response_reader;

        call->response_reader = stub_->AsyncSLGlobalInitNotif(&call->context, init_msg, &cq_, (void *)call);
    }

    // Loop while listening for completed responses.
    // Prints out the response from the server.
    void AsyncCompleteRpc() {
        void* got_tag;
        bool ok = false;

        // Block until the next result is available in the completion queue "cq".
        while (cq_.Next(&got_tag, &ok)) {
            // The tag in this example is the memory location of the call object
            ResponseHandler* responseHandler = static_cast<ResponseHandler*>(got_tag);
            std::cout << "Tag received: " << responseHandler << std::endl;

            // Verify that the request was completed successfully. Note that "ok"
            // corresponds solely to the request for updates introduced by Finish().
            std::cout << "Next returned: " << ok << std::endl;
            //AsyncClientCall* callptr = static_cast<AsyncClientCall*>(got_tag);
            //callptr->response_reader->Read(&notif, (void *)callptr);
            //std::cout << typeid(notif).name();
            responseHandler->HandleResponse(ok);
        }
    }

private:

    class ResponseHandler {
    public:
        virtual bool HandleResponse(bool eventStatus) = 0;
    };

    // struct for keeping state and data information
    class AsyncClientCall: public ResponseHandler {
        enum CallStatus {CREATE, PROCESS, PROCESSED, FINISH};
        CallStatus callStatus_;
    public:
        AsyncClientCall(): callStatus_(CREATE) {}

        // Container for the data we expect from the server.
        service_layer::SLGlobalNotif notif;
        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        grpc::ClientContext context;

        //std::unique_ptr<ClientAsyncResponseReader<HelloReply>> response_reader;
        std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::service_layer::SLGlobalNotif>> response_reader;

        bool HandleResponse(bool responseStatus) override {
            std::cout << "Handling response "<< responseStatus << std::endl;
            response_reader->Read(&notif, (void *)this);
            std::cout << typeid(notif).name() << std::endl;
            std::cout << notif.eventtype() << std::endl;
        }
    };


    // Out of the passed in Channel comes the stub, stored here, our view of the
    // server's exposed services.
    std::unique_ptr<service_layer::SLGlobal::Stub> stub_;

    // The producer-consumer queue we use to communicate asynchronously with the
    // gRPC runtime.
    CompletionQueue cq_;
};

int main(int argc, char** argv) {
    AsyncNotifChannel asynchandler(grpc::CreateChannel(
                              "10.0.2.2:57345", grpc::InsecureChannelCredentials()));

    // Spawn reader thread that loops indefinitely
    std::thread thread_ = std::thread(&AsyncNotifChannel::AsyncCompleteRpc, &asynchandler);


    service_layer::SLInitMsg init_msg;
    init_msg.set_majorver(service_layer::SL_MAJOR_VERSION);
    init_msg.set_minorver(service_layer::SL_MINOR_VERSION);
    init_msg.set_subver(service_layer::SL_SUB_VERSION);


    asynchandler.SendInitMsg(init_msg);  // The actual RPC call!

    std::cout << "Press control-c to quit" << std::endl << std::endl;
    thread_.join();  //blocks forever

    return 0;
}

