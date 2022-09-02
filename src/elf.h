#pragma once

#include <stdint.h>

namespace ELF
{

#define EI_NIDENT 16

#define Elf32_Addr uint32_t
#define Elf32_Off uint32_t

#define Elf64_Addr uint64_t
#define Elf64_Off uint64_t

#define Elf_Half uint16_t
#define Elf_Sword int32_t
#define Elf_Word uint32_t

#define EI_MAG0 0
#define EI_MAG1 1
#define EI_MAG2 2
#define EI_MAG3 3
#define EI_CLASS 4
#define EI_DATA 5

#define ELFMAG0 0x7f
#define ELFMAG1 'E'
#define ELFMAG2 'L'
#define ELFMAG3 'F'

    typedef struct _Elf32Header
    {
        uint8_t e_ident[EI_NIDENT];
        Elf_Half e_type;
        Elf_Half e_machine;
        Elf_Word e_version;
        Elf32_Addr e_entry;   // Entry to the executable
        Elf32_Off e_phoff;    // Program header table offset
        Elf32_Off e_shoff;    // Section header table offset
        Elf_Word e_flags;     // Processor specific flags
        Elf_Half e_ehsize;    // ELF header size
        Elf_Half e_phentsize; // Program header entry size
        Elf_Half e_phnum;     // Program header entry count
        Elf_Half e_shentsize; // Section header entry size
        Elf_Half e_shnum;     // Section header entry count
        Elf_Half e_shstrndx;  // Section name string table index
    } Elf32Header;

    typedef struct _Elf64Header
    {
        uint8_t e_ident[EI_NIDENT];
        Elf_Half e_type;
        Elf_Half e_machine;
        Elf_Word e_version;
        Elf64_Addr e_entry;   // Entry to the executable
        Elf64_Off e_phoff;    // Program header table offset
        Elf64_Off e_shoff;    // Section header table offset
        Elf_Word e_flags;     // Processor specific flags
        Elf_Half e_ehsize;    // ELF header size
        Elf_Half e_phentsize; // Program header entry size
        Elf_Half e_phnum;     // Program header entry count
        Elf_Half e_shentsize; // Section header entry size
        Elf_Half e_shnum;     // Section header entry count
        Elf_Half e_shstrndx;  // Section name string table index
    } Elf64Header;

    typedef enum _ElfType
    {
        ET_NONE = 0,
        ET_REL = 1,
        ET_EXEC = 2,
        ET_DYN = 3,
        ET_CORE = 4,
        ET_LOPROC = 0xff00,
        ET_HIPROC = 0xffff,
    } ElfType;

    typedef enum _ElfMachine
    {
        EM_NONE = 0,
        EM_M32 = 1,
        EM_SPARC = 2,
        EM386 = 3,
        EM_68K = 4,
        EM_88K = 5,
        EM_860 = 7,
        EM_MIPS = 8,
    } ElfMachine;

    typedef enum _ElfVersion
    {
        EV_NONE = 0,
        EV_CURRENT = 1,
    } ElfVersion;

    typedef enum _ElfClass
    {
        ELFCLASSNONE = 0,
        ELFCLASS32 = 1,
        ELFCLASS64 = 2,
    } ElfClass;

    typedef enum _ElfData
    {
        ELFDATANONE = 0,
        ELFDATA2LSB = 1,
        ELFDATA2MSB = 2,
    } ElfData;

    typedef enum _ElfVerifyErr
    {
        VerifyOK,
        VerifyFailed,
    } ElfVerifyErr;

    typedef enum _ElfLoadErr
    {
        LoadOK,
        LoadFailed,
    } ElfLoadErr;

    class ELF
    {
    private:
        Elf32Header header32;
        Elf64Header header64;

        void *entry;

    public:
        ELF();
        ELF(FILE *elfFile);
        ~ELF();

        // TODO: Add what to verify against
        ElfVerifyErr verify();
        ElfLoadErr load();
        int run();
    };

}