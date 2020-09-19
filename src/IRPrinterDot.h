#ifndef HALIDE_IRVIZ_H
#define HALIDE_IRVIZ_H
#include "IRVisitor.h"

#include <string>
#include <fstream>
#include <map>

namespace Halide {
namespace Internal {

class IRPrinterDot : public IRVisitor {
public:
    IRPrinterDot(std::string dotname);
    ~IRPrinterDot();
protected:
    std::ofstream os;
    std::map<const void *, int> defined;
    int defined_id;
    int define(const void *, std::string&);
    int use(const void *op);
    void link(int node, const std::string &field, IRHandle node_next);
    void visit(const IntImm *) override;
    void visit(const UIntImm *) override;
    void visit(const FloatImm *) override;
    void visit(const StringImm *) override;
    void visit(const Cast *) override;
    void visit(const Variable *) override;
    void visit(const Add *) override;
    void visit(const Sub *) override;
    void visit(const Mul *) override;
    void visit(const Div *) override;
    void visit(const Mod *) override;
    void visit(const Min *) override;
    void visit(const Max *) override;
    void visit(const EQ *) override;
    void visit(const NE *) override;
    void visit(const LT *) override;
    void visit(const LE *) override;
    void visit(const GT *) override;
    void visit(const GE *) override;
    void visit(const And *) override;
    void visit(const Or *) override;
    void visit(const Not *) override;
    void visit(const Select *) override;
    void visit(const Load *) override;
    void visit(const Ramp *) override;
    void visit(const Broadcast *) override;
    void visit(const Call *) override;
    void visit(const Let *) override;
    void visit(const LetStmt *) override;
    void visit(const AssertStmt *) override;
    void visit(const ProducerConsumer *) override;
    void visit(const For *) override;
    void visit(const Store *) override;
    void visit(const Provide *) override;
    void visit(const Allocate *) override;
    void visit(const Free *) override;
    void visit(const Realize *) override;
    void visit(const Block *) override;
    void visit(const IfThenElse *) override;
    void visit(const Evaluate *) override;
    void visit(const Shuffle *) override;
    void visit(const VectorReduce *) override;
    void visit(const Prefetch *) override;
    void visit(const Fork *) override;
    void visit(const Acquire *) override;
    void visit(const Atomic *) override;
};

}  // namespace Internal
}  // namespace Halide
#endif
