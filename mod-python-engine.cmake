message(STATUS "Configuring mod-python-engine...")

# Dependencies
find_package(Python3 3.10 COMPONENTS Interpreter Development REQUIRED)
set(BOOST_PYTHON_COMPONENT "python${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR}")
find_package(Boost REQUIRED COMPONENTS ${BOOST_PYTHON_COMPONENT})

# Create an interface library for Python/Boost
add_library(pyeng-interface INTERFACE)
target_include_directories(pyeng-interface
  INTERFACE
    ${Python3_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)
target_link_libraries(pyeng-interface
  INTERFACE
    ${Python3_LIBRARIES}
    ${Boost_LIBRARIES}
)

# Apply Python/Boost to main modules target
target_link_libraries(modules PRIVATE pyeng-interface)

# Apply Python/Boost to ALL dynamic modules
if(DYNAMIC_SCRIPT_MODULE_PROJECTS)
  foreach(DYNAMIC_MODULE ${DYNAMIC_SCRIPT_MODULE_PROJECTS})
    if(TARGET ${DYNAMIC_MODULE})
      target_link_libraries(${DYNAMIC_MODULE} PRIVATE pyeng-interface)
    endif()
  endforeach()
endif()

# Compile Options (RTTI is required for Boost.Python)
if(MSVC)
  target_compile_options(modules PRIVATE "/GR" "/EHsc")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(modules PRIVATE "-frtti")
endif()

# Boost.Python and modern Python C API require at least C++17
target_compile_features(modules PRIVATE cxx_std_17)
