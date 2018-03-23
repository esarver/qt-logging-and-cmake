add_subdirectory(Common)

set(
   objects
   $<TARGET_OBJECTS:Common-Logger>
   $<TARGET_OBJECTS:Common-Config>
)

add_executable(
   ${PROJECT_NAME}
   ${objects}
   main.cpp
)

target_link_libraries(
   ${PROJECT_NAME} 
   Qt5::Core 
   Qt5::Sql
)
