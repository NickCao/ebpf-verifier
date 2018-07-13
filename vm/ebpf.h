/*
 * Copyright 2015 Big Switch Networks, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef EBPF_H
#define EBPF_H

#include <stdint.h>

/* eBPF definitions */

struct ebpf_inst {
    uint8_t opcode;
    uint8_t dst : 4;
    uint8_t src : 4;
    int16_t offset;
    int32_t imm;
};

#define EBPF_CLS_MASK 0x07
#define EBPF_ALU_OP_MASK 0xf0

#define EBPF_CLS_LD 0x00
#define EBPF_CLS_LDX 0x01
#define EBPF_CLS_ST 0x02
#define EBPF_CLS_STX 0x03
#define EBPF_CLS_ALU 0x04
#define EBPF_CLS_JMP 0x05
#define EBPF_CLS_ALU64 0x07

#define EBPF_SRC_IMM 0x00
#define EBPF_SRC_REG 0x08

#define EBPF_SIZE_W 0x00
#define EBPF_SIZE_H 0x08
#define EBPF_SIZE_B 0x10
#define EBPF_SIZE_DW 0x18

#define EBPF_SIZE_MASK 0x18 

/* Other memory modes are not yet supported */
#define EBPF_MODE_IMM 0x00
#define EBPF_MODE_ABS 0x20 // new
#define	EBPF_MODE_IND 0x40 // new
#define EBPF_MODE_MEM 0x60
#define	EBPF_MODE_LEN 0x80 // new
#define	EBPF_MODE_MSH 0xa0 // new

#define EBPF_XADD 0xc0

#define EBPF_STXADDW  (EBPF_CLS_STX|EBPF_XADD|EBPF_SIZE_W)
#define EBPF_STXADDDW (EBPF_CLS_STX|EBPF_XADD|EBPF_SIZE_DW)

#define EBPF_OP_ADD_IMM  (EBPF_CLS_ALU|EBPF_SRC_IMM|0x00)
#define EBPF_OP_ADD_REG  (EBPF_CLS_ALU|EBPF_SRC_REG|0x00)
#define EBPF_OP_SUB_IMM  (EBPF_CLS_ALU|EBPF_SRC_IMM|0x10)
#define EBPF_OP_SUB_REG  (EBPF_CLS_ALU|EBPF_SRC_REG|0x10)
#define EBPF_OP_MUL_IMM  (EBPF_CLS_ALU|EBPF_SRC_IMM|0x20)
#define EBPF_OP_MUL_REG  (EBPF_CLS_ALU|EBPF_SRC_REG|0x20)
#define EBPF_OP_DIV_IMM  (EBPF_CLS_ALU|EBPF_SRC_IMM|0x30)
#define EBPF_OP_DIV_REG  (EBPF_CLS_ALU|EBPF_SRC_REG|0x30)
#define EBPF_OP_OR_IMM   (EBPF_CLS_ALU|EBPF_SRC_IMM|0x40)
#define EBPF_OP_OR_REG   (EBPF_CLS_ALU|EBPF_SRC_REG|0x40)
#define EBPF_OP_AND_IMM  (EBPF_CLS_ALU|EBPF_SRC_IMM|0x50)
#define EBPF_OP_AND_REG  (EBPF_CLS_ALU|EBPF_SRC_REG|0x50)
#define EBPF_OP_LSH_IMM  (EBPF_CLS_ALU|EBPF_SRC_IMM|0x60)
#define EBPF_OP_LSH_REG  (EBPF_CLS_ALU|EBPF_SRC_REG|0x60)
#define EBPF_OP_RSH_IMM  (EBPF_CLS_ALU|EBPF_SRC_IMM|0x70)
#define EBPF_OP_RSH_REG  (EBPF_CLS_ALU|EBPF_SRC_REG|0x70)
#define EBPF_OP_NEG      (EBPF_CLS_ALU|0x80)
#define EBPF_OP_MOD_IMM  (EBPF_CLS_ALU|EBPF_SRC_IMM|0x90)
#define EBPF_OP_MOD_REG  (EBPF_CLS_ALU|EBPF_SRC_REG|0x90)
#define EBPF_OP_XOR_IMM  (EBPF_CLS_ALU|EBPF_SRC_IMM|0xa0)
#define EBPF_OP_XOR_REG  (EBPF_CLS_ALU|EBPF_SRC_REG|0xa0)
#define EBPF_OP_MOV_IMM  (EBPF_CLS_ALU|EBPF_SRC_IMM|0xb0)
#define EBPF_OP_MOV_REG  (EBPF_CLS_ALU|EBPF_SRC_REG|0xb0)
#define EBPF_OP_ARSH_IMM (EBPF_CLS_ALU|EBPF_SRC_IMM|0xc0)
#define EBPF_OP_ARSH_REG (EBPF_CLS_ALU|EBPF_SRC_REG|0xc0)
#define EBPF_OP_LE       (EBPF_CLS_ALU|EBPF_SRC_IMM|0xd0)
#define EBPF_OP_BE       (EBPF_CLS_ALU|EBPF_SRC_REG|0xd0)

