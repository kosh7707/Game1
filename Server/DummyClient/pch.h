#pragma once

#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#ifdef _DEBUG
#pragma comment(lib, "Servercore\\Debug\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#pragma comment(lib, "Abseil\\Debug\\abseil_dll.lib")
#pragma comment(lib, "Abseil\\Debug\\absl_decode_rust_punycode.lib")
#pragma comment(lib, "Abseil\\Debug\\absl_demangle_rust.lib")
#pragma comment(lib, "Abseil\\Debug\\absl_flags_commandlineflag.lib")
#pragma comment(lib, "Abseil\\Debug\\absl_flags_commandlineflag_internal.lib")
#pragma comment(lib, "Abseil\\Debug\\absl_flags_config.lib")
#pragma comment(lib, "Abseil\\Debug\\absl_flags_internal.lib")
#pragma comment(lib, "Abseil\\Debug\\absl_flags_marshalling.lib")
#pragma comment(lib, "Abseil\\Debug\\absl_flags_parse.lib")
#pragma comment(lib, "Abseil\\Debug\\absl_flags_private_handle_accessor.lib")
#pragma comment(lib, "Abseil\\Debug\\absl_flags_program_name.lib")
#pragma comment(lib, "Abseil\\Debug\\absl_flags_reflection.lib")
#pragma comment(lib, "Abseil\\Debug\\absl_flags_usage.lib")
#pragma comment(lib, "Abseil\\Debug\\absl_flags_usage_internal.lib")
#pragma comment(lib, "Abseil\\Debug\\absl_log_flags.lib")
#pragma comment(lib, "Abseil\\Debug\\absl_poison.lib")
#pragma comment(lib, "Abseil\\Debug\\absl_utf8_for_code_point.lib")
#else
#pragma comment(lib, "Servercore\\Release\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#pragma comment(lib, "Abseil\\Release\\abseil_dll.lib")
#pragma comment(lib, "Abseil\\Release\\absl_decode_rust_punycode.lib")
#pragma comment(lib, "Abseil\\Release\\absl_demangle_rust.lib")
#pragma comment(lib, "Abseil\\Release\\absl_flags_commandlineflag.lib")
#pragma comment(lib, "Abseil\\Release\\absl_flags_commandlineflag_internal.lib")
#pragma comment(lib, "Abseil\\Release\\absl_flags_config.lib")
#pragma comment(lib, "Abseil\\Release\\absl_flags_internal.lib")
#pragma comment(lib, "Abseil\\Release\\absl_flags_marshalling.lib")
#pragma comment(lib, "Abseil\\Release\\absl_flags_parse.lib")
#pragma comment(lib, "Abseil\\Release\\absl_flags_private_handle_accessor.lib")
#pragma comment(lib, "Abseil\\Release\\absl_flags_program_name.lib")
#pragma comment(lib, "Abseil\\Release\\absl_flags_reflection.lib")
#pragma comment(lib, "Abseil\\Release\\absl_flags_usage.lib")
#pragma comment(lib, "Abseil\\Release\\absl_flags_usage_internal.lib")
#pragma comment(lib, "Abseil\\Release\\absl_log_flags.lib")
#pragma comment(lib, "Abseil\\Release\\absl_poison.lib")
#pragma comment(lib, "Abseil\\Release\\absl_utf8_for_code_point.lib")
#endif

#include "CorePch.h"