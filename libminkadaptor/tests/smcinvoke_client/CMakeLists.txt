project(smcinvoke_client CXX)

# ''CXX configuration''.

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ''Build IDL Headers''.

set (IDLS
	idl/CAppLoader
	idl/CDiagnostics
	idl/IAppController
	idl/IAppLegacyTest
	idl/IAppLoader
	idl/IClientEnv
	idl/ICredentials
	idl/IDiagnostics
	idl/IIO
	idl/IOpener
	idl/ITestCBack
	idl/ITestMemManager
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
			COMMAND ${MINKIDLC_BIN_DIR}/idlc ${INPUT} -o ${IDL_OUT} ${VARIANT}
		)

		list(APPEND IDL_OUT_LIST ${IDL_OUT})
	endforeach()
endforeach()

# A custom target to build the MINK-HEADERS which is always out of date.
add_custom_target(
        ${PROJECT_NAME}_MINKHEADERS ALL
        DEPENDS ${IDL_OUT_LIST}
)

# ''Build binary''.

set(SRC
	src/smcinvoke_client.cpp
	src/CTestCallable.cpp
	src/CIO.c
)

add_executable(${PROJECT_NAME} ${SRC})

# The binary depends on the MINK-IDLs
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_MINKHEADERS)

# ''Headers and dependencies''.

target_include_directories(${PROJECT_NAME}
	PRIVATE src
	PRIVATE include
	PRIVATE idl
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE minkadaptor
)

install(TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_INSTALL_BINDIR}")
