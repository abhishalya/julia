// This file is a part of Julia. License is MIT: https://julialang.org/license

// Declarations for debuginfo.cpp

extern int jl_DI_for_fptr(uint64_t fptr, uint64_t *symsize, int64_t *slide, int64_t *section_slide,
        const object::ObjectFile **object,
        llvm::DIContext **context);

extern bool jl_dylib_DI_for_fptr(size_t pointer, const object::ObjectFile **object, llvm::DIContext **context,
        int64_t *slide, int64_t *section_slide,
        bool onlySysImg, bool *isSysImg, void **saddr, char **name, char **filename);

extern uint64_t getModuleSectionIndexForAddress(const object::ObjectFile *obj, uint64_t Address);

#if JL_LLVM_VERSION >= 90000
static object::SectionedAddress makeAddress(const llvm::object::ObjectFile *object, uint64_t address)
{
    return object::SectionedAddress{address, getModuleSectionIndexForAddress(object, address)};
}
#else
static uint64_t makeAddress(const llvm::object::ObjectFile *object, uint64_t address)
{
    (void)object;
    return address;
}
#endif
