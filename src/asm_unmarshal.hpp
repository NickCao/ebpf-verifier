// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#pragma once

#include "etl/optional.h"
#include "etl/string.h"
#include "etl/variant.h"
#include "etl/vector.h"

#include "asm_syntax.hpp"
#include "spec_type_descriptors.hpp"
#include "platform.hpp"

/** Translate a sequence of eBPF instructions (elf binary format) to a sequence
 *  of Instructions.
 *
 *  \param raw_prog is the input program to parse.
 *  \param notes is where errors and warnings are written to.
 *  \return a sequence of instruction if successful, an error string otherwise.
 */
etl::variant<InstructionSeq, etl::string<SIZE>> unmarshal(const raw_program& raw_prog, etl::vector<etl::vector<etl::string<SIZE>, SIZE_VEC>, SIZE_VEC>& notes);
etl::variant<InstructionSeq, etl::string<SIZE>> unmarshal(const raw_program& raw_prog);
