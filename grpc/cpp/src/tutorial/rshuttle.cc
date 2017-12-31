#include "quickstart.h"
#include <google/protobuf/text_format.h>
#include <csignal>

using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::CompletionQueue;
using grpc::Status;
using service_layer::SLInitMsg;
using service_layer::SLVersion;
using service_layer::SLGlobal;


std::mutex init_mutex;
std::condition_variable init_condVar;
bool init_success;


uint32_t RShuttle::ipv4ToLong(const char* address)
{
    struct sockaddr_in sa;
    if (inet_pton(AF_INET, address, &(sa.sin_addr)) != 1) {
        LOG(ERROR) << "Invalid IPv4 address " << address; 
        return 0;
    }

    return ntohl(sa.sin_addr.s_addr);
}

std::string RShuttle::ipv6ToByteArrayString(const char* address)
{
    //const char *ipv6str = address;
    struct in6_addr ipv6data;
    if (inet_pton(AF_INET6, address, &ipv6data) != 1 ) {
        LOG(ERROR) << "Invalid IPv6 address " << address; 
        return 0;
    }

    const char *ptr(reinterpret_cast<const char*>(&ipv6data.s6_addr));
    std::string ipv6_charstr(ptr, ptr+16);
    return ipv6_charstr;
}


RShuttle::RShuttle(std::shared_ptr<grpc::Channel> Channel)
    : channel(Channel) {} 


service_layer::SLRoutev4* 
    RShuttle::routev4Add(std::string vrfName)
{
    routev4_msg.set_vrfname(vrfName);
    return routev4_msg.add_routes();
}

// Overloaded method to Set V4 route without Admin Distance.
// Used for DELETE Operation

void RShuttle::routev4Set(service_layer::SLRoutev4* routev4Ptr,
                          uint32_t prefix,
                          uint32_t prefixLen)
{   
    routev4Ptr->set_prefix(prefix);
    routev4Ptr->set_prefixlen(prefixLen);
}


// Overloaded method to Set V4 route without Admin Distance.
// Used for ADD or UPDATE Operation


void RShuttle::routev4Set(service_layer::SLRoutev4* routev4Ptr,
                          uint32_t prefix,
                          uint32_t prefixLen,
                          uint32_t adminDistance)
{
    routev4Ptr->set_prefix(prefix);
    routev4Ptr->set_prefixlen(prefixLen);
    routev4Ptr->mutable_routecommon()->set_admindistance(adminDistance);
}


void RShuttle::routev4PathAdd(service_layer::SLRoutev4* routev4Ptr,
                              uint32_t nextHopAddress,
                              std::string nextHopIf)
{
    
    auto routev4PathPtr = routev4Ptr->add_pathlist();
    routev4PathPtr->mutable_nexthopaddress()->set_v4address(nextHopAddress);
    routev4PathPtr->mutable_nexthopinterface()->set_name(nextHopIf);
}

