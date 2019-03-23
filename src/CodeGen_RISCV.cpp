#include <iostream>
#include <sstream>

#include "CodeGen_RISCV.h"
#include "ConciseCasts.h"
#include "Debug.h"
#include "IREquality.h"
#include "IRMatch.h"
#include "IROperator.h"
#include "IRPrinter.h"
#include "LLVM_Headers.h"
#include "Simplify.h"
#include "Util.h"

namespace Halide {
namespace Internal {

using std::ostringstream;
using std::pair;
using std::string;
using std::vector;

using namespace Halide::ConciseCasts;
using namespace llvm;

CodeGen_RISCV::CodeGen_RISCV(Target target) : CodeGen_Posix(target) {
}

string CodeGen_RISCV::mcpu() const {
    return "";
}

string CodeGen_RISCV::mattrs() const {
    return "+m,+a,+c";
}

bool CodeGen_RISCV::use_soft_float_abi() const {
    return target.has_feature(Target::SoftFloatABI);
}

int CodeGen_RISCV::native_vector_bits() const {
    return 128;
}
}  // namespace Internal
}  // namespace Halide
