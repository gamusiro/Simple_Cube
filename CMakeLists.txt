cmake_minimum_required(VERSION 3.22.0)
project(BulletPhysicsApp)

# subdirectories
add_subdirectory(vendor/bullet3)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/entt)
add_subdirectory(vendor/glad)

# project files
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/app/*.cpp
    ${CMAKE_SOURCE_DIR}/app/*.h
)

# build project
add_executable(${PROJECT_NAME} ${SOURCES})

# define
target_compile_definitions(${PROJECT_NAME} PUBLIC
    GLFW_INCLUDE_NONE
    GLM_ENABLE_EXPERIMENTAL
)

# include external
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/app/include
    ${CMAKE_SOURCE_DIR}/vendor/bullet3/src
    ${CMAKE_SOURCE_DIR}/vendor/entt/src
    ${CMAKE_SOURCE_DIR}/vendor/glm
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/vendor/glad/include
)

# link libraries
if(WIN32)
    target_link_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}/build/lib/${CONFIG}
    )

    target_link_libraries(${PROJECT_NAME} PUBLIC
        BulletDynamics_$<CONFIG>
        BulletCollision_$<CONFIG>
        LinearMath_$<CONFIG>
    )
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC
        BulletDynamics
        BulletCollision
        LinearMath
    )
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC
    glfw
    EnTT
    glm
    GLAD
)

# Asset Directory
set(ASSET_DIR ${CMAKE_SOURCE_DIR}/assets)

# Outpud Directory
set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/assets)

# Get asset files
file(GLOB_RECURSE ASSET_FILES
    ${ASSET_DIR}/*
)

# command copy
foreach(ASSET_FILE ${ASSET_FILES})
    # relative path
    file(RELATIVE_PATH RELATIVE_PATH ${ASSET_DIR} ${ASSET_FILE})
    set(DESTINATION_PATH "${OUTPUT_DIR}/${RELATIVE_PATH}")
    message(STATUS ${DESTINATION_PATH})

    # create dir & copy file
    add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
        COMMAND ${CMAKE_COMMAND} -E copy ${ASSET_FILE} ${DESTINATION_PATH}
    )
endforeach()