# In-memory deck, result and query API shared by all bindings and file adapters.
add_library(oor_core STATIC
    Design.cpp
    Deck.cpp
    Results.cpp
    NamedResults.cpp
    Queries.cpp
    CardEdits.cpp
    ControlEdits.cpp
    QueryArgumentsJson.cpp
    CardTables.cpp)
add_library(oor::core ALIAS oor_core)
target_include_directories(oor_core PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>" "$<INSTALL_INTERFACE:include>")
target_link_libraries(oor_core PUBLIC oor_query)
oor_enable_warnings(oor_core)
