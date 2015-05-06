cmake_minimum_required(VERSION 2.8)

find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)


set(SQUARE_MODULE_SRCS "${CMAKE_SOURCE_DIR}/python/square_module.c")
set(SQUARE_INC_DIRS "${CMAKE_SOURCE_DIR}/include")
set(SQUARE_LIB_DIRS "${CMAKE_BINARY_DIR}/src")
set(SQUARE_LIBS square)

#configure_file(setup.py.in setup.py)

set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in")
set(SETUP_PY "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
set(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/build/timestamp")

configure_file(${SETUP_PY_IN} ${SETUP_PY})

add_custom_command(OUTPUT ${OUTPUT}
    COMMAND ${PYTHON_EXECUTABLE} ${SETUP_PY} build
    COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT}
    DEPENDS square)

add_custom_target(target ALL DEPENDS ${OUTPUT})

install(CODE "execute_process(COMMAND ${PYTHON_EXECUTABLE} ${SETUP_PY} install --home=${CMAKE_INSTALL_PREFIX})")