void RShuttle::routev4Op(service_layer::SLObjectOp routeOp,
                         unsigned int timeout)
{

    // Convert ADD to UPDATE automatically, it will solve both the 
    // conditions - add or update.

   // if (routeOp == service_layer::SL_OBJOP_ADD) {
   //     routeOp = service_layer::SL_OBJOP_UPDATE;
   // }

    route_op = routeOp;
    routev4_msg.set_oper(route_op);

    auto stub_ = service_layer::SLRoutev4Oper::NewStub(channel); 

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    grpc::ClientContext context;

    // Storage for the status of the RPC upon completion.
    grpc::Status status;

    // Set timeout for RPC
    std::chrono::system_clock::time_point deadline =
        std::chrono::system_clock::now() + std::chrono::seconds(timeout);

    context.set_deadline(deadline);

    //Issue the RPC         
    std::string s;

    if (google::protobuf::TextFormat::PrintToString(routev4_msg, &s)) {
        VLOG(2) << "###########################" ;
        VLOG(2) << "Transmitted message: IOSXR-SL RouteV4 " << s;
        VLOG(2) << "###########################" ;
    } else {
        VLOG(2) << "###########################" ;
        VLOG(2) << "Message not valid (partial content: "
                  << routev4_msg.ShortDebugString() << ")";
        VLOG(2) << "###########################" ;
    }

    status = stub_->SLRoutev4Op(&context, routev4_msg, &routev4_msg_resp);

    if (status.ok()) {
        VLOG(1) << "RPC call was successful, checking response...";


        if (routev4_msg_resp.statussummary().status() ==
               service_layer::SLErrorStatus_SLErrno_SL_SUCCESS) {

            VLOG(1) << "IPv4 Route Operation:"<< route_op << " Successful"; 
        } else {
            LOG(ERROR) << "IPv4 Route Operation Unsuccessful!"
                       << "Error code for IPv4 Route Operation:" << route_op 
                       << " is 0x" << std::hex << routev4_msg_resp.statussummary().status(); 

            // Print Partial failures within the batch if applicable
            if (routev4_msg_resp.statussummary().status() ==
                    service_layer::SLErrorStatus_SLErrno_SL_SOME_ERR) {
                for (int result = 0; result < routev4_msg_resp.results_size(); result++) {
                      auto slerr_status = static_cast<int>(routev4_msg_resp.results(result).errstatus().status());
                      LOG(ERROR) << "Error code for prefix: " 
                                 << routev4_msg_resp.results(result).prefix() 
                                 << " prefixlen: " << routev4_msg_resp.results(result).prefixlen()
                                 <<" is 0x"<< std::hex << slerr_status;
                }
            }
        }
    } else {
        LOG(ERROR) << "RPC failed, error code is " << status.error_code(); 
    }
}

void RShuttle::insertAddBatchV4(std::string vrfName,
                                std::string prefix,
                                uint32_t prefixLen,
                                uint32_t adminDistance,
                                std::string nextHopAddress,
                                std::string nextHopIf)
{

    auto address = prefix + "/" + std::to_string(prefixLen);
    auto map_index = this->routev4_msg.routes_size();

    if (this->prefix_map_v4.find(address) == this->prefix_map_v4.end()) {

        // Obtain pointer to a new route object within route batch
        auto routev4_ptr = this->routev4Add(vrfName);
        
        // Set up the new v4 route object
        this->routev4Set(routev4_ptr, 
                         ipv4ToLong(prefix.c_str()),
                         prefixLen, 
                         adminDistance);
        this->prefix_map_v4[address] = map_index;
    
        this->routev4PathAdd(routev4_ptr, 
                             ipv4ToLong(nextHopAddress.c_str()), 
                             nextHopIf); 

    } else {
        auto routev4_ptr = this->routev4_msg.mutable_routes(prefix_map_v4[address]);
        this->routev4PathAdd(routev4_ptr,
                             ipv4ToLong(nextHopAddress.c_str()),
                             nextHopIf);  
    }
}


void RShuttle::insertDeleteBatchV4(std::string vrfName,
                                   std::string prefix,
                                   uint32_t prefixLen)
{

    // Obtain pointer to a new route object within route batch
    auto routev4_ptr = this->routev4Add(vrfName);
    
    // Set up the new v4 route object 
    this->routev4Set(routev4_ptr, 
                     ipv4ToLong(prefix.c_str()),
                     prefixLen);
}

void RShuttle::clearBatchV4()
{
   routev4_msg.clear_routes(); 
   prefix_map_v4.clear();
}


