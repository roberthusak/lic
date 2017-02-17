include_directories(.)

set(LIC_SOURCES
    lic.cpp
	format/ClrMetadataFormat.cpp
	format/Opcodes.cpp
	interpreter/CallStackFrame.cpp
	interpreter/EvaluationStack.cpp
	interpreter/Interpreter.cpp
	loader/Assembly.cpp
	loader/AssemblyLoader.cpp
	loader/Metadata.cpp
	loader/MethodDefinition.cpp
	loader/TypeDefinition.cpp
	types/NumberType.cpp
	types/RuntimeType.cpp
)

add_executable(lic ${LIC_SOURCES})