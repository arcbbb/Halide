#ifndef HALIDE_CODEGEN_RISCV_H
#define HALIDE_CODEGEN_RISCV_H

#include "CodeGen_Posix.h"

namespace Halide {
namespace Internal {

class CodeGen_RISCV : public CodeGen_Posix {
public:
    CodeGen_RISCV(Target);

protected:

    std::string mcpu() const override;
    std::string mattrs() const override;
    bool use_soft_float_abi() const override;
    int native_vector_bits() const override;
};

}  // namespace Internal
}  // namespace Halide

#endif

