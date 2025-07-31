project(qtee_supplicant C)

# ''Source files''.

set(SRC
	src/qtee_supplicant.c
	src/listener_mngr.c
	src/listener_mngr.h
)

# ''Built binary''.

add_executable(${PROJECT_NAME} ${SRC})

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

target_link_libraries(${PROJECT_NAME}
	PRIVATE dl
)

install(TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_INSTALL_BINDIR}")
