// Generated by the gRPC protobuf plugin.
// If you make any local change, they will be lost.
// source: sl_bfd_ipv4.proto
#ifndef GRPC_sl_5fbfd_5fipv4_2eproto__INCLUDED
#define GRPC_sl_5fbfd_5fipv4_2eproto__INCLUDED

#include "sl_bfd_ipv4.pb.h"

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

class SLBfdv4Oper GRPC_FINAL {
 public:
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status SLBfdv4RegOp(::grpc::ClientContext* context, const ::service_layer::SLBfdRegMsg& request, ::service_layer::SLBfdRegMsgRsp* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLBfdRegMsgRsp>> AsyncSLBfdv4RegOp(::grpc::ClientContext* context, const ::service_layer::SLBfdRegMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLBfdRegMsgRsp>>(AsyncSLBfdv4RegOpRaw(context, request, cq));
    }
    virtual ::grpc::Status SLBfdv4Get(::grpc::ClientContext* context, const ::service_layer::SLBfdGetMsg& request, ::service_layer::SLBfdGetMsgRsp* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLBfdGetMsgRsp>> AsyncSLBfdv4Get(::grpc::ClientContext* context, const ::service_layer::SLBfdGetMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLBfdGetMsgRsp>>(AsyncSLBfdv4GetRaw(context, request, cq));
    }
    virtual ::grpc::Status SLBfdv4GetStats(::grpc::ClientContext* context, const ::service_layer::SLBfdGetMsg& request, ::service_layer::SLBfdGetStatsMsgRsp* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLBfdGetStatsMsgRsp>> AsyncSLBfdv4GetStats(::grpc::ClientContext* context, const ::service_layer::SLBfdGetMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLBfdGetStatsMsgRsp>>(AsyncSLBfdv4GetStatsRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientReaderInterface< ::service_layer::SLBfdv4Notif>> SLBfdv4GetNotifStream(::grpc::ClientContext* context, const ::service_layer::SLBfdGetNotifMsg& request) {
      return std::unique_ptr< ::grpc::ClientReaderInterface< ::service_layer::SLBfdv4Notif>>(SLBfdv4GetNotifStreamRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::service_layer::SLBfdv4Notif>> AsyncSLBfdv4GetNotifStream(::grpc::ClientContext* context, const ::service_layer::SLBfdGetNotifMsg& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::service_layer::SLBfdv4Notif>>(AsyncSLBfdv4GetNotifStreamRaw(context, request, cq, tag));
    }
    virtual ::grpc::Status SLBfdv4SessionOp(::grpc::ClientContext* context, const ::service_layer::SLBfdv4Msg& request, ::service_layer::SLBfdv4MsgRsp* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLBfdv4MsgRsp>> AsyncSLBfdv4SessionOp(::grpc::ClientContext* context, const ::service_layer::SLBfdv4Msg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLBfdv4MsgRsp>>(AsyncSLBfdv4SessionOpRaw(context, request, cq));
    }
    virtual ::grpc::Status SLBfdv4SessionGet(::grpc::ClientContext* context, const ::service_layer::SLBfdv4GetMsg& request, ::service_layer::SLBfdv4GetMsgRsp* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLBfdv4GetMsgRsp>> AsyncSLBfdv4SessionGet(::grpc::ClientContext* context, const ::service_layer::SLBfdv4GetMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLBfdv4GetMsgRsp>>(AsyncSLBfdv4SessionGetRaw(context, request, cq));
    }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLBfdRegMsgRsp>* AsyncSLBfdv4RegOpRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdRegMsg& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLBfdGetMsgRsp>* AsyncSLBfdv4GetRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdGetMsg& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLBfdGetStatsMsgRsp>* AsyncSLBfdv4GetStatsRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdGetMsg& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientReaderInterface< ::service_layer::SLBfdv4Notif>* SLBfdv4GetNotifStreamRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdGetNotifMsg& request) = 0;
    virtual ::grpc::ClientAsyncReaderInterface< ::service_layer::SLBfdv4Notif>* AsyncSLBfdv4GetNotifStreamRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdGetNotifMsg& request, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLBfdv4MsgRsp>* AsyncSLBfdv4SessionOpRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdv4Msg& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::service_layer::SLBfdv4GetMsgRsp>* AsyncSLBfdv4SessionGetRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdv4GetMsg& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub GRPC_FINAL : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status SLBfdv4RegOp(::grpc::ClientContext* context, const ::service_layer::SLBfdRegMsg& request, ::service_layer::SLBfdRegMsgRsp* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdRegMsgRsp>> AsyncSLBfdv4RegOp(::grpc::ClientContext* context, const ::service_layer::SLBfdRegMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdRegMsgRsp>>(AsyncSLBfdv4RegOpRaw(context, request, cq));
    }
    ::grpc::Status SLBfdv4Get(::grpc::ClientContext* context, const ::service_layer::SLBfdGetMsg& request, ::service_layer::SLBfdGetMsgRsp* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdGetMsgRsp>> AsyncSLBfdv4Get(::grpc::ClientContext* context, const ::service_layer::SLBfdGetMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdGetMsgRsp>>(AsyncSLBfdv4GetRaw(context, request, cq));
    }
    ::grpc::Status SLBfdv4GetStats(::grpc::ClientContext* context, const ::service_layer::SLBfdGetMsg& request, ::service_layer::SLBfdGetStatsMsgRsp* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdGetStatsMsgRsp>> AsyncSLBfdv4GetStats(::grpc::ClientContext* context, const ::service_layer::SLBfdGetMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdGetStatsMsgRsp>>(AsyncSLBfdv4GetStatsRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientReader< ::service_layer::SLBfdv4Notif>> SLBfdv4GetNotifStream(::grpc::ClientContext* context, const ::service_layer::SLBfdGetNotifMsg& request) {
      return std::unique_ptr< ::grpc::ClientReader< ::service_layer::SLBfdv4Notif>>(SLBfdv4GetNotifStreamRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReader< ::service_layer::SLBfdv4Notif>> AsyncSLBfdv4GetNotifStream(::grpc::ClientContext* context, const ::service_layer::SLBfdGetNotifMsg& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReader< ::service_layer::SLBfdv4Notif>>(AsyncSLBfdv4GetNotifStreamRaw(context, request, cq, tag));
    }
    ::grpc::Status SLBfdv4SessionOp(::grpc::ClientContext* context, const ::service_layer::SLBfdv4Msg& request, ::service_layer::SLBfdv4MsgRsp* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdv4MsgRsp>> AsyncSLBfdv4SessionOp(::grpc::ClientContext* context, const ::service_layer::SLBfdv4Msg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdv4MsgRsp>>(AsyncSLBfdv4SessionOpRaw(context, request, cq));
    }
    ::grpc::Status SLBfdv4SessionGet(::grpc::ClientContext* context, const ::service_layer::SLBfdv4GetMsg& request, ::service_layer::SLBfdv4GetMsgRsp* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdv4GetMsgRsp>> AsyncSLBfdv4SessionGet(::grpc::ClientContext* context, const ::service_layer::SLBfdv4GetMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdv4GetMsgRsp>>(AsyncSLBfdv4SessionGetRaw(context, request, cq));
    }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdRegMsgRsp>* AsyncSLBfdv4RegOpRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdRegMsg& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdGetMsgRsp>* AsyncSLBfdv4GetRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdGetMsg& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdGetStatsMsgRsp>* AsyncSLBfdv4GetStatsRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdGetMsg& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientReader< ::service_layer::SLBfdv4Notif>* SLBfdv4GetNotifStreamRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdGetNotifMsg& request) GRPC_OVERRIDE;
    ::grpc::ClientAsyncReader< ::service_layer::SLBfdv4Notif>* AsyncSLBfdv4GetNotifStreamRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdGetNotifMsg& request, ::grpc::CompletionQueue* cq, void* tag) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdv4MsgRsp>* AsyncSLBfdv4SessionOpRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdv4Msg& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdv4GetMsgRsp>* AsyncSLBfdv4SessionGetRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdv4GetMsg& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    const ::grpc::RpcMethod rpcmethod_SLBfdv4RegOp_;
    const ::grpc::RpcMethod rpcmethod_SLBfdv4Get_;
    const ::grpc::RpcMethod rpcmethod_SLBfdv4GetStats_;
    const ::grpc::RpcMethod rpcmethod_SLBfdv4GetNotifStream_;
    const ::grpc::RpcMethod rpcmethod_SLBfdv4SessionOp_;
    const ::grpc::RpcMethod rpcmethod_SLBfdv4SessionGet_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status SLBfdv4RegOp(::grpc::ServerContext* context, const ::service_layer::SLBfdRegMsg* request, ::service_layer::SLBfdRegMsgRsp* response);
    virtual ::grpc::Status SLBfdv4Get(::grpc::ServerContext* context, const ::service_layer::SLBfdGetMsg* request, ::service_layer::SLBfdGetMsgRsp* response);
    virtual ::grpc::Status SLBfdv4GetStats(::grpc::ServerContext* context, const ::service_layer::SLBfdGetMsg* request, ::service_layer::SLBfdGetStatsMsgRsp* response);
    virtual ::grpc::Status SLBfdv4GetNotifStream(::grpc::ServerContext* context, const ::service_layer::SLBfdGetNotifMsg* request, ::grpc::ServerWriter< ::service_layer::SLBfdv4Notif>* writer);
    virtual ::grpc::Status SLBfdv4SessionOp(::grpc::ServerContext* context, const ::service_layer::SLBfdv4Msg* request, ::service_layer::SLBfdv4MsgRsp* response);
    virtual ::grpc::Status SLBfdv4SessionGet(::grpc::ServerContext* context, const ::service_layer::SLBfdv4GetMsg* request, ::service_layer::SLBfdv4GetMsgRsp* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_SLBfdv4RegOp : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithAsyncMethod_SLBfdv4RegOp() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_SLBfdv4RegOp() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLBfdv4RegOp(::grpc::ServerContext* context, const ::service_layer::SLBfdRegMsg* request, ::service_layer::SLBfdRegMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSLBfdv4RegOp(::grpc::ServerContext* context, ::service_layer::SLBfdRegMsg* request, ::grpc::ServerAsyncResponseWriter< ::service_layer::SLBfdRegMsgRsp>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_SLBfdv4Get : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithAsyncMethod_SLBfdv4Get() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_SLBfdv4Get() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLBfdv4Get(::grpc::ServerContext* context, const ::service_layer::SLBfdGetMsg* request, ::service_layer::SLBfdGetMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSLBfdv4Get(::grpc::ServerContext* context, ::service_layer::SLBfdGetMsg* request, ::grpc::ServerAsyncResponseWriter< ::service_layer::SLBfdGetMsgRsp>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_SLBfdv4GetStats : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithAsyncMethod_SLBfdv4GetStats() {
      ::grpc::Service::MarkMethodAsync(2);
    }
    ~WithAsyncMethod_SLBfdv4GetStats() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLBfdv4GetStats(::grpc::ServerContext* context, const ::service_layer::SLBfdGetMsg* request, ::service_layer::SLBfdGetStatsMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSLBfdv4GetStats(::grpc::ServerContext* context, ::service_layer::SLBfdGetMsg* request, ::grpc::ServerAsyncResponseWriter< ::service_layer::SLBfdGetStatsMsgRsp>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_SLBfdv4GetNotifStream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithAsyncMethod_SLBfdv4GetNotifStream() {
      ::grpc::Service::MarkMethodAsync(3);
    }
    ~WithAsyncMethod_SLBfdv4GetNotifStream() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLBfdv4GetNotifStream(::grpc::ServerContext* context, const ::service_layer::SLBfdGetNotifMsg* request, ::grpc::ServerWriter< ::service_layer::SLBfdv4Notif>* writer) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSLBfdv4GetNotifStream(::grpc::ServerContext* context, ::service_layer::SLBfdGetNotifMsg* request, ::grpc::ServerAsyncWriter< ::service_layer::SLBfdv4Notif>* writer, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncServerStreaming(3, context, request, writer, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_SLBfdv4SessionOp : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithAsyncMethod_SLBfdv4SessionOp() {
      ::grpc::Service::MarkMethodAsync(4);
    }
    ~WithAsyncMethod_SLBfdv4SessionOp() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLBfdv4SessionOp(::grpc::ServerContext* context, const ::service_layer::SLBfdv4Msg* request, ::service_layer::SLBfdv4MsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSLBfdv4SessionOp(::grpc::ServerContext* context, ::service_layer::SLBfdv4Msg* request, ::grpc::ServerAsyncResponseWriter< ::service_layer::SLBfdv4MsgRsp>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(4, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_SLBfdv4SessionGet : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithAsyncMethod_SLBfdv4SessionGet() {
      ::grpc::Service::MarkMethodAsync(5);
    }
    ~WithAsyncMethod_SLBfdv4SessionGet() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLBfdv4SessionGet(::grpc::ServerContext* context, const ::service_layer::SLBfdv4GetMsg* request, ::service_layer::SLBfdv4GetMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSLBfdv4SessionGet(::grpc::ServerContext* context, ::service_layer::SLBfdv4GetMsg* request, ::grpc::ServerAsyncResponseWriter< ::service_layer::SLBfdv4GetMsgRsp>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(5, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_SLBfdv4RegOp<WithAsyncMethod_SLBfdv4Get<WithAsyncMethod_SLBfdv4GetStats<WithAsyncMethod_SLBfdv4GetNotifStream<WithAsyncMethod_SLBfdv4SessionOp<WithAsyncMethod_SLBfdv4SessionGet<Service > > > > > > AsyncService;
  template <class BaseClass>
  class WithGenericMethod_SLBfdv4RegOp : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithGenericMethod_SLBfdv4RegOp() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_SLBfdv4RegOp() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLBfdv4RegOp(::grpc::ServerContext* context, const ::service_layer::SLBfdRegMsg* request, ::service_layer::SLBfdRegMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_SLBfdv4Get : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithGenericMethod_SLBfdv4Get() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_SLBfdv4Get() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLBfdv4Get(::grpc::ServerContext* context, const ::service_layer::SLBfdGetMsg* request, ::service_layer::SLBfdGetMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_SLBfdv4GetStats : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithGenericMethod_SLBfdv4GetStats() {
      ::grpc::Service::MarkMethodGeneric(2);
    }
    ~WithGenericMethod_SLBfdv4GetStats() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLBfdv4GetStats(::grpc::ServerContext* context, const ::service_layer::SLBfdGetMsg* request, ::service_layer::SLBfdGetStatsMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_SLBfdv4GetNotifStream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithGenericMethod_SLBfdv4GetNotifStream() {
      ::grpc::Service::MarkMethodGeneric(3);
    }
    ~WithGenericMethod_SLBfdv4GetNotifStream() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLBfdv4GetNotifStream(::grpc::ServerContext* context, const ::service_layer::SLBfdGetNotifMsg* request, ::grpc::ServerWriter< ::service_layer::SLBfdv4Notif>* writer) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_SLBfdv4SessionOp : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithGenericMethod_SLBfdv4SessionOp() {
      ::grpc::Service::MarkMethodGeneric(4);
    }
    ~WithGenericMethod_SLBfdv4SessionOp() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLBfdv4SessionOp(::grpc::ServerContext* context, const ::service_layer::SLBfdv4Msg* request, ::service_layer::SLBfdv4MsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_SLBfdv4SessionGet : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(Service *service) {}
   public:
    WithGenericMethod_SLBfdv4SessionGet() {
      ::grpc::Service::MarkMethodGeneric(5);
    }
    ~WithGenericMethod_SLBfdv4SessionGet() GRPC_OVERRIDE {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SLBfdv4SessionGet(::grpc::ServerContext* context, const ::service_layer::SLBfdv4GetMsg* request, ::service_layer::SLBfdv4GetMsgRsp* response) GRPC_FINAL GRPC_OVERRIDE {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
};

}  // namespace service_layer


#endif  // GRPC_sl_5fbfd_5fipv4_2eproto__INCLUDED
