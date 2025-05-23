cmake_minimum_required(VERSION 3.4)
project(minkipc)

# Build Mink TEEC library
option(BUILD_MINKTEEC "Build MinkTEEC" TRUE)

option(BUILD_UNITTEST "Build unittest" FALSE)

include(GNUInstallDirs)

set(MINKIDLC_BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/minkidlc)

file(DOWNLOAD
  https://github.com/quic/mink-idl-compiler/releases/download/v0.2.0/idlc
  ${MINKIDLC_BIN_DIR}/minkidlc
)

file(CHMOD ${MINKIDLC_BIN_DIR}/minkidlc PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ)

add_compile_options(
	-Wall -Wextra -Werror -Wshadow -Wcast-align
	-Wmissing-declarations -Wformat-security -Wmissing-noreturn
	-Wdeprecated -fPIC
)

add_subdirectory(libminkadaptor)

add_subdirectory(qtee_supplicant)
add_subdirectory(listeners/libdrmtime)
add_subdirectory(listeners/libtaautoload)

if (BUILD_MINKTEEC)
	add_subdirectory(libminkteec)
endif()