bool RShuttle::prefixInAppRibV4(std::string vrfName,
                                std::string prefix,
                                uint32_t prefixLen,
                                unsigned int timeout)
{
   
    auto stub_ = service_layer::SLRoutev4Oper::NewStub(channel);
    service_layer::SLRoutev4GetMsg routev4_get_msg; 
    service_layer::SLRoutev4GetMsgRsp routev4_get_msg_resp;
 
    routev4_get_msg.set_vrfname(vrfName);
    routev4_get_msg.set_prefix(ipv4ToLong(prefix.c_str()));
    routev4_get_msg.set_prefixlen(prefixLen); 
    routev4_get_msg.set_entriescount(1);
    routev4_get_msg.set_getnext(false);


    // Context for the client.
    grpc::ClientContext context;

    // Storage for the status of the RPC upon completion.
    grpc::Status status;

    // Set timeout for RPC
    std::chrono::system_clock::time_point deadline =
        std::chrono::system_clock::now() + std::chrono::seconds(timeout);

    context.set_deadline(deadline);


    //Issue the RPC         
    std::string s;

    if (google::protobuf::TextFormat::PrintToString(routev4_get_msg, &s)) {
        VLOG(2) << "###########################" ;
        VLOG(2) << "Transmitted message: IOSXR-SL Route Get " << s;
        VLOG(2) << "###########################" ;
    } else {
        VLOG(2) << "###########################" ;
        VLOG(2) << "Message not valid (partial content: "
                << routev4_get_msg.ShortDebugString() << ")";
        VLOG(2) << "###########################" ;
    }

    //Issue the RPC         

    status = stub_->SLRoutev4Get(&context, routev4_get_msg, &routev4_get_msg_resp);

    if (status.ok()) {
         VLOG(1) << "RPC call was successful, checking response...";


        auto slerr_status =
        static_cast<int>(routev4_get_msg_resp.errstatus().status());


        if (slerr_status ==
               service_layer::SLErrorStatus_SLErrno_SL_SUCCESS) {

            VLOG(1) << "IPv4 Route GET Operation successful";
//            for (int entry = 0; entry < routev4_get_msg_resp.entries_size(); entry++) {
                
//            }
            //print the Response         
            std::string s;

            if (google::protobuf::TextFormat::PrintToString(routev4_get_msg_resp, &s)) {
                VLOG(2) << "###########################" ;
                VLOG(2) << "Received  message: IOSXR-SL Route Get " << s;
                VLOG(2) << "###########################" ;
            } else {
                VLOG(2) << "###########################" ;
                VLOG(2) << "Message not valid (partial content: "
                        << routev4_get_msg_resp.ShortDebugString() << ")";
                VLOG(2) << "###########################" ;

            }
            return true;
        } else {
            LOG(ERROR) << "Error code for vrf "
                       << routev4_get_msg_resp.vrfname()
                       <<" is 0x"<< std::hex << slerr_status;
            return false;
        }
    } else {
        LOG(ERROR) << "RPC failed, error code is " << status.error_code();
    }


}


service_layer::SLRoutev6*
    RShuttle::routev6Add(std::string vrfName)
{
    routev6_msg.set_vrfname(vrfName);
    return routev6_msg.add_routes();
}


// Overloaded method to Set V4 route without Admin Distance.
// Used for DELETE Operation

void RShuttle::routev6Set(service_layer::SLRoutev6* routev6Ptr,
                          std::string prefix,
                          uint32_t prefixLen)
{
    routev6Ptr->set_prefix(prefix);
    routev6Ptr->set_prefixlen(prefixLen);
}


// Overloaded method to Set V4 route without Admin Distance.
// Used for ADD or UPDATE Operation

void RShuttle::routev6Set(service_layer::SLRoutev6* routev6Ptr,
                          std::string prefix,
                          uint32_t prefixLen,
                          uint32_t adminDistance)
{
    routev6Ptr->set_prefix(prefix);
    routev6Ptr->set_prefixlen(prefixLen);
    routev6Ptr->mutable_routecommon()->set_admindistance(adminDistance);
}

void RShuttle::routev6PathAdd(service_layer::SLRoutev6* routev6Ptr,
                              std::string nextHopAddress,
                              std::string nextHopIf)
{

    auto routev6PathPtr = routev6Ptr->add_pathlist();
    routev6PathPtr->mutable_nexthopaddress()->set_v6address(nextHopAddress);
    routev6PathPtr->mutable_nexthopinterface()->set_name(nextHopIf);
}

