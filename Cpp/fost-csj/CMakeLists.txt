add_library(fost-csj
        iterator.cpp
        parser.cpp
    )
target_include_directories(fost-csj PUBLIC ../include)
target_link_libraries(fost-csj fost-jsondb)
set_target_properties(fost-csj PROPERTIES DEBUG_POSTFIX "-d")
install(TARGETS fost-csj LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(DIRECTORY ../include/fost DESTINATION include)

if(TARGET check)
    add_library(fost-csj-smoke STATIC EXCLUDE_FROM_ALL
            iterator.tests.cpp
            parser.tests.cpp
        )
    target_link_libraries(fost-csj-smoke fost-csj)
    smoke_test(fost-csj-smoke)
endif()
