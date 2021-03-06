add_library(fostgres
        configuration.cpp
        datum.cpp
        file.cpp
        fostgres-control-error.cpp
        fostgres-control-retry.cpp
        fostgres-sql.cpp
        matcher.cpp
        precondition.cpp
        response.cpp
        response.csj.cpp
        response.json-csv.cpp
        response.object.cpp
        sql.cpp
        updater.cpp
    )
target_link_libraries(fostgres fostgres-core f5-json-schema fost-csj)
set_target_properties(fostgres PROPERTIES DEBUG_POSTFIX "-d")
install(TARGETS fostgres LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

if(TARGET check)
    add_library(fostgres-smoke STATIC EXCLUDE_FROM_ALL
            datum.tests.cpp
            matcher.tests.cpp
            precondition.tests.cpp
            sql.tests.cpp
        )
    target_link_libraries(fostgres-smoke fostgres)
    smoke_test(fostgres-smoke)
endif()
