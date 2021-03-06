// Generated by the gRPC protobuf plugin.
// If you make any local change, they will be lost.
// source: sl_bfd_ipv4.proto

#include "sl_bfd_ipv4.pb.h"
#include "sl_bfd_ipv4.grpc.pb.h"

#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/impl/codegen/async_unary_call.h>
#include <grpc++/impl/codegen/channel_interface.h>
#include <grpc++/impl/codegen/client_unary_call.h>
#include <grpc++/impl/codegen/method_handler_impl.h>
#include <grpc++/impl/codegen/rpc_service_method.h>
#include <grpc++/impl/codegen/service_type.h>
#include <grpc++/impl/codegen/sync_stream.h>
namespace service_layer {

static const char* SLBfdv4Oper_method_names[] = {
  "/service_layer.SLBfdv4Oper/SLBfdv4RegOp",
  "/service_layer.SLBfdv4Oper/SLBfdv4Get",
  "/service_layer.SLBfdv4Oper/SLBfdv4GetStats",
  "/service_layer.SLBfdv4Oper/SLBfdv4GetNotifStream",
  "/service_layer.SLBfdv4Oper/SLBfdv4SessionOp",
  "/service_layer.SLBfdv4Oper/SLBfdv4SessionGet",
};

std::unique_ptr< SLBfdv4Oper::Stub> SLBfdv4Oper::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  std::unique_ptr< SLBfdv4Oper::Stub> stub(new SLBfdv4Oper::Stub(channel));
  return stub;
}

