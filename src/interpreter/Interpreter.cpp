#include "Interpreter.h"

#include "types/NumberType.h"

#define DEBUG

// Simple conditional logging
#ifdef DEBUG

#define LOG(command) command

#else

#define LOG(command) 

#endif // DEBUG

using namespace std;
using namespace gsl;
using namespace lic;

lic::Interpreter::Interpreter(const std::string& assembly, std::istream & in, std::ostream & out, std::ostream& log)
    : in{ in }, out{ out }, log{ log }, ip{ nullptr }, frame{ nullptr }
{
    this->loader.LoadAssembly(assembly);
}

gsl::span<Assembly> lic::Interpreter::Assemblies()
{
    return this->loader.Assemblies();
}

void lic::Interpreter::Run(MethodDefinition& method)
{

    // TODO: Check that the method has no parameters

    this->AddCall(method, span<TypedValue>(), nullptr);
    this->PerformEvaluationLoop();
}

void lic::Interpreter::AddCall(MethodDefinition& method, gsl::span<TypedValue> args, Opcode* returnAddress)
{
    LOG(this->log << "Calling method " << method.Name() << "..." << endl);

    this->callStack.emplace_back(method, args, returnAddress);

    const byte* header = method.Code();
    uint8_t headerFormat = *reinterpret_cast<const uint8_t*>(header) & MethodHeaderFormatMask;
    if (headerFormat == (uint8_t)HeaderFormat::Tiny)
    {
        LOG(this->log << "Tiny header format" << endl);
        this->ip = header + 1;
    }
    else if (headerFormat == (uint8_t)HeaderFormat::Fat)
    {
        LOG(this->log << "Fat header format" << endl);
        this->ip = header + 12;
    }
    else
    {
        throw exception("Invalid header format");
    }

	this->frame = &this->callStack.back();
}