void RShuttle::routev6Op(service_layer::SLObjectOp routeOp,
                         unsigned int timeout)
{                      

    // Convert ADD to UPDATE automatically, it will solve both the 
    // conditions - add or update.
    
   // if (routeOp == service_layer::SL_OBJOP_ADD) {
    //    routeOp = service_layer::SL_OBJOP_UPDATE;
    //}
    
    route_op = routeOp;
    routev6_msg.set_oper(route_op);


    auto stub_ = service_layer::SLRoutev6Oper::NewStub(channel);

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    grpc::ClientContext context;

    // Storage for the status of the RPC upon completion.
    grpc::Status status;

    // Set timeout for RPC
    std::chrono::system_clock::time_point deadline =
        std::chrono::system_clock::now() + std::chrono::seconds(timeout);

    context.set_deadline(deadline);


    //Issue the RPC         
    std::string s;

    if (google::protobuf::TextFormat::PrintToString(routev6_msg, &s)) {
        VLOG(2) << "###########################" ;
        VLOG(2) << "Transmitted message: IOSXR-SL RouteV6 " << s;
        VLOG(2) << "###########################" ;
    } else {
        VLOG(2) << "###########################" ;
        VLOG(2) << "Message not valid (partial content: "
                << routev6_msg.ShortDebugString() << ")";
        VLOG(2) << "###########################" ;
    }

    //Issue the RPC         

    status = stub_->SLRoutev6Op(&context, routev6_msg, &routev6_msg_resp);

    if (status.ok()) {
         VLOG(1) << "RPC call was successful, checking response...";


        if (routev6_msg_resp.statussummary().status() ==
               service_layer::SLErrorStatus_SLErrno_SL_SUCCESS) {

            VLOG(1) << "IPv6 Route Operation:"<< route_op << " Successful";
        } else {
            LOG(ERROR) << "Error code for IPv6 Route Operation:" 
                       << route_op 
                       << " is 0x" << std::hex 
                       << routev6_msg_resp.statussummary().status();

            // Print Partial failures within the batch if applicable
            if (routev6_msg_resp.statussummary().status() ==
                    service_layer::SLErrorStatus_SLErrno_SL_SOME_ERR) {
                for (int result = 0; result < routev6_msg_resp.results_size(); result++) {
                      auto slerr_status = 
                      static_cast<int>(routev6_msg_resp.results(result).errstatus().status());
                      LOG(ERROR) << "Error code for prefix: " 
                                 << routev6_msg_resp.results(result).prefix() 
                                 << " prefixlen: " 
                                 << routev6_msg_resp.results(result).prefixlen()
                                 <<" is 0x"<< std::hex << slerr_status; 

                }
            }
        }
    } else {
        LOG(ERROR) << "RPC failed, error code is " << status.error_code();
    }
}


void RShuttle::insertAddBatchV6(std::string vrfName,
                                std::string prefix,
                                uint32_t prefixLen,
                                uint32_t adminDistance,
                                std::string nextHopAddress,
                                std::string nextHopIf)
{   
    auto address = prefix + "/" + std::to_string(prefixLen);
    auto map_index = this->routev6_msg.routes_size();

    if (this->prefix_map_v6.find(address) == this->prefix_map_v6.end()) {
        
        // Obtain pointer to a new route object within route batch
        auto routev6_ptr = this->routev6Add(vrfName);

        // Set up the new v6 route object
        this->routev6Set(routev6_ptr, 
                         ipv6ToByteArrayString(prefix.c_str()),
                         prefixLen, 
                         adminDistance);
        this->prefix_map_v6[address] = map_index;
    
        this->routev6PathAdd(routev6_ptr,
                             ipv6ToByteArrayString(nextHopAddress.c_str()),
                             nextHopIf);

    } else {
        auto routev6_ptr = this->routev6_msg.mutable_routes(prefix_map_v6[address]);
        this->routev6PathAdd(routev6_ptr,
                             ipv6ToByteArrayString(nextHopAddress.c_str()),
                             nextHopIf);
    }

}


void RShuttle::insertDeleteBatchV6(std::string vrfName,
                                   std::string prefix,
                                   uint32_t prefixLen)
{   
    
    // Obtain pointer to a new route object within route batch
    auto routev6_ptr = this->routev6Add(vrfName);
    
    // Set up the new v6 route object 
    this->routev6Set(routev6_ptr, 
                     ipv6ToByteArrayString(prefix.c_str()),
                     prefixLen);
}

void RShuttle::clearBatchV6()
{
   routev6_msg.clear_routes();
   prefix_map_v6.clear();
}



SLVrf::SLVrf(std::shared_ptr<grpc::Channel> Channel)
    : channel(Channel) {}