#define EBPF_OP_ADD64_IMM  (EBPF_CLS_ALU64|EBPF_SRC_IMM|0x00)
#define EBPF_OP_ADD64_REG  (EBPF_CLS_ALU64|EBPF_SRC_REG|0x00)
#define EBPF_OP_SUB64_IMM  (EBPF_CLS_ALU64|EBPF_SRC_IMM|0x10)
#define EBPF_OP_SUB64_REG  (EBPF_CLS_ALU64|EBPF_SRC_REG|0x10)
#define EBPF_OP_MUL64_IMM  (EBPF_CLS_ALU64|EBPF_SRC_IMM|0x20)
#define EBPF_OP_MUL64_REG  (EBPF_CLS_ALU64|EBPF_SRC_REG|0x20)
#define EBPF_OP_DIV64_IMM  (EBPF_CLS_ALU64|EBPF_SRC_IMM|0x30)
#define EBPF_OP_DIV64_REG  (EBPF_CLS_ALU64|EBPF_SRC_REG|0x30)
#define EBPF_OP_OR64_IMM   (EBPF_CLS_ALU64|EBPF_SRC_IMM|0x40)
#define EBPF_OP_OR64_REG   (EBPF_CLS_ALU64|EBPF_SRC_REG|0x40)
#define EBPF_OP_AND64_IMM  (EBPF_CLS_ALU64|EBPF_SRC_IMM|0x50)
#define EBPF_OP_AND64_REG  (EBPF_CLS_ALU64|EBPF_SRC_REG|0x50)
#define EBPF_OP_LSH64_IMM  (EBPF_CLS_ALU64|EBPF_SRC_IMM|0x60)
#define EBPF_OP_LSH64_REG  (EBPF_CLS_ALU64|EBPF_SRC_REG|0x60)
#define EBPF_OP_RSH64_IMM  (EBPF_CLS_ALU64|EBPF_SRC_IMM|0x70)
#define EBPF_OP_RSH64_REG  (EBPF_CLS_ALU64|EBPF_SRC_REG|0x70)
#define EBPF_OP_NEG64      (EBPF_CLS_ALU64|0x80)
#define EBPF_OP_MOD64_IMM  (EBPF_CLS_ALU64|EBPF_SRC_IMM|0x90)
#define EBPF_OP_MOD64_REG  (EBPF_CLS_ALU64|EBPF_SRC_REG|0x90)
#define EBPF_OP_XOR64_IMM  (EBPF_CLS_ALU64|EBPF_SRC_IMM|0xa0)
#define EBPF_OP_XOR64_REG  (EBPF_CLS_ALU64|EBPF_SRC_REG|0xa0)
#define EBPF_OP_MOV64_IMM  (EBPF_CLS_ALU64|EBPF_SRC_IMM|0xb0)
#define EBPF_OP_MOV64_REG  (EBPF_CLS_ALU64|EBPF_SRC_REG|0xb0)
#define EBPF_OP_ARSH64_IMM (EBPF_CLS_ALU64|EBPF_SRC_IMM|0xc0)
#define EBPF_OP_ARSH64_REG (EBPF_CLS_ALU64|EBPF_SRC_REG|0xc0)