void lic::Interpreter::PerformEvaluationLoop()
{
    while (true)
    {
        auto op = this->ReadOpcode();

        switch (op)
        {
            case lic::Opcode::Nop:
            case lic::Opcode::Break:
                break;

            case lic::Opcode::Ldarg_0:
				this->LoadArg(0);
				break;
            case lic::Opcode::Ldarg_1:
				this->LoadArg(1);
				break;
            case lic::Opcode::Ldarg_2:
				this->LoadArg(2);
				break;

            case lic::Opcode::Ldloc_0:
				this->LoadLocal(0);
				break;
            case lic::Opcode::Ldloc_1:
				this->LoadLocal(1);
				break;
            case lic::Opcode::Ldloc_2:
				this->LoadLocal(2);
				break;
            case lic::Opcode::Ldloc_3:
				this->LoadLocal(3);
				break;

            case lic::Opcode::Stloc_0:
				this->StoreLocal(0);
				break;
            case lic::Opcode::Stloc_1:
				this->StoreLocal(0);
				break;
            case lic::Opcode::Stloc_2:
				this->StoreLocal(0);
				break;
            case lic::Opcode::Stloc_3:
				this->StoreLocal(0);
				break;

			case lic::Opcode::Ldc_I4_M1:
				this->LoadInt32Constant(-1);
				break;
			case lic::Opcode::Ldc_I4_0:
				this->LoadInt32Constant(0);
				break;
			case lic::Opcode::Ldc_I4_1:
				this->LoadInt32Constant(1);
				break;
			case lic::Opcode::Ldc_I4_2:
				this->LoadInt32Constant(2);
				break;
			case lic::Opcode::Ldc_I4_3:
				this->LoadInt32Constant(3);
				break;
			case lic::Opcode::Ldc_I4_4:
				this->LoadInt32Constant(4);
				break;
			case lic::Opcode::Ldc_I4_5:
				this->LoadInt32Constant(5);
				break;
			case lic::Opcode::Ldc_I4_6:
				this->LoadInt32Constant(6);
				break;
			case lic::Opcode::Ldc_I4_7:
				this->LoadInt32Constant(7);
				break;
			case lic::Opcode::Ldc_I4_8:
				this->LoadInt32Constant(8);
				break;

			case lic::Opcode::Ldc_I4_S:
			case lic::Opcode::Ldc_I4:
			case lic::Opcode::Ldc_I8:
			case lic::Opcode::Ldc_R4:
			case lic::Opcode::Ldc_R8:
            case lic::Opcode::Ldarg_S:
            case lic::Opcode::Ldarga_S:
            case lic::Opcode::Starg_S:
            case lic::Opcode::Ldloc_S:
            case lic::Opcode::Ldloca_S:
            case lic::Opcode::Stloc_S:
            case lic::Opcode::Ldnull:
            case lic::Opcode::Dup:
            case lic::Opcode::Pop:
            case lic::Opcode::Jmp:
            case lic::Opcode::Call:
            case lic::Opcode::Calli:
            case lic::Opcode::Ret:
            case lic::Opcode::Br_S:
            case lic::Opcode::Brfalse_S:
            case lic::Opcode::Brtrue_S:
            case lic::Opcode::Beq_S:
            case lic::Opcode::Bge_S:
            case lic::Opcode::Bgt_S:
            case lic::Opcode::Ble_S:
            case lic::Opcode::Blt_S:
            case lic::Opcode::Bne_Un_S:
            case lic::Opcode::Bge_Un_S:
            case lic::Opcode::Bgt_Un_S:
            case lic::Opcode::Ble_Un_S:
            case lic::Opcode::Blt_Un_S:
            case lic::Opcode::Br:
            case lic::Opcode::Brfalse:
            case lic::Opcode::Brtrue:
            case lic::Opcode::Beq:
            case lic::Opcode::Bge:
            case lic::Opcode::Bgt:
            case lic::Opcode::Ble:
            case lic::Opcode::Blt:
            case lic::Opcode::Bne_Un:
            case lic::Opcode::Bge_Un:
            case lic::Opcode::Bgt_Un:
            case lic::Opcode::Ble_Un:
            case lic::Opcode::Blt_Un:
            case lic::Opcode::Switch:
            case lic::Opcode::Ldind_I1:
            case lic::Opcode::Ldind_U1:
            case lic::Opcode::Ldind_I2:
            case lic::Opcode::Ldind_U2:
            case lic::Opcode::Ldind_I4:
            case lic::Opcode::Ldind_U4:
            case lic::Opcode::Ldind_I8:
            case lic::Opcode::Ldind_I:
            case lic::Opcode::Ldind_R4:
            case lic::Opcode::Ldind_R8:
            case lic::Opcode::Ldind_Ref:
            case lic::Opcode::Stind_Ref:
            case lic::Opcode::Stind_I1:
            case lic::Opcode::Stind_I2:
            case lic::Opcode::Stind_I4:
            case lic::Opcode::Stind_I8:
            case lic::Opcode::Stind_R4:
            case lic::Opcode::Stind_R8:
            case lic::Opcode::Add:
            case lic::Opcode::Sub:
            case lic::Opcode::Mul:
            case lic::Opcode::Div:
            case lic::Opcode::Div_Un:
            case lic::Opcode::Rem:
            case lic::Opcode::Rem_Un:
            case lic::Opcode::And:
            case lic::Opcode::Or:
            case lic::Opcode::Xor:
            case lic::Opcode::Shl:
            case lic::Opcode::Shr:
            case lic::Opcode::Shr_Un:
            case lic::Opcode::Neg:
            case lic::Opcode::Not:
            case lic::Opcode::Conv_I1:
            case lic::Opcode::Conv_I2:
            case lic::Opcode::Conv_I4:
            case lic::Opcode::Conv_I8:
            case lic::Opcode::Conv_R4:
            case lic::Opcode::Conv_R8:
            case lic::Opcode::Conv_U4:
            case lic::Opcode::Conv_U8:
            case lic::Opcode::Callvirt:
            case lic::Opcode::Cpobj:
            case lic::Opcode::Ldobj:
            case lic::Opcode::Ldstr:
            case lic::Opcode::Newobj:
            case lic::Opcode::Castclass:
            case lic::Opcode::Isinst:
            case lic::Opcode::Conv_R_Un:
            case lic::Opcode::Unbox:
            case lic::Opcode::Throw:
            case lic::Opcode::Ldfld:
            case lic::Opcode::Ldflda:
            case lic::Opcode::Stfld:
            case lic::Opcode::Ldsfld:
            case lic::Opcode::Ldsflda:
            case lic::Opcode::Stsfld:
            case lic::Opcode::Stobj:
            case lic::Opcode::Conv_Ovf_I1_Un:
            case lic::Opcode::Conv_Ovf_I2_Un:
            case lic::Opcode::Conv_Ovf_I4_Un:
            case lic::Opcode::Conv_Ovf_I8_Un:
            case lic::Opcode::Conv_Ovf_U1_Un:
            case lic::Opcode::Conv_Ovf_U2_Un:
            case lic::Opcode::Conv_Ovf_U4_Un:
            case lic::Opcode::Conv_Ovf_U8_Un:
            case lic::Opcode::Conv_Ovf_I_Un:
            case lic::Opcode::Conv_Ovf_U_Un:
            case lic::Opcode::Box:
            case lic::Opcode::Newarr:
            case lic::Opcode::Ldlen:
            case lic::Opcode::Ldelema:
            case lic::Opcode::Ldelem_I1:
            case lic::Opcode::Ldelem_U1:
            case lic::Opcode::Ldelem_I2:
            case lic::Opcode::Ldelem_U2:
            case lic::Opcode::Ldelem_I4:
            case lic::Opcode::Ldelem_U4:
            case lic::Opcode::Ldelem_I8:
            case lic::Opcode::Ldelem_I:
            case lic::Opcode::Ldelem_R4:
            case lic::Opcode::Ldelem_R8:
            case lic::Opcode::Ldelem_Ref:
            case lic::Opcode::Stelem_I:
            case lic::Opcode::Stelem_I1:
            case lic::Opcode::Stelem_I2:
            case lic::Opcode::Stelem_I4:
            case lic::Opcode::Stelem_I8:
            case lic::Opcode::Stelem_R4:
            case lic::Opcode::Stelem_R8:
            case lic::Opcode::Stelem_Ref:
            case lic::Opcode::Conv_Ovf_I1:
            case lic::Opcode::Conv_Ovf_U1:
            case lic::Opcode::Conv_Ovf_I2:
            case lic::Opcode::Conv_Ovf_U2:
            case lic::Opcode::Conv_Ovf_I4:
            case lic::Opcode::Conv_Ovf_U4:
            case lic::Opcode::Conv_Ovf_I8:
            case lic::Opcode::Conv_Ovf_U8:
            case lic::Opcode::Refanyval:
            case lic::Opcode::Ckfinite:
            case lic::Opcode::Mkrefany:
            case lic::Opcode::Ldtoken:
            case lic::Opcode::Conv_U2:
            case lic::Opcode::Conv_U1:
            case lic::Opcode::Conv_I:
            case lic::Opcode::Conv_Ovf_I:
            case lic::Opcode::Conv_Ovf_U:
            case lic::Opcode::Add_Ovf:
            case lic::Opcode::Add_Ovf_Un:
            case lic::Opcode::Mul_Ovf:
            case lic::Opcode::Mul_Ovf_Un:
            case lic::Opcode::Sub_Ovf:
            case lic::Opcode::Sub_Ovf_Un:
            case lic::Opcode::Endfinally:
            case lic::Opcode::Leave:
            case lic::Opcode::Leave_S:
            case lic::Opcode::Stind_I:
            case lic::Opcode::Conv_U:
                throw exception("Operation not implemented");

            case lic::Opcode::LongOpcodePrefix:
            {
                auto suffix = this->ReadOpcodeSuffix();
                switch (suffix)
                {
                    case lic::LongOpcodeSuffix::Arglist:
                    case lic::LongOpcodeSuffix::Ceq:
                    case lic::LongOpcodeSuffix::Cgt:
                    case lic::LongOpcodeSuffix::Cgt_Un:
                    case lic::LongOpcodeSuffix::Clt:
                    case lic::LongOpcodeSuffix::Clt_Un:
                    case lic::LongOpcodeSuffix::Ldftn:
                    case lic::LongOpcodeSuffix::Ldvirtftn:
                    case lic::LongOpcodeSuffix::Ldarg:
                    case lic::LongOpcodeSuffix::Ldarga:
                    case lic::LongOpcodeSuffix::Starg:
                    case lic::LongOpcodeSuffix::Ldloc:
                    case lic::LongOpcodeSuffix::Ldloca:
                    case lic::LongOpcodeSuffix::Stloc:
                    case lic::LongOpcodeSuffix::Localloc:
                    case lic::LongOpcodeSuffix::Endfilter:
                    case lic::LongOpcodeSuffix::Unaligned_:
                    case lic::LongOpcodeSuffix::Volatile_:
                    case lic::LongOpcodeSuffix::Tail_:
                    case lic::LongOpcodeSuffix::Initobj:
                    case lic::LongOpcodeSuffix::Cpblk:
                    case lic::LongOpcodeSuffix::Initblk:
                    case lic::LongOpcodeSuffix::Rethrow:
                    case lic::LongOpcodeSuffix::Sizeof:
                    case lic::LongOpcodeSuffix::Refanytype:
                    case lic::LongOpcodeSuffix::InvalidOpcode:
                    default:
                        throw exception("Operation not implemented");
                }
            }

            default:
                throw exception("Operation not implemented");
        }

        LOG(this->log << endl);
    }
}

