// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#pragma once

#include "platform.hpp"

#if __linux__

#include "etl/tuple.h"
#include "etl/vector.h"

#include "asm_syntax.hpp"
#include "spec_type_descriptors.hpp"
#include "linux/gpl/spec_type_descriptors.hpp"
#include "ebpf_vm_isa.hpp"

int create_map_linux(uint32_t map_type, uint32_t key_size, uint32_t value_size, uint32_t max_entries, ebpf_verifier_options_t options);
etl::tuple<bool, double> bpf_verify_program(const EbpfProgramType& type, const etl::vector<ebpf_inst, SIZE_VEC>& raw_prog, ebpf_verifier_options_t* options);

#else

#define create_map_linux (nullptr)

inline etl::tuple<bool, double> bpf_verify_program(EbpfProgramType type, const etl::vector<ebpf_inst, SIZE_VEC>& raw_prog, ebpf_verifier_options_t* options) {
    exit(64);
    return {{}, {}};
}
#endif
