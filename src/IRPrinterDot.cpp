
#include "IRPrinterDot.h"

#include "ExternFuncArgument.h"
#include "Function.h"

namespace Halide {
namespace Internal {

IRPrinterDot::~IRPrinterDot() {
    os << "}\n";
    os.close();
}

IRPrinterDot::IRPrinterDot(std::string dotname) : os(dotname), defined_id(0) {
    os << "digraph G {\n";
}

int IRPrinterDot::define(const void *op, std::string &def) {
    std::map<const void*, int>::iterator it;
    it = defined.find(op);
    if (it == defined.end()) {
        defined.insert(std::pair<const void *, int>(op, defined_id));
        os << "node_" + std::to_string(defined_id) + def << "\n";
        return defined_id++;
    } else {
        return it->second;
    }
}

int IRPrinterDot::use(const void *op) {
    std::map<const void*, int>::iterator it;
    it = defined.find(op);
    if (it != defined.end()) {
        return it->second;
    }
    return -1;
}

void IRPrinterDot::link(int node, const std::string &field, IRHandle node_next) {
    int id_next = use(node_next.get());
    std::string link = "node_" + std::to_string(node) + ":" + field + " -> node_" + std::to_string(id_next);
    os << link << "\n";
}
void IRPrinterDot::visit(const IntImm *op) {
    /*
     * [ label = "{{<port>IntImm}|{value: 16}}" shape = "record" ];
     */
    std::string def = "[ label = \"{{<port>IntImm}|{value:" + std::to_string(op->value) + "}}\" shape = \"record\" ];";
    define(op, def);
}

void IRPrinterDot::visit(const UIntImm *op) {
    /*
     * [ label = "{{<port>UIntImm}|{value: 16}}" shape = "record" ];
     */
    std::string def = "[ label = \"{{<port>UIntImm}|{value:" + std::to_string(op->value) + "}}\" shape = \"record\" ];";
    define(op, def);
}

void IRPrinterDot::visit(const FloatImm *op) {
    /*
     * [ label = "{{<port>FloatImm}|{value: 16}}" shape = "record" ];
     */
    std::string def = "[ label = \"{{<port>FloatImm}|{value:" + std::to_string(op->value) + "}}\" shape = \"record\" ];";
    define(op, def);
}

void IRPrinterDot::visit(const StringImm *op) {
    /*
     * [ label = "{{<port>StringImm}|{value: 16}}" shape = "record" ];
     */
    std::string def = "[ label = \"{{<port>StringImm}|{value:'" + op->value + "'}}\" shape = \"record\" ];";
    define(op, def);
}

void IRPrinterDot::visit(const Cast *op) {
    op->value.accept(this);
    /*
      [
        label = "{{<port>Cast}|{<value>value}}"
        shape = "record"
      ];
    */
    std::string def = "[ label = \"{{<port>Cast}|{<value>value}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "value", op->value);
}

void IRPrinterDot::visit(const Variable *op) {
    std::string def = "[ label = \"{{<port>Variable}|{name: '" + op->name +
                       "'}}\" shape = \"record\" ];";
    define(op, def);
}

void IRPrinterDot::visit(const Add *op) {
    op->a.accept(this);
    op->b.accept(this);
    std::string def = "[ label = \"{{<port>Add}|{<a>a|<b>b}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "a", op->a);
    link(op_id, "b", op->b);
}

void IRPrinterDot::visit(const Sub *op) {
    op->a.accept(this);
    op->b.accept(this);
    std::string def = "[ label = \"{{<port>Sub}|{<a>a|<b>b}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "a", op->a);
    link(op_id, "b", op->b);
}

void IRPrinterDot::visit(const Mul *op) {
    op->a.accept(this);
    op->b.accept(this);
    std::string def = "[ label = \"{{<port>Mul}|{<a>a|<b>b}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "a", op->a);
    link(op_id, "b", op->b);
}

void IRPrinterDot::visit(const Div *op) {
    op->a.accept(this);
    op->b.accept(this);
    std::string def = "[ label = \"{{<port>Div}|{<a>a|<b>b}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "a", op->a);
    link(op_id, "b", op->b);
}

void IRPrinterDot::visit(const Mod *op) {
    op->a.accept(this);
    op->b.accept(this);
    std::string def = "[ label = \"{{<port>Mod}|{<a>a|<b>b}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "a", op->a);
    link(op_id, "b", op->b);
}

void IRPrinterDot::visit(const Min *op) {
    op->a.accept(this);
    op->b.accept(this);
    std::string def = "[ label = \"{{<port>Min}|{<a>a|<b>b}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "a", op->a);
    link(op_id, "b", op->b);
}

void IRPrinterDot::visit(const Max *op) {
    op->a.accept(this);
    op->b.accept(this);
    std::string def = "[ label = \"{{<port>Max}|{<a>a|<b>b}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "a", op->a);
    link(op_id, "b", op->b);
}

void IRPrinterDot::visit(const EQ *op) {
    op->a.accept(this);
    op->b.accept(this);
    std::string def = "[ label = \"{{<port>EQ}|{<a>a|<b>b}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "a", op->a);
    link(op_id, "b", op->b);
}

void IRPrinterDot::visit(const NE *op) {
    op->a.accept(this);
    op->b.accept(this);
    std::string def = "[ label = \"{{<port>NE}|{<a>a|<b>b}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "a", op->a);
    link(op_id, "b", op->b);
}

void IRPrinterDot::visit(const LT *op) {
    op->a.accept(this);
    op->b.accept(this);
    std::string def = "[ label = \"{{<port>LT}|{<a>a|<b>b}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "a", op->a);
    link(op_id, "b", op->b);
}

void IRPrinterDot::visit(const LE *op) {
    op->a.accept(this);
    op->b.accept(this);
    std::string def = "[ label = \"{{<port>LE}|{<a>a|<b>b}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "a", op->a);
    link(op_id, "b", op->b);
}

void IRPrinterDot::visit(const GT *op) {
    op->a.accept(this);
    op->b.accept(this);
    std::string def = "[ label = \"{{<port>GT}|{<a>a|<b>b}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "a", op->a);
    link(op_id, "b", op->b);
}

void IRPrinterDot::visit(const GE *op) {
    op->a.accept(this);
    op->b.accept(this);
    std::string def = "[ label = \"{{<port>GE}|{<a>a|<b>b}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "a", op->a);
    link(op_id, "b", op->b);
}

void IRPrinterDot::visit(const And *op) {
    op->a.accept(this);
    op->b.accept(this);
    std::string def = "[ label = \"{{<port>And}|{<a>a|<b>b}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "a", op->a);
    link(op_id, "b", op->b);
}

void IRPrinterDot::visit(const Or *op) {
    op->a.accept(this);
    op->b.accept(this);
    std::string def = "[ label = \"{{<port>Or}|{<a>a|<b>b}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "a", op->a);
    link(op_id, "b", op->b);
}

void IRPrinterDot::visit(const Not *op) {
    op->a.accept(this);
    std::string def = "[ label = \"{{<port>Not}|{<a>a}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "a", op->a);
}

void IRPrinterDot::visit(const Select *op) {
    op->condition.accept(this);
    op->true_value.accept(this);
    op->false_value.accept(this);
    std::string def = "[ label = \"{{<port>Select}|{<condition>condition|<true_value>true_value|<false_value>false_value}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "true_value", op->true_value);
    link(op_id, "false_value", op->false_value);
}

void IRPrinterDot::visit(const Load *op) {
    op->predicate.accept(this);
    op->index.accept(this);
    std::string def = "[ label = \"{{<port>Load}|{name: '" + op->name +
                      "'|<index>index}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "index", op->index);
}

void IRPrinterDot::visit(const Ramp *op) {
    op->base.accept(this);
    op->stride.accept(this);
    std::string def = "[ label = \"{{<port>Ramp}|{<base>base|<stride>stride}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "base", op->base);
    link(op_id, "stride", op->stride);
}

void IRPrinterDot::visit(const Broadcast *op) {
    op->value.accept(this);
    std::string def = "[ label = \"{{<port>Broadcast}|{lanes: " + std::to_string(op->lanes) + "|<value>value}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "value", op->value);
}

void IRPrinterDot::visit(const Call *op) {
    std::string def = "[ label = \"{{<port>Call}|{name: '" + op->name + "'";
    for (size_t i = 0; i < op->args.size(); i++) {
        def += "|<arg_" + std::to_string(i) +">Expr";
    }
    def += "}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    int id = 0;
    for (size_t i = 0; i < op->args.size(); i++) {
        op->args[i].accept(this);
        link(op_id, "arg_" + std::to_string(id), op->args[i]);
        id++;
    }

    // Consider extern call args
    if (op->func.defined()) {
        Function f(op->func);
        if (op->call_type == Call::Halide && f.has_extern_definition()) {
            for (size_t i = 0; i < f.extern_arguments().size(); i++) {
                ExternFuncArgument arg = f.extern_arguments()[i];
                if (arg.is_expr()) {
                    arg.expr.accept(this);
                }
            }
        }
    }
}

void IRPrinterDot::visit(const Let *op) {
    op->value.accept(this);
    op->body.accept(this);
    std::string def = "[ label = \"{{<port>Let}|{name: '" + op->name + "'|<value>value|<body>body}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "value", op->value);
    link(op_id, "body", op->body);
}

void IRPrinterDot::visit(const LetStmt *op) {
    op->value.accept(this);
    op->body.accept(this);
    std::string def = "[ label = \"{{<port>LetStmt}|{name: '" + op->name + "'|<value>value|<body>body}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "value", op->value);
    link(op_id, "body", op->body);
}

void IRPrinterDot::visit(const AssertStmt *op) {
    op->condition.accept(this);
    op->message.accept(this);
    std::string def = "[ label = \"{{<port>AssertStmt}|{<condition>condition|<message>message}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "condition", op->condition);
    link(op_id, "message", op->message);
}

void IRPrinterDot::visit(const ProducerConsumer *op) {
    op->body.accept(this);
    std::string def = "[ label = \"{{<port>ProducerConsumer}|{name: '" + op->name + "'|is_producer: " + std::to_string(op->is_producer) + "|<body>body}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "body", op->body);
}

void IRPrinterDot::visit(const For *op) {
    op->min.accept(this);
    op->extent.accept(this);
    op->body.accept(this);
    /*
     * [
     *    label = "{{For}|{<name>name: 'func_vadd.s0.i.i_inner'|<min>min|<extent>extent|<body>body}}"
     *    shape = "record"
     * ];
     */
    std::string def = "[ label = \"{{<port>For}|{name: '" + op->name +
                      "'|<min>min|<extent>extent|<body>body}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "min", op->min);
    link(op_id, "extent", op->extent);
    link(op_id, "body", op->body);
}

void IRPrinterDot::visit(const Acquire *op) {
    op->semaphore.accept(this);
    op->count.accept(this);
    op->body.accept(this);
    std::string def = "[ label = \"{{<port>Acquire}|{<semaphore>semaphore|<count>count|<body>body}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "semaphore", op->semaphore);
    link(op_id, "count", op->count);
    link(op_id, "body", op->body);
}

void IRPrinterDot::visit(const Store *op) {
    op->predicate.accept(this);
    op->value.accept(this);
    op->index.accept(this);
    std::string def = "[ label = \"{{<port>Store}|{name: '" + op->name + "'|<predicate>predicate|<value>value|<index>index}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "predicate", op->predicate);
    link(op_id, "value", op->value);
    link(op_id, "index", op->index);
}

void IRPrinterDot::visit(const Provide *op) {
    for (size_t i = 0; i < op->values.size(); i++) {
        op->values[i].accept(this);
    }
    for (size_t i = 0; i < op->args.size(); i++) {
        op->args[i].accept(this);
    }
    std::string def = "[ label = \"{{<port>Provide}|{name: '" + op->name + "'|<value>value|<args>args}}\" shape = \"record\" ];";
    define(op, def);
}

void IRPrinterDot::visit(const Allocate *op) {
    for (size_t i = 0; i < op->extents.size(); i++) {
        op->extents[i].accept(this);
    }
    op->condition.accept(this);
    if (op->new_expr.defined()) {
        op->new_expr.accept(this);
    }
    op->body.accept(this);
    std::string def = "[ label = \"{{<port>Allocate}|{name: '" + op->name + "'|<extents>extents|<condition>condition}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "condition", op->condition);
}

void IRPrinterDot::visit(const Free *op) {
    std::string def = "[ label = \"{{<port>Free}|{name: '" + op->name + "'}}\" shape = \"record\" ];";
    define(op, def);
}

void IRPrinterDot::visit(const Realize *op) {
    for (size_t i = 0; i < op->bounds.size(); i++) {
        op->bounds[i].min.accept(this);
        op->bounds[i].extent.accept(this);
    }
    op->condition.accept(this);
    op->body.accept(this);
    std::string def = "[ label = \"{{<port>Realize}|{name: '" + op->name + "'|<condition>condition|<body>body}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "condition", op->condition);
    link(op_id, "body", op->body);
}

void IRPrinterDot::visit(const Prefetch *op) {
    for (size_t i = 0; i < op->bounds.size(); i++) {
        op->bounds[i].min.accept(this);
        op->bounds[i].extent.accept(this);
    }
    op->condition.accept(this);
    op->body.accept(this);
    std::string def = "[ label = \"{{<port>Prefetch}|{name: '" + op->name + "'|<condition>condition|<body>body}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "condition", op->condition);
    link(op_id, "body", op->body);
}

void IRPrinterDot::visit(const Block *op) {
    op->first.accept(this);
    if (op->rest.defined()) {
        op->rest.accept(this);
    }
    std::string def = "[ label = \"{{<port>Block}|{<first>first|<rest>rest}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "first", op->first);
    link(op_id, "rest", op->rest);
}

void IRPrinterDot::visit(const Fork *op) {
    op->first.accept(this);
    if (op->rest.defined()) {
        op->rest.accept(this);
    }
    std::string def = "[ label = \"{{<port>Fork}|{<first>first|<rest>rest}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "first", op->first);
    link(op_id, "rest", op->rest);
}

void IRPrinterDot::visit(const IfThenElse *op) {
    std::string def = "[ label = \"{{<port>IfThenElse}|{<condition>condition|<then_case>then_case";
    op->condition.accept(this);
    op->then_case.accept(this);
    if (op->else_case.defined()) {
        op->else_case.accept(this);
        def += "|<else_case>else_case";
    }
    def += "}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "condition", op->condition);
    link(op_id, "then_case", op->then_case);
    if (op->else_case.defined())
        link(op_id, "else_case", op->else_case);
}

void IRPrinterDot::visit(const Evaluate *op) {
    op->value.accept(this);
    std::string def = "[ label = \"{{<port>Evaluate}|{<value>value}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "value", op->value);
}

void IRPrinterDot::visit(const Shuffle *op) {
    std::string def = "[ label = \"{{<port>Shuffle}";
    for (size_t i = 0; i < op->vectors.size(); i++) {
        def += "|<vector_" + std::to_string(i) +">Expr";
    }
    def += "}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    int id = 0;
    for (Expr i : op->vectors) {
        i.accept(this);
        link(op_id, "vector_" + std::to_string(id), i);
        id++;
    }
}

void IRPrinterDot::visit(const VectorReduce *op) {
    op->value.accept(this);
    std::string def = "[ label = \"{{<port>VectorReduce}|{op: " + std::to_string(op->op) + "|<value>value}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "value", op->value);
}

void IRPrinterDot::visit(const Atomic *op) {
    op->body.accept(this);
    std::string def = "[ label = \"{{<port>Atomic}|{producer_name: '" + op->producer_name + "'|mutex_name: '" + op->mutex_name + "'|<body>body}}\" shape = \"record\" ];";
    int op_id = define(op, def);
    link(op_id, "body", op->body);
}

}
}
