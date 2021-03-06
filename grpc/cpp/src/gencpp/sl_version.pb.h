// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: sl_version.proto

#ifndef PROTOBUF_sl_5fversion_2eproto__INCLUDED
#define PROTOBUF_sl_5fversion_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)

namespace protobuf_sl_5fversion_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
inline void InitDefaults() {
}
}  // namespace protobuf_sl_5fversion_2eproto
namespace service_layer {
}  // namespace service_layer
namespace service_layer {

enum SLVersion {
  SL_VERSION_UNUSED = 0,
  SL_MAJOR_VERSION = 0,
  SL_MINOR_VERSION = 0,
  SL_SUB_VERSION = 1,
  SLVersion_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  SLVersion_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool SLVersion_IsValid(int value);
const SLVersion SLVersion_MIN = SL_VERSION_UNUSED;
const SLVersion SLVersion_MAX = SL_SUB_VERSION;
const int SLVersion_ARRAYSIZE = SLVersion_MAX + 1;

const ::google::protobuf::EnumDescriptor* SLVersion_descriptor();
inline const ::std::string& SLVersion_Name(SLVersion value) {
  return ::google::protobuf::internal::NameOfEnum(
    SLVersion_descriptor(), value);
}
inline bool SLVersion_Parse(
    const ::std::string& name, SLVersion* value) {
  return ::google::protobuf::internal::ParseNamedEnum<SLVersion>(
    SLVersion_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace service_layer

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::service_layer::SLVersion> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::service_layer::SLVersion>() {
  return ::service_layer::SLVersion_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_sl_5fversion_2eproto__INCLUDED
