#pragma once

#include <vector>
#include <unordered_map>

#include "asm_syntax.hpp"

struct BasicBlock {
    std::vector<Instruction> insts;
    std::vector<Label> nextlist;
    std::vector<Label> prevlist;
    std::vector<std::string> pres;
    std::vector<std::string> posts;
};

struct CfgStats {
    int count = 0;
    int stores = 0;
    int loads = 0;
    int jumps = 0;
    int joins = 0;
};

class Cfg {
    std::unordered_map<Label, BasicBlock> graph;
    std::vector<Label> ordered_labels;

    void encountered(Label l) { ordered_labels.push_back(l); }
    Cfg() { }
    Cfg(const Cfg& _) = delete;
public:
    Cfg(Cfg&& _) = default;
    Cfg& operator=(Cfg&& _) = default;
    BasicBlock& operator[](Label l) { return graph[l]; }
    BasicBlock const& at(Label l) const { return graph.at(l); }

    std::vector<Label> const& keys() const { return ordered_labels; }

    static Cfg make(const InstructionSeq& labeled_insts);
                
    Cfg to_nondet(bool expand_locks) const;
    void simplify();

    CfgStats collect_stats() const {
        CfgStats res;
        for (Label const& this_label : keys()) {
            BasicBlock const& bb = at(this_label);
            for (Instruction ins : bb.insts) {
                res.count++;
                if (std::holds_alternative<Mem>(ins)) {
                    auto mem = std::get<Mem>(ins);
                    if (mem.is_load)
                        res.loads++;
                    else
                        res.stores++;
                }
            }
            if (bb.prevlist.size() > 1)
                res.joins++;
            if (bb.nextlist.size() > 1)
                res.jumps++;
        }
        return res;
    }
};