// Overloaded variant of vrfRegMsgAdd without adminDistance and Purgeinterval
// Suitable for VRF UNREGISTER and REGISTER operations

void SLVrf::vrfRegMsgAdd(std::string vrfName) {

    // Get a pointer to a new vrf_reg entry in vrf_msg
    service_layer::SLVrfReg* vrf_reg = vrf_msg.add_vrfregmsgs();

    // Populate the new vrf_reg entry
    vrf_reg->set_vrfname(vrfName);
}

// Overloaded variant of vrfRegMsgAdd with adminDistance and Purgeinterval
// Suitable for VRF REGISTER

void SLVrf::vrfRegMsgAdd(std::string vrfName,
                         unsigned int adminDistance,
                         unsigned int vrfPurgeIntervalSeconds) {

    // Get a pointer to a new vrf_reg entry in vrf_msg
    service_layer::SLVrfReg* vrf_reg = vrf_msg.add_vrfregmsgs();

    // Populate the new vrf_reg entry
    vrf_reg->set_vrfname(vrfName);
    vrf_reg->set_admindistance(adminDistance);
    vrf_reg->set_vrfpurgeintervalseconds(vrfPurgeIntervalSeconds);
}


void SLVrf::registerVrf(unsigned int addrFamily) {

    // Send an RPC for VRF registrations

    switch(addrFamily) {
    case AF_INET:
        vrfOpv4(service_layer::SL_REGOP_REGISTER);

        // RPC EOF to cleanup any previous stale routes
        vrfOpv4(service_layer::SL_REGOP_EOF);

        break;

    case AF_INET6:
        vrfOpv6(service_layer::SL_REGOP_REGISTER);

        // RPC EOF to cleanup any previous stale routes
        vrfOpv6(service_layer::SL_REGOP_EOF);

        break;            

    default:
        LOG(ERROR) << "Invalid Address family, skipping..";
        break;
    }

}

void SLVrf::unregisterVrf(unsigned int addrFamily) {

    //  When done with the VRFs, RPC Delete Registration

    switch(addrFamily) {
    case AF_INET:
        vrfOpv4(service_layer::SL_REGOP_UNREGISTER);
        break;

    case AF_INET6:
        vrfOpv6(service_layer::SL_REGOP_UNREGISTER);
        break;

    default:
        LOG(ERROR) << "Invalid Address family, skipping..";
        break;
    }
}

void SLVrf::vrfOpv4(service_layer::SLRegOp vrfOp) {
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

    vrf_msg.set_oper(vrfOp);

    std::string s;

    if (google::protobuf::TextFormat::PrintToString(vrf_msg, &s)) {
        VLOG(2) << "###########################" ;
        VLOG(2) << "Transmitted message: IOSXR-SL VRF " << s;
        VLOG(2) << "###########################" ;
    } else {
        VLOG(2) << "###########################" ;
        VLOG(2) << "Message not valid (partial content: "
                << vrf_msg.ShortDebugString() << ")";
        VLOG(2) << "###########################" ;
    }


    //Issue the RPC         

    status = stub_->SLRoutev4VrfRegOp(&context, vrf_msg, &vrf_msg_resp);

    if (status.ok()) {
        VLOG(1) << "RPC call was successful, checking response...";


        if (vrf_msg_resp.statussummary().status() ==
               service_layer::SLErrorStatus_SLErrno_SL_SUCCESS) {

            VLOG(1) << "IPv4 Vrf Operation:"<< vrfOp << " Successful";
        } else {
            LOG(ERROR) << "Error code for VRF Operation:" 
                       << vrfOp 
                       << " is 0x" << std::hex 
                       << vrf_msg_resp.statussummary().status();

            // Print Partial failures within the batch if applicable
            if (vrf_msg_resp.statussummary().status() ==
                    service_layer::SLErrorStatus_SLErrno_SL_SOME_ERR) {
                for (int result = 0; result < vrf_msg_resp.results_size(); result++) {
                      auto slerr_status = 
                      static_cast<int>(vrf_msg_resp.results(result).errstatus().status());
                      LOG(ERROR) << "Error code for vrf " 
                                 << vrf_msg_resp.results(result).vrfname() 
                                 << " is 0x" << std::hex 
                                 << slerr_status;
                }
            }
        }
    } else {
        LOG(ERROR) << "RPC failed, error code is " << status.error_code();
    }
}
                    
