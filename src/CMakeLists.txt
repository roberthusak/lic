include_directories(.)

set(LIC_SOURCES
    lic.cpp
	format/ClrMetadataFormat.cpp
	loader/Assembly.cpp
	loader/AssemblyLoader.cpp
)

add_executable(lic ${LIC_SOURCES})