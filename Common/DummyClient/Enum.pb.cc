// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Enum.proto

#include "Enum.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
#include "google/protobuf/generated_message_tctable_impl.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace Protocol {
}  // namespace Protocol
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_Enum_2eproto[3];
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_Enum_2eproto = nullptr;
const ::uint32_t TableStruct_Enum_2eproto::offsets[1] = {};
static constexpr ::_pbi::MigrationSchema* schemas = nullptr;
static constexpr ::_pb::Message* const* file_default_instances = nullptr;
const char descriptor_table_protodef_Enum_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
    "\n\nEnum.proto\022\010Protocol*h\n\nPlayerType\022\024\n\020"
    "PLAYER_TYPE_NONE\020\000\022\026\n\022PLAYER_TYPE_KNIGHT"
    "\020\001\022\024\n\020PLAYER_TYPE_MAGE\020\002\022\026\n\022PLAYER_TYPE_"
    "ARCHER\020\003*@\n\tBaseState\022\010\n\004IDLE\020\000\022\n\n\006MOVIN"
    "G\020\001\022\t\n\005SKILL\020\002\022\010\n\004DEAD\020\003\022\010\n\004JUMP\020\004*\036\n\007Mo"
    "veDir\022\010\n\004LEFT\020\000\022\t\n\005RIGHT\020\001B\036\370\001\001\252\002\030Google"
    ".Protobuf.Protocolb\006proto3"
};
static ::absl::once_flag descriptor_table_Enum_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_Enum_2eproto = {
    false,
    false,
    266,
    descriptor_table_protodef_Enum_2eproto,
    "Enum.proto",
    &descriptor_table_Enum_2eproto_once,
    nullptr,
    0,
    0,
    schemas,
    file_default_instances,
    TableStruct_Enum_2eproto::offsets,
    nullptr,
    file_level_enum_descriptors_Enum_2eproto,
    file_level_service_descriptors_Enum_2eproto,
};

// This function exists to be marked as weak.
// It can significantly speed up compilation by breaking up LLVM's SCC
// in the .pb.cc translation units. Large translation units see a
// reduction of more than 35% of walltime for optimized builds. Without
// the weak attribute all the messages in the file, including all the
// vtables and everything they use become part of the same SCC through
// a cycle like:
// GetMetadata -> descriptor table -> default instances ->
//   vtables -> GetMetadata
// By adding a weak function here we break the connection from the
// individual vtables back into the descriptor table.
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_Enum_2eproto_getter() {
  return &descriptor_table_Enum_2eproto;
}
// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_Enum_2eproto(&descriptor_table_Enum_2eproto);
namespace Protocol {
const ::google::protobuf::EnumDescriptor* PlayerType_descriptor() {
  ::google::protobuf::internal::AssignDescriptors(&descriptor_table_Enum_2eproto);
  return file_level_enum_descriptors_Enum_2eproto[0];
}
PROTOBUF_CONSTINIT const uint32_t PlayerType_internal_data_[] = {
    262144u, 0u, };
bool PlayerType_IsValid(int value) {
  return 0 <= value && value <= 3;
}
const ::google::protobuf::EnumDescriptor* BaseState_descriptor() {
  ::google::protobuf::internal::AssignDescriptors(&descriptor_table_Enum_2eproto);
  return file_level_enum_descriptors_Enum_2eproto[1];
}
PROTOBUF_CONSTINIT const uint32_t BaseState_internal_data_[] = {
    327680u, 0u, };
bool BaseState_IsValid(int value) {
  return 0 <= value && value <= 4;
}
const ::google::protobuf::EnumDescriptor* MoveDir_descriptor() {
  ::google::protobuf::internal::AssignDescriptors(&descriptor_table_Enum_2eproto);
  return file_level_enum_descriptors_Enum_2eproto[2];
}
PROTOBUF_CONSTINIT const uint32_t MoveDir_internal_data_[] = {
    131072u, 0u, };
bool MoveDir_IsValid(int value) {
  return 0 <= value && value <= 1;
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace Protocol
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"
