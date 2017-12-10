#include <iostream>
#include <memory>
#include <string>
#include <csignal>

#include <grpc++/grpc++.h>
#include "sl_global.grpc.pb.h" 
#include "sl_global.pb.h"
#include "sl_common_types.pb.h"
#include "sl_version.pb.h"
#include "sl_route_common.pb.h"
#include "sl_route_ipv4.grpc.pb.h"
#include "sl_route_ipv6.grpc.pb.h"

#include <thread>
#include <typeinfo>
#include <condition_variable>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::CompletionQueue;
using grpc::Status;
using service_layer::SLInitMsg;
using service_layer::SLVersion;
using service_layer::SLGlobal;

std::mutex m_mutex;
std::condition_variable m_condVar;
bool m_InitSuccess;


class SLVrf {
public:
    SLVrf(std::shared_ptr<Channel> Channel,
          service_layer::SLRegOp VrfOp)
        : channel(Channel), vrfOp(VrfOp) {}


    std::shared_ptr<Channel> channel;
    service_layer::SLRegOp vrfOp;
    service_layer::SLVrfRegMsg vrfMsg;
    service_layer::SLVrfRegMsgRsp vrfMsgResp;


    void VrfRegMsgAdd(std::string vrfName,
                      unsigned int adminDistance,
                      unsigned int vrfPurgeIntervalSeconds) {
        service_layer::SLVrfReg* vrfReg = vrfMsg.add_vrfregmsgs();
        vrfReg->set_vrfname(vrfName);
        vrfReg->set_admindistance(adminDistance);
        vrfReg->set_vrfpurgeintervalseconds(vrfPurgeIntervalSeconds);
    }


    void SendRoutev4VrfRegOp() {

        // Set up the RouteV4Oper Stub
        auto stub_ = service_layer::SLRoutev4Oper::NewStub(channel);

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        grpc::ClientContext context;

        // Storage for the status of the RPC upon completion.
        grpc::Status status;        

        unsigned int timeout = 10;
        // Set timeout for API
        std::chrono::system_clock::time_point deadline =
            std::chrono::system_clock::now() + std::chrono::seconds(timeout);

        context.set_deadline(deadline);

        // Set up vrfRegMsg Operation

        vrfMsg.set_oper(vrfOp);

        //Issue the RPC         

        status = stub_->SLRoutev4VrfRegOp(&context, vrfMsg, &vrfMsgResp);

        if (status.ok()) {
            std::cout << "RPC call was successful, checking response..." << std::endl;

  
            if (vrfMsgResp.statussummary().status() ==
                   service_layer::SLErrorStatus_SLErrno_SL_SUCCESS) {

                std::cout << "IPv4 Vrf Operation:"<< vrfOp << " Successful" << std::endl;
            } else {
                std::cout << "Error code for VRF Operation:" << vrfOp << " is 0x" << std::hex << vrfMsgResp.statussummary().status() << std::endl;

                // Print Partial failures within the batch if applicable
                if (vrfMsgResp.statussummary().status() ==
                        service_layer::SLErrorStatus_SLErrno_SL_SOME_ERR) {
                    for (int result = 0; result < vrfMsgResp.results_size(); result++) {
                          auto slerrstatus = static_cast<int>(vrfMsgResp.results(result).errstatus().status());
                          std::cout << "Error code for vrf " << vrfMsgResp.results(result).vrfname() << " is 0x" << std::hex << slerrstatus << std::endl;
                    }
                } 
            }
        } else {
            std::cout << "RPC failed, error code is " << status.error_code() << std::endl;
        }
 
    }
                    
    void SendRoutev6VrfRegOp() {

        // Set up the RouteV4Oper Stub
        auto stub_ = service_layer::SLRoutev6Oper::NewStub(channel);


        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        grpc::ClientContext context;
        
        // Storage for the status of the RPC upon completion.
        grpc::Status status;
        
        unsigned int timeout = 10;
        // Set timeout for API
        std::chrono::system_clock::time_point deadline =
            std::chrono::system_clock::now() + std::chrono::seconds(timeout);
     
        context.set_deadline(deadline);

        // Set up vrfRegMsg Operation

        vrfMsg.set_oper(vrfOp);

        //Issue the RPC         

        status = stub_->SLRoutev6VrfRegOp(&context, vrfMsg, &vrfMsgResp);

        if (status.ok()) {
            std::cout << "RPC call was successful, checking response...";
            if (vrfMsgResp.statussummary().status() ==
                   service_layer::SLErrorStatus_SLErrno_SL_SUCCESS) {
                
                std::cout << "IPv6 Vrf Operation: "<< vrfOp << " successful" << std::endl;
            } else {
                std::cout << "Error code for VRF Operation:" << vrfOp << " is 0x" << std::hex << vrfMsgResp.statussummary().status() << std::endl;

                // Print Partial failures within the batch if applicable
                if (vrfMsgResp.statussummary().status() ==
                        service_layer::SLErrorStatus_SLErrno_SL_SOME_ERR) {
                    for (int result = 0; result < vrfMsgResp.results_size(); result++) {
                        auto slerrstatus = static_cast<int>(vrfMsgResp.results(result).errstatus().status());
                        std::cout << "Error code for vrf " << vrfMsgResp.results(result).vrfname() << " is 0x" << std::hex << slerrstatus << std::endl;
                    }
                }
            }
        } else {
            std::cout << "RPC failed, error code is " << status.error_code() << std::endl;
        }

    }
 
};


