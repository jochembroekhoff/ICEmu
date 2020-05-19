#ifndef MEMLAYOUT_H_
#define MEMLAYOUT_H_

#include <cstdint>
#include <string>
#include <vector>

#include "elfio/elfio.hpp"
#include "config.h"

typedef uint32_t armaddr_t;

typedef struct memsec {
    std::string name;
    armaddr_t origin;
    armaddr_t length;

    uint8_t *data;
} memsec_t;

typedef struct memseg {
    std::string name;
    armaddr_t origin;
    armaddr_t length;

    std::vector<memsec_t> sections; // Sections part of this segment
} memseg_t;

class MemLayout {
    private:
        bool good_ = false;
        std::string elf_file_;
        Config &cfg_;
        bool collect();

    public:
        ELFIO::elfio elf_reader;
        std::vector<memseg_t> memory;

        MemLayout(Config &cfg, std::string elf_file) : cfg_(cfg) {
            elf_file_ = elf_file;
            good_ = collect();
        }

        bool good() {return good_;}
        bool bad() {return !good_;}

        friend std::ostream& operator<< (std::ostream &out, const MemLayout& ml);
};

// Printing
inline std::ostream& operator<< (std::ostream &out, const MemLayout& ml) {
    out << "Elf file: " << ml.elf_file_ << std::endl;
    out << "Segments:" << std::endl;

    for (const auto &m : ml.memory) {
        out << "Name = " << m.name
            << " : Origin = 0x" << std::hex << m.origin
            << ", Length = " << std::dec << m.length << std::endl;

        //out << "Sections:" << std::endl;
        for (const auto &sec : m.sections) {
            out << "  Section: " << sec.name
                << " orig: "
                << "0x" << std::hex << sec.origin
                << " length: "
                << sec.length
                << std::endl;
        }
    }
    return out;
}

#endif /* MEMLAYOUT_H_ */
