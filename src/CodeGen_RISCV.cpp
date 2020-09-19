#include "CodeGen_RISCV.h"
#include "LLVM_Headers.h"
#include "Util.h"

namespace Halide {
namespace Internal {

using std::string;

using namespace llvm;

CodeGen_RISCV::CodeGen_RISCV(Target t)
    : CodeGen_Posix(t) {
#if !defined(WITH_RISCV)
    user_error << "llvm build not configured with RISCV target enabled.\n";
#endif
}

string CodeGen_RISCV::mcpu() const {
    return "";
}

string CodeGen_RISCV::mattrs() const {
    string arch_flags;
    if (target.has_feature(Target::RVV)) {
        arch_flags = "+experimental-v";
    }
    return arch_flags;
}

bool CodeGen_RISCV::use_soft_float_abi() const {
    return false;
}

int CodeGen_RISCV::native_vector_bits() const {
    if (target.has_feature(Target::RVV)) {
        // FIXME: should check the cpu implementation
        return 512;
    }
    return 128;
}

}  // namespace Internal
}  // namespace Halide
