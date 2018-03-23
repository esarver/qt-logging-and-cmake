set(
   testname
   FileLogger_Test
)

set(
    objects
    $<TARGET_OBJECTS:Common-Logger>
)

add_executable(
    ${testname}
    ${objects}
    FileLogger_Test.cpp
)

# Link the libraries to target.
target_link_libraries(
    ${testname}
    Qt5::Core 
    Qt5::Test
)

add_test(${testname} ${testname}) 

