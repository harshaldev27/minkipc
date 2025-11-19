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

if (CFG_USE_PKGCONFIG)
	find_package(PkgConfig)
	if (PKG_CONFIG_FOUND)
		pkg_check_modules(SYSTEMD REQUIRED IMPORTED_TARGET systemd)
		if (SYSTEMD_FOUND AND CFG_ENABLE_SYSTEMD)
			pkg_get_variable(UNIT_DIR systemd systemd_system_unit_dir)
			set(SYSTEMD_UNIT_DIR "${UNIT_DIR}" CACHE PATH "Location of systemd unit files.")
			unset(UNIT_DIR)
		endif()
	endif()
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_INSTALL_BINDIR}")
if (CFG_ENABLE_SYSTEMD)
	configure_file(qteesupplicant.service.in qteesupplicant.service @ONLY)
	install(FILES "${CMAKE_CURRENT_BINARY_DIR}/qteesupplicant.service" DESTINATION "${SYSTEMD_UNIT_DIR}")
endif()
