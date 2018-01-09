// Generated by the gRPC protobuf plugin.
// If you make any local change, they will be lost.
// source: sl_interface.proto
#ifndef GRPC_sl_5finterface_2eproto__INCLUDED
#define GRPC_sl_5finterface_2eproto__INCLUDED

#include "sl_interface.pb.h"

#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/impl/codegen/async_unary_call.h>
#include <grpc++/impl/codegen/proto_utils.h>
#include <grpc++/impl/codegen/rpc_method.h>
#include <grpc++/impl/codegen/service_type.h>
#include <grpc++/impl/codegen/status.h>
#include <grpc++/impl/codegen/stub_options.h>
#include <grpc++/impl/codegen/sync_stream.h>

namespace grpc {
class CompletionQueue;
class RpcService;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace service_layer {

class SLInterfaceOper GRPC_FINAL {
 public:
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status SLInterfaceGlobalsRegOp(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsRegMsg& request, ::service_layer::SLInterfaceGlobalsRegMsgRsp* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLInterfaceGlobalsRegMsgRsp>> AsyncSLInterfaceGlobalsRegOp(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsRegMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLInterfaceGlobalsRegMsgRsp>>(AsyncSLInterfaceGlobalsRegOpRaw(context, request, cq));
    }
    virtual ::grpc::Status SLInterfaceGlobalsGet(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg& request, ::service_layer::SLInterfaceGlobalsGetMsgRsp* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLInterfaceGlobalsGetMsgRsp>> AsyncSLInterfaceGlobalsGet(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLInterfaceGlobalsGetMsgRsp>>(AsyncSLInterfaceGlobalsGetRaw(context, request, cq));
    }
    virtual ::grpc::Status SLInterfaceGlobalsGetStats(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg& request, ::service_layer::SLInterfaceGlobalsGetStatsMsgRsp* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLInterfaceGlobalsGetStatsMsgRsp>> AsyncSLInterfaceGlobalsGetStats(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLInterfaceGlobalsGetStatsMsgRsp>>(AsyncSLInterfaceGlobalsGetStatsRaw(context, request, cq));
    }
    virtual ::grpc::Status SLInterfaceGet(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGetMsg& request, ::service_layer::SLInterfaceGetMsgRsp* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLInterfaceGetMsgRsp>> AsyncSLInterfaceGet(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGetMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLInterfaceGetMsgRsp>>(AsyncSLInterfaceGetRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientReaderInterface< ::service_layer::SLInterfaceNotif>> SLInterfaceGetNotifStream(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGetNotifMsg& request) {
      return std::unique_ptr< ::grpc::ClientReaderInterface< ::service_layer::SLInterfaceNotif>>(SLInterfaceGetNotifStreamRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::service_layer::SLInterfaceNotif>> AsyncSLInterfaceGetNotifStream(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGetNotifMsg& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::service_layer::SLInterfaceNotif>>(AsyncSLInterfaceGetNotifStreamRaw(context, request, cq, tag));
    }
    virtual ::grpc::Status SLInterfaceNotifOp(::grpc::ClientContext* context, const ::service_layer::SLInterfaceNotifMsg& request, ::service_layer::SLInterfaceNotifMsgRsp* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLInterfaceNotifMsgRsp>> AsyncSLInterfaceNotifOp(::grpc::ClientContext* context, const ::service_layer::SLInterfaceNotifMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLInterfaceNotifMsgRsp>>(AsyncSLInterfaceNotifOpRaw(context, request, cq));
    }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLInterfaceGlobalsRegMsgRsp>* AsyncSLInterfaceGlobalsRegOpRaw(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsRegMsg& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLInterfaceGlobalsGetMsgRsp>* AsyncSLInterfaceGlobalsGetRaw(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLInterfaceGlobalsGetStatsMsgRsp>* AsyncSLInterfaceGlobalsGetStatsRaw(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLInterfaceGetMsgRsp>* AsyncSLInterfaceGetRaw(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGetMsg& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientReaderInterface< ::service_layer::SLInterfaceNotif>* SLInterfaceGetNotifStreamRaw(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGetNotifMsg& request) = 0;
    virtual ::grpc::ClientAsyncReaderInterface< ::service_layer::SLInterfaceNotif>* AsyncSLInterfaceGetNotifStreamRaw(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGetNotifMsg& request, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLInterfaceNotifMsgRsp>* AsyncSLInterfaceNotifOpRaw(::grpc::ClientContext* context, const ::service_layer::SLInterfaceNotifMsg& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub GRPC_FINAL : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status SLInterfaceGlobalsRegOp(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsRegMsg& request, ::service_layer::SLInterfaceGlobalsRegMsgRsp* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLInterfaceGlobalsRegMsgRsp>> AsyncSLInterfaceGlobalsRegOp(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsRegMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLInterfaceGlobalsRegMsgRsp>>(AsyncSLInterfaceGlobalsRegOpRaw(context, request, cq));
    }
    ::grpc::Status SLInterfaceGlobalsGet(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg& request, ::service_layer::SLInterfaceGlobalsGetMsgRsp* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLInterfaceGlobalsGetMsgRsp>> AsyncSLInterfaceGlobalsGet(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLInterfaceGlobalsGetMsgRsp>>(AsyncSLInterfaceGlobalsGetRaw(context, request, cq));
    }
    ::grpc::Status SLInterfaceGlobalsGetStats(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg& request, ::service_layer::SLInterfaceGlobalsGetStatsMsgRsp* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLInterfaceGlobalsGetStatsMsgRsp>> AsyncSLInterfaceGlobalsGetStats(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLInterfaceGlobalsGetStatsMsgRsp>>(AsyncSLInterfaceGlobalsGetStatsRaw(context, request, cq));
    }
    ::grpc::Status SLInterfaceGet(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGetMsg& request, ::service_layer::SLInterfaceGetMsgRsp* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLInterfaceGetMsgRsp>> AsyncSLInterfaceGet(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGetMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLInterfaceGetMsgRsp>>(AsyncSLInterfaceGetRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientReader< ::service_layer::SLInterfaceNotif>> SLInterfaceGetNotifStream(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGetNotifMsg& request) {
      return std::unique_ptr< ::grpc::ClientReader< ::service_layer::SLInterfaceNotif>>(SLInterfaceGetNotifStreamRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReader< ::service_layer::SLInterfaceNotif>> AsyncSLInterfaceGetNotifStream(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGetNotifMsg& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReader< ::service_layer::SLInterfaceNotif>>(AsyncSLInterfaceGetNotifStreamRaw(context, request, cq, tag));
    }
    ::grpc::Status SLInterfaceNotifOp(::grpc::ClientContext* context, const ::service_layer::SLInterfaceNotifMsg& request, ::service_layer::SLInterfaceNotifMsgRsp* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLInterfaceNotifMsgRsp>> AsyncSLInterfaceNotifOp(::grpc::ClientContext* context, const ::service_layer::SLInterfaceNotifMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLInterfaceNotifMsgRsp>>(AsyncSLInterfaceNotifOpRaw(context, request, cq));
    }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    ::grpc::ClientAsyncResponseReader< ::service_layer::SLInterfaceGlobalsRegMsgRsp>* AsyncSLInterfaceGlobalsRegOpRaw(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsRegMsg& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::service_layer::SLInterfaceGlobalsGetMsgRsp>* AsyncSLInterfaceGlobalsGetRaw(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::service_layer::SLInterfaceGlobalsGetStatsMsgRsp>* AsyncSLInterfaceGlobalsGetStatsRaw(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::service_layer::SLInterfaceGetMsgRsp>* AsyncSLInterfaceGetRaw(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGetMsg& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientReader< ::service_layer::SLInterfaceNotif>* SLInterfaceGetNotifStreamRaw(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGetNotifMsg& request) GRPC_OVERRIDE;
    ::grpc::ClientAsyncReader< ::service_layer::SLInterfaceNotif>* AsyncSLInterfaceGetNotifStreamRaw(::grpc::ClientContext* context, const ::service_layer::SLInterfaceGetNotifMsg& request, ::grpc::CompletionQueue* cq, void* tag) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::service_layer::SLInterfaceNotifMsgRsp>* AsyncSLInterfaceNotifOpRaw(::grpc::ClientContext* context, const ::service_layer::SLInterfaceNotifMsg& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    const ::grpc::RpcMethod rpcmethod_SLInterfaceGlobalsRegOp_;
    const ::grpc::RpcMethod rpcmethod_SLInterfaceGlobalsGet_;
    const ::grpc::RpcMethod rpcmethod_SLInterfaceGlobalsGetStats_;
    const ::grpc::RpcMethod rpcmethod_SLInterfaceGet_;
    const ::grpc::RpcMethod rpcmethod_SLInterfaceGetNotifStream_;
    const ::grpc::RpcMethod rpcmethod_SLInterfaceNotifOp_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status SLInterfaceGlobalsRegOp(::grpc::ServerContext* context, const ::service_layer::SLInterfaceGlobalsRegMsg* request, ::service_layer::SLInterfaceGlobalsRegMsgRsp* response);
    virtual ::grpc::Status SLInterfaceGlobalsGet(::grpc::ServerContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg* request, ::service_layer::SLInterfaceGlobalsGetMsgRsp* response);
    virtual ::grpc::Status SLInterfaceGlobalsGetStats(::grpc::ServerContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg* request, ::service_layer::SLInterfaceGlobalsGetStatsMsgRsp* response);
    virtual ::grpc::Status SLInterfaceGet(::grpc::ServerContext* context, const ::service_layer::SLInterfaceGetMsg* request, ::service_layer::SLInterfaceGetMsgRsp* response);
    virtual ::grpc::Status SLInterfaceGetNotifStream(::grpc::ServerContext* context, const ::service_layer::SLInterfaceGetNotifMsg* request, ::grpc::ServerWriter< ::service_layer::SLInterfaceNotif>* writer);
    virtual ::grpc::Status SLInterfaceNotifOp(::grpc::ServerContext* context, const ::service_layer::SLInterfaceNotifMsg* request, ::service_layer::SLInterfaceNotifMsgRsp* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_SLInterfaceGlobalsRegOp : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithAsyncMethod_SLInterfaceGlobalsRegOp() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_SLInterfaceGlobalsRegOp() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLInterfaceGlobalsRegOp(::grpc::ServerContext* context, const ::service_layer::SLInterfaceGlobalsRegMsg* request, ::service_layer::SLInterfaceGlobalsRegMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSLInterfaceGlobalsRegOp(::grpc::ServerContext* context, ::service_layer::SLInterfaceGlobalsRegMsg* request, ::grpc::ServerAsyncResponseWriter< ::service_layer::SLInterfaceGlobalsRegMsgRsp>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_SLInterfaceGlobalsGet : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithAsyncMethod_SLInterfaceGlobalsGet() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_SLInterfaceGlobalsGet() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLInterfaceGlobalsGet(::grpc::ServerContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg* request, ::service_layer::SLInterfaceGlobalsGetMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSLInterfaceGlobalsGet(::grpc::ServerContext* context, ::service_layer::SLInterfaceGlobalsGetMsg* request, ::grpc::ServerAsyncResponseWriter< ::service_layer::SLInterfaceGlobalsGetMsgRsp>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_SLInterfaceGlobalsGetStats : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithAsyncMethod_SLInterfaceGlobalsGetStats() {
      ::grpc::Service::MarkMethodAsync(2);
    }
    ~WithAsyncMethod_SLInterfaceGlobalsGetStats() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLInterfaceGlobalsGetStats(::grpc::ServerContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg* request, ::service_layer::SLInterfaceGlobalsGetStatsMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSLInterfaceGlobalsGetStats(::grpc::ServerContext* context, ::service_layer::SLInterfaceGlobalsGetMsg* request, ::grpc::ServerAsyncResponseWriter< ::service_layer::SLInterfaceGlobalsGetStatsMsgRsp>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_SLInterfaceGet : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithAsyncMethod_SLInterfaceGet() {
      ::grpc::Service::MarkMethodAsync(3);
    }
    ~WithAsyncMethod_SLInterfaceGet() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLInterfaceGet(::grpc::ServerContext* context, const ::service_layer::SLInterfaceGetMsg* request, ::service_layer::SLInterfaceGetMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSLInterfaceGet(::grpc::ServerContext* context, ::service_layer::SLInterfaceGetMsg* request, ::grpc::ServerAsyncResponseWriter< ::service_layer::SLInterfaceGetMsgRsp>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(3, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_SLInterfaceGetNotifStream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithAsyncMethod_SLInterfaceGetNotifStream() {
      ::grpc::Service::MarkMethodAsync(4);
    }
    ~WithAsyncMethod_SLInterfaceGetNotifStream() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLInterfaceGetNotifStream(::grpc::ServerContext* context, const ::service_layer::SLInterfaceGetNotifMsg* request, ::grpc::ServerWriter< ::service_layer::SLInterfaceNotif>* writer) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSLInterfaceGetNotifStream(::grpc::ServerContext* context, ::service_layer::SLInterfaceGetNotifMsg* request, ::grpc::ServerAsyncWriter< ::service_layer::SLInterfaceNotif>* writer, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncServerStreaming(4, context, request, writer, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_SLInterfaceNotifOp : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithAsyncMethod_SLInterfaceNotifOp() {
      ::grpc::Service::MarkMethodAsync(5);
    }
    ~WithAsyncMethod_SLInterfaceNotifOp() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLInterfaceNotifOp(::grpc::ServerContext* context, const ::service_layer::SLInterfaceNotifMsg* request, ::service_layer::SLInterfaceNotifMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSLInterfaceNotifOp(::grpc::ServerContext* context, ::service_layer::SLInterfaceNotifMsg* request, ::grpc::ServerAsyncResponseWriter< ::service_layer::SLInterfaceNotifMsgRsp>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(5, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_SLInterfaceGlobalsRegOp<WithAsyncMethod_SLInterfaceGlobalsGet<WithAsyncMethod_SLInterfaceGlobalsGetStats<WithAsyncMethod_SLInterfaceGet<WithAsyncMethod_SLInterfaceGetNotifStream<WithAsyncMethod_SLInterfaceNotifOp<Service > > > > > > AsyncService;
  template <class BaseClass>
  class WithGenericMethod_SLInterfaceGlobalsRegOp : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithGenericMethod_SLInterfaceGlobalsRegOp() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_SLInterfaceGlobalsRegOp() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLInterfaceGlobalsRegOp(::grpc::ServerContext* context, const ::service_layer::SLInterfaceGlobalsRegMsg* request, ::service_layer::SLInterfaceGlobalsRegMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_SLInterfaceGlobalsGet : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithGenericMethod_SLInterfaceGlobalsGet() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_SLInterfaceGlobalsGet() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLInterfaceGlobalsGet(::grpc::ServerContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg* request, ::service_layer::SLInterfaceGlobalsGetMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_SLInterfaceGlobalsGetStats : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithGenericMethod_SLInterfaceGlobalsGetStats() {
      ::grpc::Service::MarkMethodGeneric(2);
    }
    ~WithGenericMethod_SLInterfaceGlobalsGetStats() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLInterfaceGlobalsGetStats(::grpc::ServerContext* context, const ::service_layer::SLInterfaceGlobalsGetMsg* request, ::service_layer::SLInterfaceGlobalsGetStatsMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_SLInterfaceGet : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithGenericMethod_SLInterfaceGet() {
      ::grpc::Service::MarkMethodGeneric(3);
    }
    ~WithGenericMethod_SLInterfaceGet() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLInterfaceGet(::grpc::ServerContext* context, const ::service_layer::SLInterfaceGetMsg* request, ::service_layer::SLInterfaceGetMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_SLInterfaceGetNotifStream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithGenericMethod_SLInterfaceGetNotifStream() {
      ::grpc::Service::MarkMethodGeneric(4);
    }
    ~WithGenericMethod_SLInterfaceGetNotifStream() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLInterfaceGetNotifStream(::grpc::ServerContext* context, const ::service_layer::SLInterfaceGetNotifMsg* request, ::grpc::ServerWriter< ::service_layer::SLInterfaceNotif>* writer) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_SLInterfaceNotifOp : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithGenericMethod_SLInterfaceNotifOp() {
      ::grpc::Service::MarkMethodGeneric(5);
    }
    ~WithGenericMethod_SLInterfaceNotifOp() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLInterfaceNotifOp(::grpc::ServerContext* context, const ::service_layer::SLInterfaceNotifMsg* request, ::service_layer::SLInterfaceNotifMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
};

}  // namespace service_layer


#endif  // GRPC_sl_5finterface_2eproto__INCLUDED