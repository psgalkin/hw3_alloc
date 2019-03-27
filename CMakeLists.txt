CMAKE_MINIMUM_REQUIRED ( VERSION 3.2 )

PROJECT ( alloc VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}) 

add_executable ( alloc hw3.cpp )

set (container Container.h)
add_library(container INTERFACE)
target_include_directories(container INTERFACE include/)

add_library(allocator INTERFACE Map_allocator.h)
target_include_directories(allocator INTERFACE include/)

set_target_properties ( alloc PROPERTIES
    COMPILE_FLAGS -pthread 
    LINK_FLAGS -pthread
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_link_libraries(alloc
    container
    allocator
)

target_link_libraries(container
    allocator
)

install(TARGETS alloc RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT ps.galkin@yandex.ru)

include(CPack)
