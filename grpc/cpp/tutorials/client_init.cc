#include <iostream>
#include <memory>
#include <string>
#include <csignal>

#include <grpc++/grpc++.h>
#include "sl_global.grpc.pb.h" 
#include "sl_global.pb.h"
#include "sl_common_types.pb.h"
#include "sl_version.pb.h"
#include <thread>
#include <typeinfo>
#include <condition_variable>

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

std::mutex m_mutex;
std::condition_variable m_condVar;
bool m_InitSuccess;

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
            // The tag is the memory location of the call object
            ResponseHandler* responseHandler = static_cast<ResponseHandler*>(got_tag);

            // Verify that the request was completed successfully. Note that "ok"
            // corresponds solely to the request for updates introduced by Finish().
            responseHandler->HandleResponse(ok);
        }
    }

private:

    class ResponseHandler {
    public:
        virtual void HandleResponse(bool eventStatus) = 0;
    };

    // struct for keeping state and data information
    class AsyncClientCall: public ResponseHandler {
        enum CallStatus {CREATE, PROCESS, FINISH};
        CallStatus callStatus_;
    public:
        AsyncClientCall(): callStatus_(CREATE) {}

        // Container for the data we expect from the server.
        service_layer::SLGlobalNotif notif;
        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        grpc::ClientContext context;

        // Storage for the status of the RPC upon completion.
        Status status;

        //std::unique_ptr<ClientAsyncResponseReader<HelloReply>> response_reader;
        std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::service_layer::SLGlobalNotif>> response_reader;

        void HandleResponse(bool responseStatus) override {
            //The First completion queue entry indicates session creation and shouldn't be processed - Check?
            switch (callStatus_) {
            case CREATE:
                if (responseStatus) {
                    response_reader->Read(&notif, (void*)this);
                    callStatus_ = PROCESS;
                } else {
                    response_reader->Finish(&status, (void*)this);
                    callStatus_ = FINISH;
                }
                break;
            case PROCESS:
                if (responseStatus) {
                    response_reader->Read(&notif, (void *)this);
                    auto slerrstatus = static_cast<int>(notif.errstatus().status());
                    auto eventtype = static_cast<int>(notif.eventtype());

                    if( eventtype == static_cast<int>(service_layer::SL_GLOBAL_EVENT_TYPE_VERSION) ) {
                        if((slerrstatus == 
                               service_layer::SLErrorStatus_SLErrno_SL_SUCCESS) ||
                           (slerrstatus == 
                               service_layer::SLErrorStatus_SLErrno_SL_INIT_STATE_READY) ||
                           (slerrstatus == 
                               service_layer::SLErrorStatus_SLErrno_SL_INIT_STATE_CLEAR)) {
                            std::cout << "Server returned " ; 
                            std::cout << "Successfully Initialized, connection Established!" << std::endl;
                            
                            // Lock the mutex before notifying using the conditional variable
                            std::lock_guard<std::mutex> guard(m_mutex);

                            // Set the initsuccess flag to indicate successful initialization
                            m_InitSuccess = true;
         
                            // Notify the condition variable;
                            m_condVar.notify_one();

                        } else {
                            std::cout << "client init error code " << slerrstatus << std::endl;
                        }
                    } else if (eventtype == static_cast<int>(service_layer::SL_GLOBAL_EVENT_TYPE_HEARTBEAT)) {
                        std::cout << "Received Heartbeat" << std::endl; 
                    } else if (eventtype == static_cast<int>(service_layer::SL_GLOBAL_EVENT_TYPE_ERROR)) {
                        if (slerrstatus == service_layer::SLErrorStatus_SLErrno_SL_NOTIF_TERM) {
                            std::cout << "Received notice to terminate. Client Takeover?" << std::endl;
                            //response_reader->Finish(&status, (void*)this);
                            //callStatus_ = FINISH;
                        } else {
                            std::cout << "Error Not Handled " << slerrstatus << std::endl;
                        } 
                    } else {
                        std::cout << "client init unrecognized response " << eventtype << std::endl;
                    }
                } else {
                    response_reader->Finish(&status, (void*)this);
                    callStatus_ = FINISH;
                }
                break;
            case FINISH:
                if (status.ok()) {
                    std::cout << "Server Response Completed: " << this << " CallData: " << this << std::endl;
                }
                else {
                    std::cout << "RPC failed" << std::endl;
                }
                delete this;
                std::exit(0);
            }
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

    // Acquire the lock
    std::unique_lock<std::mutex> mlock(m_mutex);

    // Spawn reader thread that loops indefinitely
    std::thread thread_ = std::thread(&AsyncNotifChannel::AsyncCompleteRpc, &asynchandler);


    service_layer::SLInitMsg init_msg;
    init_msg.set_majorver(service_layer::SL_MAJOR_VERSION);
    init_msg.set_minorver(service_layer::SL_MINOR_VERSION);
    init_msg.set_subver(service_layer::SL_SUB_VERSION);


    asynchandler.SendInitMsg(init_msg);  

    // Wait on the mutex lock
    while (!m_InitSuccess) {
        m_condVar.wait(mlock);
    }


    std::cout << "Press control-c to quit" << std::endl << std::endl;
    thread_.join();

    return 0;
}

