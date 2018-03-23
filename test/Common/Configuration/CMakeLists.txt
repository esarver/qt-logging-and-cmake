set(
   testname
   ConfigurationManager_Test
)

set(
    objects
    $<TARGET_OBJECTS:Common-ConfigurationManager>
)

add_executable(
    ${testname}
    ${objects}
    ConfigurationManager_Test.cpp
)

# Link the libraries to target.
target_link_libraries(
    ${testname}
    Qt5::Core 
    Qt5::Test
)

add_test(${testname} ${testname}) 