void SLVrf::vrfOpv6(service_layer::SLRegOp vrfOp) {

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

    vrf_msg.set_oper(vrfOp);

    std::string s;

    if (google::protobuf::TextFormat::PrintToString(vrf_msg, &s)) {
        VLOG(2) << "###########################" ;
        VLOG(2) << "Transmitted message: IOSXR-SL VRF " << s;
        VLOG(2) << "###########################" ;
    } else {
        VLOG(2) << "###########################" ;
        VLOG(2) << "Message not valid (partial content: "
                  << vrf_msg.ShortDebugString() << ")";
        VLOG(2) << "###########################" ;
    }


    //Issue the RPC         

    status = stub_->SLRoutev6VrfRegOp(&context, vrf_msg, &vrf_msg_resp);

    if (status.ok()) {
        VLOG(1) << "RPC call was successful, checking response...";
        if (vrf_msg_resp.statussummary().status() ==
               service_layer::SLErrorStatus_SLErrno_SL_SUCCESS) {
            VLOG(1) << "IPv6 Vrf Operation: "<< vrfOp << " successful";
        } else {
            LOG(ERROR) << "Error code for VRF Operation:" 
                       << vrfOp 
                       << " is 0x" << std::hex 
                       << vrf_msg_resp.statussummary().status();

            // Print Partial failures within the batch if applicable
            if (vrf_msg_resp.statussummary().status() ==
                    service_layer::SLErrorStatus_SLErrno_SL_SOME_ERR) {
                for (int result = 0; result < vrf_msg_resp.results_size(); result++) {
                    auto slerr_status = 
                    static_cast<int>(vrf_msg_resp.results(result).errstatus().status());
                    LOG(ERROR) << "Error code for vrf " 
                               << vrf_msg_resp.results(result).vrfname() 
                               << " is 0x" << std::hex 
                               << slerr_status;
                }
            }
        }
    } else {
        LOG(ERROR) << "RPC failed, error code is " << status.error_code(); 
    }

}
 
AsyncNotifChannel::AsyncNotifChannel(std::shared_ptr<grpc::Channel> channel)
        : stub_(service_layer::SLGlobal::NewStub(channel)) {}


// Assembles the client's payload and sends it to the server.

void AsyncNotifChannel::SendInitMsg(const service_layer::SLInitMsg init_msg) {

    std::string s;

    if (google::protobuf::TextFormat::PrintToString(init_msg, &s)) {
        VLOG(2) << "###########################" ;
        VLOG(2) << "Transmitted message: IOSXR-SL INIT " << s;
        VLOG(2) << "###########################" ;
    } else {
        VLOG(2) << "###########################" ;
        VLOG(2) << "Message not valid (partial content: "
                  << init_msg.ShortDebugString() << ")";
        VLOG(2) << "###########################" ;
    }

    // Typically when using the asynchronous API, we hold on to the 
    //"call" instance in order to get updates on the ongoing RPC.
    // In our case it isn't really necessary, since we operate within the
    // context of the same class, but anyway, we pass it in as the tag

    call.response_reader = stub_->AsyncSLGlobalInitNotif(&call.context, init_msg, &cq_, (void *)&call);
}

void AsyncNotifChannel::Shutdown() {

    tear_down = true;

    std::unique_lock<std::mutex> channel_lock(channel_mutex);

    while(!channel_closed) {
        channel_condVar.wait(channel_lock);
    }
}


void AsyncNotifChannel::Cleanup() {
    void* got_tag;
    bool ok = false;

    VLOG(1) << "Asynchronous client shutdown requested"
            << "Let's clean up!";

    // Finish the Async session
    call.HandleResponse(false, &cq_);

    // Shutdown the completion queue
    call.HandleResponse(false, &cq_);

    VLOG(1) << "Notifying channel close";
    channel_closed = true;
    // Notify the condition variable;
    channel_condVar.notify_one();
}


