// Simple Visitor Pattern example

class Instance;
class Netlist;

void DoNothingC(Instance *) {}

void
traverse_netlist_c(Netlist * n,
                   void (*v)(Instance *) = DoNothingC) {
    // ...
    // every time we encounter an instance, call the visitor
    Instance * inst;
    v(inst);           // always calls this pointer
}

struct DoNothingInstanceVisitor {
    void operator()(Instance *) const {}
};

template<typename InstanceVisitor = DoNothingInstanceVisitor>
void
traverse_netlist(Netlist * n,
                 InstanceVisitor v = InstanceVisitor()) {
    // ...
    // every time we encounter an instance, call the visitor
    Instance * inst;  // = whatever
    v(inst);          // optimized away for DoNothingInstanceVisitor
}