#define EBPF_OP_LDXW  (EBPF_CLS_LDX|EBPF_MODE_MEM|EBPF_SIZE_W)
#define EBPF_OP_LDXH  (EBPF_CLS_LDX|EBPF_MODE_MEM|EBPF_SIZE_H)
#define EBPF_OP_LDXB  (EBPF_CLS_LDX|EBPF_MODE_MEM|EBPF_SIZE_B)
#define EBPF_OP_LDXDW (EBPF_CLS_LDX|EBPF_MODE_MEM|EBPF_SIZE_DW)
#define EBPF_OP_STW   (EBPF_CLS_ST|EBPF_MODE_MEM|EBPF_SIZE_W)
#define EBPF_OP_STH   (EBPF_CLS_ST|EBPF_MODE_MEM|EBPF_SIZE_H)
#define EBPF_OP_STB   (EBPF_CLS_ST|EBPF_MODE_MEM|EBPF_SIZE_B)
#define EBPF_OP_STDW  (EBPF_CLS_ST|EBPF_MODE_MEM|EBPF_SIZE_DW)
#define EBPF_OP_STXW  (EBPF_CLS_STX|EBPF_MODE_MEM|EBPF_SIZE_W)
#define EBPF_OP_STXH  (EBPF_CLS_STX|EBPF_MODE_MEM|EBPF_SIZE_H)
#define EBPF_OP_STXB  (EBPF_CLS_STX|EBPF_MODE_MEM|EBPF_SIZE_B)
#define EBPF_OP_STXDW (EBPF_CLS_STX|EBPF_MODE_MEM|EBPF_SIZE_DW)

#define EBPF_OP_LDDW      (EBPF_CLS_LD |EBPF_MODE_IMM|EBPF_SIZE_DW) // Special

#define EBPF_OP_LDABSW    (EBPF_CLS_LD |EBPF_MODE_ABS|EBPF_SIZE_W)
#define EBPF_OP_LDABSH    (EBPF_CLS_LD |EBPF_MODE_ABS|EBPF_SIZE_H)
#define EBPF_OP_LDABSB    (EBPF_CLS_LD |EBPF_MODE_ABS|EBPF_SIZE_B)
#define EBPF_OP_LDABSDW   (EBPF_CLS_LD |EBPF_MODE_ABS|EBPF_SIZE_DW)
#define EBPF_OP_LDXABSW   (EBPF_CLS_LDX|EBPF_MODE_ABS|EBPF_SIZE_W)
#define EBPF_OP_LDXABSH   (EBPF_CLS_LDX|EBPF_MODE_ABS|EBPF_SIZE_H)
#define EBPF_OP_LDXABSB   (EBPF_CLS_LDX|EBPF_MODE_ABS|EBPF_SIZE_B)
#define EBPF_OP_LDXABSDW  (EBPF_CLS_LDX|EBPF_MODE_ABS|EBPF_SIZE_DW)
#define EBPF_OP_STABSW    (EBPF_CLS_ST |EBPF_MODE_ABS|EBPF_SIZE_W)
#define EBPF_OP_STABSH    (EBPF_CLS_ST |EBPF_MODE_ABS|EBPF_SIZE_H)
#define EBPF_OP_STABSB    (EBPF_CLS_ST |EBPF_MODE_ABS|EBPF_SIZE_B)
#define EBPF_OP_STABSDW   (EBPF_CLS_ST |EBPF_MODE_ABS|EBPF_SIZE_DW)
#define EBPF_OP_STXABSW   (EBPF_CLS_STX|EBPF_MODE_ABS|EBPF_SIZE_W)
#define EBPF_OP_STXABSH   (EBPF_CLS_STX|EBPF_MODE_ABS|EBPF_SIZE_H)
#define EBPF_OP_STXABSB   (EBPF_CLS_STX|EBPF_MODE_ABS|EBPF_SIZE_B)
#define EBPF_OP_STXABSDW  (EBPF_CLS_STX|EBPF_MODE_ABS|EBPF_SIZE_DW)