// Loop while listening for completed responses.
// Prints out the response from the server.
void AsyncNotifChannel::AsyncCompleteRpc() {
    void* got_tag;
    bool ok = false;
    // Storage for the status of the RPC upon completion.
    grpc::Status status;

    // Lock the mutex before notifying using the conditional variable
    std::lock_guard<std::mutex> guard(channel_mutex);


    unsigned int timeout = 5;

    // Set timeout for API
    std::chrono::system_clock::time_point deadline =
        std::chrono::system_clock::now() + std::chrono::seconds(timeout);

    while (!tear_down) {
        auto nextStatus = cq_.AsyncNext(&got_tag, &ok, deadline);

        switch(nextStatus) {
        case grpc::CompletionQueue::GOT_EVENT:
             // Verify that the request was completed successfully. Note that "ok"
             // corresponds solely to the request for updates introduced by Finish().
             call.HandleResponse(ok, &cq_);
             break;
        case grpc::CompletionQueue::SHUTDOWN:
             VLOG(1) << "Shutdown event received for completion queue";
             channel_closed = true;
             // Notify the condition variable;
             channel_condVar.notify_one();
             tear_down = true;
             break;
        case grpc::CompletionQueue::TIMEOUT:
             continue;
             break;
        }
    }

    if(!channel_closed) {
        Cleanup();
    }
}


AsyncNotifChannel::AsyncClientCall::AsyncClientCall(): callStatus_(CREATE) {}

void AsyncNotifChannel::AsyncClientCall::HandleResponse(bool responseStatus, grpc::CompletionQueue* pcq_) {
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
                    VLOG(1) << "IOS-XR gRPC Server returned "; 
                    VLOG(1) << "Successfully Initialized, connection Established!";
                            
                    // Lock the mutex before notifying using the conditional variable
                    std::lock_guard<std::mutex> guard(init_mutex);

                    // Set the initsuccess flag to indicate successful initialization
                    init_success = true;
       
                    // Notify the condition variable;
                    init_condVar.notify_one();

                } else {
                    LOG(ERROR) << "Client init error code " << slerrstatus ;
                }
            } else if (eventtype == static_cast<int>(service_layer::SL_GLOBAL_EVENT_TYPE_HEARTBEAT)) {
                VLOG(1) << "Received Heartbeat"; 
            } else if (eventtype == static_cast<int>(service_layer::SL_GLOBAL_EVENT_TYPE_ERROR)) {
                if (slerrstatus == service_layer::SLErrorStatus_SLErrno_SL_NOTIF_TERM) {
                    LOG(ERROR) << "Received notice to terminate. Client Takeover?";
                } else {
                    LOG(ERROR) << "Error Not Handled " << slerrstatus;
                } 
            } else {
                LOG(ERROR) << "client init unrecognized response " << eventtype;
            }
        } else {
            response_reader->Finish(&status, (void*)this);
            callStatus_ = FINISH;
        }
        break;
    case FINISH:
        if (status.ok()) {
            VLOG(1) << "Server Response Completed: "  
                    << this << " CallData: " 
                    << this;
        }
        else {
            LOG(ERROR) << "RPC failed";
        }
        VLOG(1) << "Shutting down the completion queue";
        pcq_->Shutdown();
    }
} 



std::string getEnvVar( std::string const & key )
{
    char * val = std::getenv( key.c_str() );
    return val == NULL ? std::string("") : std::string(val);
}


SLVrf* vrfhandler_signum;
AsyncNotifChannel* asynchandler_signum;

void signalHandler( int signum ) {
   VLOG(1) << "Interrupt signal (" << signum << ") received.";

   // Clear out the last vrfRegMsg batch
   vrfhandler_signum->vrf_msg.clear_vrfregmsgs();

   // Create a fresh SLVrfRegMsg batch for cleanup
   vrfhandler_signum->vrfRegMsgAdd("default");

   vrfhandler_signum->unregisterVrf(AF_INET);
   vrfhandler_signum->unregisterVrf(AF_INET6);

 
   // Shutdown the Async Notification Channel  
   asynchandler_signum->Shutdown();

   // terminate program  

   exit(signum);  
}


