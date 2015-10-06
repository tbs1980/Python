cmake_minimum_required(VERSION 2.8)

include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
PYTHON_ADD_MODULE(hello hello.cpp)
target_link_libraries(hello ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
FILE(COPY hello.py DESTINATION .)
