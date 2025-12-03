message(STATUS "Configuring mod-python-engine...")

# Dependencies
find_package(Python3 3.10 COMPONENTS Interpreter Development REQUIRED)
set(BOOST_PYTHON_COMPONENT "python${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR}")
find_package(Boost REQUIRED COMPONENTS ${BOOST_PYTHON_COMPONENT})

# Link Dependencies to the main 'modules' target
target_link_libraries(modules PUBLIC
  ${Python3_LIBRARIES}
  ${Boost_LIBRARIES}
)

# Add Include Directories
target_include_directories(modules PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/src
  ${CMAKE_CURRENT_LIST_DIR}/src/Bindings
  ${CMAKE_CURRENT_LIST_DIR}/src/Bindings/Adapters
  ${CMAKE_CURRENT_LIST_DIR}/src/Bindings/Constants
  ${CMAKE_CURRENT_LIST_DIR}/src/Bindings/Exports
  ${CMAKE_CURRENT_LIST_DIR}/src/Bindings/Functions
  ${CMAKE_CURRENT_LIST_DIR}/src/Hooks
  ${CMAKE_CURRENT_LIST_DIR}/src/Scripts
  ${Python3_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

# Definitions
target_compile_definitions(modules PRIVATE -D_MOD_PYTHON_ENABLED)

# Compile Options (RTTI is required for Boost.Python)
if(MSVC)
  target_compile_options(modules PRIVATE "/GR" "/EHsc")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(modules PRIVATE "-frtti")
endif()

# Ensure C++17
# AC usually defaults to 17 or 20, but Boost.Python might need modern standards
target_compile_features(modules PRIVATE cxx_std_17)