int main(int argc, char** argv) {

    auto server_ip = getEnvVar("SERVER_IP");
    auto server_port = getEnvVar("SERVER_PORT");

    if (server_ip == "" || server_port == "") {
        if (server_ip == "") {
            LOG(ERROR) << "SERVER_IP environment variable not set";
        }
        if (server_port == "") {
            LOG(ERROR) << "SERVER_PORT environment variable not set";
        }
        return 1;

    }
    std::string grpc_server = server_ip + ":" + server_port;

    LOG(INFO) << "Connecting IOS-XR to gRPC server at " << grpc_server;

    AsyncNotifChannel asynchandler(grpc::CreateChannel(
                              grpc_server, grpc::InsecureChannelCredentials()));

    // Acquire the lock
    std::unique_lock<std::mutex> initlock(init_mutex);

    // Spawn reader thread that maintains our Notification Channel
    std::thread thread_ = std::thread(&AsyncNotifChannel::AsyncCompleteRpc, &asynchandler);


    service_layer::SLInitMsg init_msg;
    init_msg.set_majorver(service_layer::SL_MAJOR_VERSION);
    init_msg.set_minorver(service_layer::SL_MINOR_VERSION);
    init_msg.set_subver(service_layer::SL_SUB_VERSION);


    asynchandler.SendInitMsg(init_msg);  

    // Wait on the mutex lock
    while (!init_success) {
        init_condVar.wait(initlock);
    }

    // Set up a new channel for vrf/route messages

    SLVrf vrfhandler(grpc::CreateChannel(
                              grpc_server, grpc::InsecureChannelCredentials()));

    // Create a new SLVrfRegMsg batch
    vrfhandler.vrfRegMsgAdd("default", 10, 500);

    // Register the SLVrfRegMsg batch for v4 and v6
    vrfhandler.registerVrf(AF_INET);
    vrfhandler.registerVrf(AF_INET6);

   
    // Create a route shuttle object to hold route batches
    auto rshuttle = RShuttle(vrfhandler.channel);

    // Insert routes - prefix, prefixlen, admindistance, nexthopaddress, nexthopif one by one
    rshuttle.insertAddBatchV4("default", "20.0.1.0", 24, 120, "14.1.1.10","GigabitEthernet0/0/0/0");
    rshuttle.insertAddBatchV4("default", "20.0.1.0", 24, 120, "15.1.1.10","GigabitEthernet0/0/0/1");
    rshuttle.insertAddBatchV4("default", "23.0.1.0", 24, 120, "14.1.1.10","GigabitEthernet0/0/0/0");
    rshuttle.insertAddBatchV4("default", "23.0.1.0", 24, 120, "15.1.1.10","GigabitEthernet0/0/0/1");
    rshuttle.insertAddBatchV4("default", "30.0.1.0", 24, 120, "14.1.1.10","GigabitEthernet0/0/0/0");

    // Push route batch into the IOS-XR RIB
    rshuttle.routev4Op(service_layer::SL_OBJOP_UPDATE);

    // Clear the batch before the next operation
    rshuttle.clearBatchV4();

    rshuttle.prefixInAppRibV4("default", "31.0.1.0", 24);


    // Create a v6 route batch, same principle as v4
    rshuttle.insertAddBatchV6("default", "2002:aa::0", 64, 120, "2002:ae::3", "GigabitEthernet0/0/0/0");
    rshuttle.insertAddBatchV6("default", "2003:aa::0", 64, 120, "2002:ae::4", "GigabitEthernet0/0/0/1");

    // Push route batch into the IOS-XR RIB
    rshuttle.routev6Op(service_layer::SL_OBJOP_ADD);

    // Clear the batch before the next operation
    rshuttle.clearBatchV6();


    // Let's create a delete route batch for v4 
    rshuttle.insertDeleteBatchV4("default", "20.0.1.0", 24);
    rshuttle.insertDeleteBatchV4("default", "23.0.1.0", 24); 

    // Push route batch into the IOS-XR RIB
    rshuttle.routev4Op(service_layer::SL_OBJOP_DELETE);

    // Clear the batch before the next operation
    rshuttle.clearBatchV4();


    vrfhandler_signum = &vrfhandler;
    asynchandler_signum = &asynchandler;

    signal(SIGINT, signalHandler);  
    LOG(INFO) << "Press control-c to quit";
    thread_.join();

    return 0;
}
