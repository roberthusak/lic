#ifndef LIC_INTERPRETER
#define LIC_INTERPRETER

#include "CallStackFrame.h"
#include "loader/AssemblyLoader.h"

namespace lic
{

class Interpreter
{
public:
    Interpreter(const std::string& assembly, std::istream& in, std::ostream& out, std::ostream& log);

    gsl::span<Assembly> Assemblies();

    void Run(MethodDefinition& method);

private:
    std::istream& in;
    std::ostream& out;
    std::ostream& log;

    AssemblyLoader loader;
    std::vector<CallStackFrame> callStack;
	CallStackFrame* frame;
    const gsl::byte* ip;

    void AddCall(MethodDefinition& method, gsl::span<TypedValue> args, Opcode* returnAddress);
    void PerformEvaluationLoop();

    Opcode ReadOpcode();
    LongOpcodeSuffix ReadOpcodeSuffix();
    int8_t ReadInt8();
    int32_t ReadInt32();

	void LoadArg(size_t index);
	void LoadLocal(size_t index);
	void StoreLocal(size_t index);
	void LoadInt32Constant(int32_t constant);

    bool PopCompareInt32(std::function<bool(int32_t, int32_t)> op);
    bool PopBool();
    void PushBool(bool value);
    void Branch(bool conditionResult, int32_t offset);
};

}

#endif // !LIC_INTERPRETER