Opcode lic::Interpreter::ReadOpcode()
{
    auto opcode = *reinterpret_cast<const Opcode*>(this->ip);
    this->ip++;

    if (opcode != Opcode::LongOpcodePrefix)
    {
        LOG(this->log << OpcodeName(opcode) << ' ');
    }

    return opcode;
}

LongOpcodeSuffix lic::Interpreter::ReadOpcodeSuffix()
{
    auto suffix = *reinterpret_cast<const LongOpcodeSuffix*>(this->ip);
    this->ip++;

    LOG(this->log << OpcodeName(Opcode::LongOpcodePrefix, suffix) << ' ');

    return suffix;
}

void lic::Interpreter::LoadArg(size_t index)
{
	auto& arg = this->frame->Arg(index);
	this->frame->Stack().Push(arg);
}

void lic::Interpreter::LoadLocal(size_t index)
{
	auto& local = this->frame->Local(index);
	this->frame->Stack().Push(local);
}

void lic::Interpreter::StoreLocal(size_t index)
{
	this->frame->Local(index) = this->frame->Stack().Top();
	this->frame->Stack().Pop();
}

void lic::Interpreter::LoadInt32Constant(int32_t constant)
{
	TypedValue val;
	val.type = &NumberType::Instance();
	NumberType::StoreConstant(constant, &val.data[0]);
	this->frame->Stack().Push(val);
}
