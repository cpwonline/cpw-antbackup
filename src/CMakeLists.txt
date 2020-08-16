
include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_search_module(SQLITE3 sqlite3)

set(
	BACKUPS_SRC
	backups.cpp
	${HEADER}/backups.h
)
set(
	MENU_SRC
	menu.cpp
	${HEADER}/menu.h
)

add_library(BACKUPS SHARED ${BACKUPS_SRC})
add_library(MENU SHARED ${MENU_SRC})


include_directories(BACKUPS PUBLIC ${SQLITE3_INCLUDE_DIRS})
link_directories(${CPPUNIT_LIBRARY_DIRS})
target_compile_options(BACKUPS PUBLIC ${SQLITE3_CFLAGS_OTHERS})

target_link_libraries(BACKUPS ${SQLITE3_LIBRARIES})


add_executable(
	${PROJECT_NAME}
	main.cpp
)
target_link_libraries(${PROJECT_NAME} PUBLIC BACKUPS MENU)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    "${PROJECT_BINARY_DIR}"
)

# Install targets

install(TARGETS BACKUPS DESTINATION lib/cpw-antbackup)
install(FILES "${HEADER}/backups.h" DESTINATION include/cpw-antbackup)

install(TARGETS MENU DESTINATION lib/cpw-antbackup)
install(FILES "${HEADER}/menu.h" DESTINATION include/cpw-antbackup)