class AsyncNotifChannel {
public:
    explicit AsyncNotifChannel(std::shared_ptr<Channel> channel)
        : stub_(service_layer::SLGlobal::NewStub(channel)) {}

    // Assembles the client's payload and sends it to the server.
    void SendInitMsg(const service_layer::SLInitMsg init_msg) {
        // Call object to store rpc data
        AsyncClientCall* call = new AsyncClientCall;

        // Because we are using the asynchronous API, we need to
        // hold on to the "call" instance in order to get updates on the ongoing RPC.

        //std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::service_layer::SLGlobalNotif>> response_reader;

        call->response_reader = stub_->AsyncSLGlobalInitNotif(&call->context, init_msg, &cq_, (void *)call);
    }

    // Loop while listening for completed responses.
    // Prints out the response from the server.
    void AsyncCompleteRpc() {
        void* got_tag;
        bool ok = false;

        unsigned int timeout = 365*24*60*60;
        // Set timeout for API
        std::chrono::system_clock::time_point deadline =
            std::chrono::system_clock::now() + std::chrono::seconds(timeout);

 
        while (!tearDown) {
            auto nextStatus = cq_.AsyncNext(&got_tag, &ok, deadline);
            // The tag is the memory location of the call object
            ResponseHandler* responseHandler = static_cast<ResponseHandler*>(got_tag);

            switch(nextStatus) {
            case grpc::CompletionQueue::GOT_EVENT:
                 // Verify that the request was completed successfully. Note that "ok"
                 // corresponds solely to the request for updates introduced by Finish().
                 responseHandler->HandleResponse(ok, &cq_);
                 break;
             case grpc::CompletionQueue::SHUTDOWN:
                 std::cout << "Shutdown event received for completion queue, shutdown the thread" << std::endl;
                 delete responseHandler;
                 tearDown = true;
                 break;
             case grpc::CompletionQueue::TIMEOUT:
                 break;
            }
        }
    }

private:

    class ResponseHandler {
    public:
        virtual void HandleResponse(bool eventStatus, CompletionQueue* pcq_) = 0;
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
        grpc::Status status;

        //std::unique_ptr<ClientAsyncResponseReader<HelloReply>> response_reader;
        std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::service_layer::SLGlobalNotif>> response_reader;

        void HandleResponse(bool responseStatus, CompletionQueue* pcq_) override {
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
                std::cout << "Shutting down the completion queue" << std::endl;
                pcq_->Shutdown();
            }
        } 
    };


    // Out of the passed in Channel comes the stub, stored here, our view of the
    // server's exposed services.
    std::unique_ptr<service_layer::SLGlobal::Stub> stub_;

    // The producer-consumer queue we use to communicate asynchronously with the
    // gRPC runtime.
    CompletionQueue cq_;

    // Used as an indicator to exit completion queue thread upon queue shutdown.
    bool tearDown = false;
};

int main(int argc, char** argv) {
    AsyncNotifChannel asynchandler(grpc::CreateChannel(
                              "10.0.2.2:57345", grpc::InsecureChannelCredentials()));

    // Acquire the lock
    std::unique_lock<std::mutex> mlock(m_mutex);

    // Spawn reader thread that maintains our Notification Channel
    std::thread thread_ = std::thread(&AsyncNotifChannel::AsyncCompleteRpc, &asynchandler);


    service_layer::SLInitMsg init_msg;
    init_msg.set_majorver(service_layer::SL_MAJOR_VERSION);
    init_msg.set_minorver(service_layer::SL_MINOR_VERSION);
    init_msg.set_subver(service_layer::SL_SUB_VERSION);


    asynchandler.SendInitMsg(init_msg);  

    // Wait on the mutex lock
    while (!m_InitSuccess) {
        std::cout << "Indicator Set" << std::endl;
        m_condVar.wait(mlock);
        std::cout << "Good to go!" << std::endl;
    }



    SLVrf vrfhandler(grpc::CreateChannel(
                              "10.0.2.2:57345", grpc::InsecureChannelCredentials()),
                     service_layer::SL_REGOP_REGISTER);

    vrfhandler.VrfRegMsgAdd("test123", 10, 500);
    vrfhandler.VrfRegMsgAdd("test1", 12, 500);
    vrfhandler.VrfRegMsgAdd("test2", 13, 500);
    vrfhandler.VrfRegMsgAdd("test3", 14, 500);
    vrfhandler.VrfRegMsgAdd("test4", 15, 500);
    vrfhandler.VrfRegMsgAdd("test5", 16, 500);
    vrfhandler.VrfRegMsgAdd("test6", 17, 500);
    vrfhandler.SendRoutev6VrfRegOp();
    vrfhandler.SendRoutev4VrfRegOp();

    vrfhandler.vrfMsg.clear_vrfregmsgs();

    vrfhandler.VrfRegMsgAdd("test", 10, 500);
    vrfhandler.VrfRegMsgAdd("test1", 12, 500);
    vrfhandler.VrfRegMsgAdd("test2", 13, 500);

    vrfhandler.vrfOp = service_layer::SL_REGOP_UNREGISTER;

    vrfhandler.SendRoutev6VrfRegOp();
    vrfhandler.SendRoutev4VrfRegOp();


    std::cout << "Press control-c to quit" << std::endl << std::endl;
    thread_.join();

    return 0;
}

