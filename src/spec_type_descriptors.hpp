// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#pragma once

#include "etl/map.h"
#include "etl/string.h"
#include "etl/vector.h"
#include "ebpf_base.h"
#include "ebpf_vm_isa.hpp"

constexpr int EBPF_STACK_SIZE = 512;
constexpr size_t SIZE = 100;
constexpr size_t SIZE_VEC = 200;
constexpr size_t SIZE_MAP = 100;

enum class EbpfMapValueType {
    ANY, MAP, PROGRAM
};

struct EbpfMapType {
    uint32_t platform_specific_type; // EbpfMapDescriptor.type value.
    etl::string<SIZE> name; // For ease of display, not used by the verifier.
    bool is_array; // True if key is integer in range [0,max_entries-1].
    EbpfMapValueType value_type; // The type of items stored in the map.
};

struct EbpfMapDescriptor {
    int original_fd;
    uint32_t type; // Platform-specific type value in ELF file.
    unsigned int key_size;
    unsigned int value_size;
    unsigned int max_entries;
    unsigned int inner_map_fd;
};

struct EbpfProgramType {
    etl::string<SIZE> name; // For ease of display, not used by the verifier.
    const ebpf_context_descriptor_t* context_descriptor;
    uint64_t platform_specific_data; // E.g., integer program type.
    // TODO: fix
    // etl::vector<etl::string<SIZE>, SIZE_VEC> section_prefixes;
    bool is_privileged;
};

using EquivalenceKey = std::tuple<
    EbpfMapValueType /* value_type */,
    uint32_t /* key_size */,
    uint32_t /* value_size */,
    uint32_t /* max_entries */>;

struct program_info {
    const struct ebpf_platform_t* platform;
    etl::vector<EbpfMapDescriptor, SIZE_VEC> map_descriptors;
    EbpfProgramType type;
    etl::map<EquivalenceKey, int, SIZE_MAP> cache;
};

struct raw_program {
    etl::string<SIZE> filename;
    etl::string<SIZE> section;
    etl::vector<ebpf_inst, SIZE_VEC> prog;
    program_info info;
};

extern thread_local program_info global_program_info;