#define EBPF_OP_LDINDW    (EBPF_CLS_LD |EBPF_MODE_IND|EBPF_SIZE_W)
#define EBPF_OP_LDINDH    (EBPF_CLS_LD |EBPF_MODE_IND|EBPF_SIZE_H)
#define EBPF_OP_LDINDB    (EBPF_CLS_LD |EBPF_MODE_IND|EBPF_SIZE_B)
#define EBPF_OP_LDINDDW   (EBPF_CLS_LD |EBPF_MODE_IND|EBPF_SIZE_DW)
#define EBPF_OP_LDXINDW   (EBPF_CLS_LDX|EBPF_MODE_IND|EBPF_SIZE_W)
#define EBPF_OP_LDXINDH   (EBPF_CLS_LDX|EBPF_MODE_IND|EBPF_SIZE_H)
#define EBPF_OP_LDXINDB   (EBPF_CLS_LDX|EBPF_MODE_IND|EBPF_SIZE_B)
#define EBPF_OP_LDXINDDW  (EBPF_CLS_LDX|EBPF_MODE_IND|EBPF_SIZE_DW)
#define EBPF_OP_STINDW    (EBPF_CLS_ST |EBPF_MODE_IND|EBPF_SIZE_W)
#define EBPF_OP_STINDH    (EBPF_CLS_ST |EBPF_MODE_IND|EBPF_SIZE_H)
#define EBPF_OP_STINDB    (EBPF_CLS_ST |EBPF_MODE_IND|EBPF_SIZE_B)
#define EBPF_OP_STINDDW   (EBPF_CLS_ST |EBPF_MODE_IND|EBPF_SIZE_DW)
#define EBPF_OP_STXINDW   (EBPF_CLS_STX|EBPF_MODE_IND|EBPF_SIZE_W)
#define EBPF_OP_STXINDH   (EBPF_CLS_STX|EBPF_MODE_IND|EBPF_SIZE_H)
#define EBPF_OP_STXINDB   (EBPF_CLS_STX|EBPF_MODE_IND|EBPF_SIZE_B)
#define EBPF_OP_STXINDDW  (EBPF_CLS_STX|EBPF_MODE_IND|EBPF_SIZE_DW)

#define EBPF_OP_JA       (EBPF_CLS_JMP|0x00)
#define EBPF_OP_JEQ_IMM  (EBPF_CLS_JMP|EBPF_SRC_IMM|0x10)
#define EBPF_OP_JEQ_REG  (EBPF_CLS_JMP|EBPF_SRC_REG|0x10)
#define EBPF_OP_JGT_IMM  (EBPF_CLS_JMP|EBPF_SRC_IMM|0x20)
#define EBPF_OP_JGT_REG  (EBPF_CLS_JMP|EBPF_SRC_REG|0x20)
#define EBPF_OP_JGE_IMM  (EBPF_CLS_JMP|EBPF_SRC_IMM|0x30)
#define EBPF_OP_JGE_REG  (EBPF_CLS_JMP|EBPF_SRC_REG|0x30)
#define EBPF_OP_JSET_REG (EBPF_CLS_JMP|EBPF_SRC_REG|0x40)
#define EBPF_OP_JSET_IMM (EBPF_CLS_JMP|EBPF_SRC_IMM|0x40)
#define EBPF_OP_JNE_IMM  (EBPF_CLS_JMP|EBPF_SRC_IMM|0x50)
#define EBPF_OP_JNE_REG  (EBPF_CLS_JMP|EBPF_SRC_REG|0x50)
#define EBPF_OP_JSGT_IMM (EBPF_CLS_JMP|EBPF_SRC_IMM|0x60)
#define EBPF_OP_JSGT_REG (EBPF_CLS_JMP|EBPF_SRC_REG|0x60)
#define EBPF_OP_JSGE_IMM (EBPF_CLS_JMP|EBPF_SRC_IMM|0x70)
#define EBPF_OP_JSGE_REG (EBPF_CLS_JMP|EBPF_SRC_REG|0x70)
#define EBPF_OP_CALL     (EBPF_CLS_JMP|0x80)
#define EBPF_OP_EXIT     (EBPF_CLS_JMP|0x90)
#define EBPF_OP_JLT_IMM  (EBPF_CLS_JMP|EBPF_SRC_IMM|0xa0)
#define EBPF_OP_JLT_REG  (EBPF_CLS_JMP|EBPF_SRC_REG|0xa0)
#define EBPF_OP_JLE_IMM  (EBPF_CLS_JMP|EBPF_SRC_IMM|0xb0)
#define EBPF_OP_JLE_REG  (EBPF_CLS_JMP|EBPF_SRC_REG|0xb0)
#define EBPF_OP_JSLT_IMM (EBPF_CLS_JMP|EBPF_SRC_IMM|0xc0)
#define EBPF_OP_JSLT_REG (EBPF_CLS_JMP|EBPF_SRC_REG|0xc0)
#define EBPF_OP_JSLE_IMM (EBPF_CLS_JMP|EBPF_SRC_IMM|0xd0)
#define EBPF_OP_JSLE_REG (EBPF_CLS_JMP|EBPF_SRC_REG|0xd0)

#endif
