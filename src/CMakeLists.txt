include_directories(.)

set(LIC_SOURCES
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

add_library(licl ${LIC_SOURCES})

add_executable(lic lic.cpp)
target_link_libraries(lic licl)

add_executable(tests tests.cpp)
target_link_libraries(tests licl)
