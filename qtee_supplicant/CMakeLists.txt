project(qtee_supplicant C)

# ''Packages''.

# Append modules directory.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(QCBOR_DIR_HINT "" CACHE PATH "Hint path for QCBOR directory")

find_package(QCBOR REQUIRED)
if(NOT QCBOR_FOUND)
	message(FATAL_ERROR "QCBOR not found")
endif()

include_directories(${QCBOR_INCLUDE_DIRS})

find_package(Threads REQUIRED)
if(NOT THREADS_FOUND)
        message(FATAL_ERROR "Threads not found")
endif()

# ''Build IDL Headers''.

set (IDLS
	idl/CRegisterListenerCBO
	idl/IClientEnv
	idl/ICredentials
	idl/IIO
	idl/IListenerCBO
	idl/IMemRegion
	idl/IRegisterListenerCBO
)

foreach(IDL ${IDLS})
	foreach(VARIANT "" "--skel" )
		if (VARIANT)
			set(INVOKE _invoke)
		else()
			set(INVOKE "")
		endif()

		set(IDL_OUT ${CMAKE_CURRENT_SOURCE_DIR}/${IDL}${INVOKE}.h)
		set(INPUT ${CMAKE_CURRENT_SOURCE_DIR}/${IDL}.idl)

		add_custom_command(
			OUTPUT  ${IDL_OUT}
			DEPENDS ${INPUT}
			COMMAND ${MINKIDLC_BIN_DIR}/minkidlc ${INPUT} -o ${IDL_OUT} ${VARIANT}
		)

		list(APPEND IDL_OUT_LIST ${IDL_OUT})
	endforeach()
endforeach()

# A custom target to build the MINK-HEADERS which is always out of date.
add_custom_target(
        ${PROJECT_NAME}_MINKHEADERS ALL
        DEPENDS ${IDL_OUT_LIST}
)

# ''Source files''.

set(SRC
	src/qtee_supplicant.c
	src/listener_mngr.c
	src/CListenerCBO.c
)

# ''Built binary''.

add_executable(${PROJECT_NAME} ${SRC})

# The binary depends on the MINK-IDLs
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_MINKHEADERS)

# ''Optional Flags''.

if(BUILD_TIME_LISTENER)
	target_compile_definitions(${PROJECT_NAME}
		PRIVATE -DTIME_LISTENER)
endif()

if(BUILD_TA_AUTOLOAD_LISTENER)
	target_compile_definitions(${PROJECT_NAME}
		PRIVATE -DTA_AUTOLOAD_LISTENER)
endif()

if(BUILD_FS_LISTENER)
	target_compile_definitions(${PROJECT_NAME}
		PRIVATE -DFS_LISTENER)
endif()

if(BUILD_GPFS_LISTENER)
	target_compile_definitions(${PROJECT_NAME}
		PRIVATE -DGPFS_LISTENER)
endif()

# ''Headers and dependencies''.

target_include_directories(${PROJECT_NAME}
	PRIVATE src
	PRIVATE include
	PRIVATE idl
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE minkadaptor
	PRIVATE ${QCBOR_LIBRARIES}
	PRIVATE dl
)

install(TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_INSTALL_BINDIR}")