SLBfdv4Oper::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_SLBfdv4RegOp_(SLBfdv4Oper_method_names[0], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_SLBfdv4Get_(SLBfdv4Oper_method_names[1], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_SLBfdv4GetStats_(SLBfdv4Oper_method_names[2], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_SLBfdv4GetNotifStream_(SLBfdv4Oper_method_names[3], ::grpc::RpcMethod::SERVER_STREAMING, channel)
  , rpcmethod_SLBfdv4SessionOp_(SLBfdv4Oper_method_names[4], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_SLBfdv4SessionGet_(SLBfdv4Oper_method_names[5], ::grpc::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status SLBfdv4Oper::Stub::SLBfdv4RegOp(::grpc::ClientContext* context, const ::service_layer::SLBfdRegMsg& request, ::service_layer::SLBfdRegMsgRsp* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_SLBfdv4RegOp_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdRegMsgRsp>* SLBfdv4Oper::Stub::AsyncSLBfdv4RegOpRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdRegMsg& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdRegMsgRsp>(channel_.get(), cq, rpcmethod_SLBfdv4RegOp_, context, request);
}

::grpc::Status SLBfdv4Oper::Stub::SLBfdv4Get(::grpc::ClientContext* context, const ::service_layer::SLBfdGetMsg& request, ::service_layer::SLBfdGetMsgRsp* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_SLBfdv4Get_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdGetMsgRsp>* SLBfdv4Oper::Stub::AsyncSLBfdv4GetRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdGetMsg& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdGetMsgRsp>(channel_.get(), cq, rpcmethod_SLBfdv4Get_, context, request);
}

::grpc::Status SLBfdv4Oper::Stub::SLBfdv4GetStats(::grpc::ClientContext* context, const ::service_layer::SLBfdGetMsg& request, ::service_layer::SLBfdGetStatsMsgRsp* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_SLBfdv4GetStats_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdGetStatsMsgRsp>* SLBfdv4Oper::Stub::AsyncSLBfdv4GetStatsRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdGetMsg& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdGetStatsMsgRsp>(channel_.get(), cq, rpcmethod_SLBfdv4GetStats_, context, request);
}

::grpc::ClientReader< ::service_layer::SLBfdv4Notif>* SLBfdv4Oper::Stub::SLBfdv4GetNotifStreamRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdGetNotifMsg& request) {
  return new ::grpc::ClientReader< ::service_layer::SLBfdv4Notif>(channel_.get(), rpcmethod_SLBfdv4GetNotifStream_, context, request);
}

::grpc::ClientAsyncReader< ::service_layer::SLBfdv4Notif>* SLBfdv4Oper::Stub::AsyncSLBfdv4GetNotifStreamRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdGetNotifMsg& request, ::grpc::CompletionQueue* cq, void* tag) {
  return new ::grpc::ClientAsyncReader< ::service_layer::SLBfdv4Notif>(channel_.get(), cq, rpcmethod_SLBfdv4GetNotifStream_, context, request, tag);
}

::grpc::Status SLBfdv4Oper::Stub::SLBfdv4SessionOp(::grpc::ClientContext* context, const ::service_layer::SLBfdv4Msg& request, ::service_layer::SLBfdv4MsgRsp* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_SLBfdv4SessionOp_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdv4MsgRsp>* SLBfdv4Oper::Stub::AsyncSLBfdv4SessionOpRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdv4Msg& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdv4MsgRsp>(channel_.get(), cq, rpcmethod_SLBfdv4SessionOp_, context, request);
}

::grpc::Status SLBfdv4Oper::Stub::SLBfdv4SessionGet(::grpc::ClientContext* context, const ::service_layer::SLBfdv4GetMsg& request, ::service_layer::SLBfdv4GetMsgRsp* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_SLBfdv4SessionGet_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdv4GetMsgRsp>* SLBfdv4Oper::Stub::AsyncSLBfdv4SessionGetRaw(::grpc::ClientContext* context, const ::service_layer::SLBfdv4GetMsg& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::service_layer::SLBfdv4GetMsgRsp>(channel_.get(), cq, rpcmethod_SLBfdv4SessionGet_, context, request);
}

SLBfdv4Oper::Service::Service() {
  (void)SLBfdv4Oper_method_names;
  AddMethod(new ::grpc::RpcServiceMethod(
      SLBfdv4Oper_method_names[0],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< SLBfdv4Oper::Service, ::service_layer::SLBfdRegMsg, ::service_layer::SLBfdRegMsgRsp>(
          std::mem_fn(&SLBfdv4Oper::Service::SLBfdv4RegOp), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      SLBfdv4Oper_method_names[1],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< SLBfdv4Oper::Service, ::service_layer::SLBfdGetMsg, ::service_layer::SLBfdGetMsgRsp>(
          std::mem_fn(&SLBfdv4Oper::Service::SLBfdv4Get), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      SLBfdv4Oper_method_names[2],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< SLBfdv4Oper::Service, ::service_layer::SLBfdGetMsg, ::service_layer::SLBfdGetStatsMsgRsp>(
          std::mem_fn(&SLBfdv4Oper::Service::SLBfdv4GetStats), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      SLBfdv4Oper_method_names[3],
      ::grpc::RpcMethod::SERVER_STREAMING,
      new ::grpc::ServerStreamingHandler< SLBfdv4Oper::Service, ::service_layer::SLBfdGetNotifMsg, ::service_layer::SLBfdv4Notif>(
          std::mem_fn(&SLBfdv4Oper::Service::SLBfdv4GetNotifStream), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      SLBfdv4Oper_method_names[4],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< SLBfdv4Oper::Service, ::service_layer::SLBfdv4Msg, ::service_layer::SLBfdv4MsgRsp>(
          std::mem_fn(&SLBfdv4Oper::Service::SLBfdv4SessionOp), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      SLBfdv4Oper_method_names[5],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< SLBfdv4Oper::Service, ::service_layer::SLBfdv4GetMsg, ::service_layer::SLBfdv4GetMsgRsp>(
          std::mem_fn(&SLBfdv4Oper::Service::SLBfdv4SessionGet), this)));
}

SLBfdv4Oper::Service::~Service() {
}

::grpc::Status SLBfdv4Oper::Service::SLBfdv4RegOp(::grpc::ServerContext* context, const ::service_layer::SLBfdRegMsg* request, ::service_layer::SLBfdRegMsgRsp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status SLBfdv4Oper::Service::SLBfdv4Get(::grpc::ServerContext* context, const ::service_layer::SLBfdGetMsg* request, ::service_layer::SLBfdGetMsgRsp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status SLBfdv4Oper::Service::SLBfdv4GetStats(::grpc::ServerContext* context, const ::service_layer::SLBfdGetMsg* request, ::service_layer::SLBfdGetStatsMsgRsp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status SLBfdv4Oper::Service::SLBfdv4GetNotifStream(::grpc::ServerContext* context, const ::service_layer::SLBfdGetNotifMsg* request, ::grpc::ServerWriter< ::service_layer::SLBfdv4Notif>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status SLBfdv4Oper::Service::SLBfdv4SessionOp(::grpc::ServerContext* context, const ::service_layer::SLBfdv4Msg* request, ::service_layer::SLBfdv4MsgRsp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status SLBfdv4Oper::Service::SLBfdv4SessionGet(::grpc::ServerContext* context, const ::service_layer::SLBfdv4GetMsg* request, ::service_layer::SLBfdv4GetMsgRsp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace service_layer

