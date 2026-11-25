cmake_minimum_required(VERSION 3.25)
project(model_clients LANGUAGES C CXX)

# Build the candidate Model and its optional OOS adapter with the reference Solver.
add_subdirectory(../.. model)
set(OOS_WITH_MODEL ON CACHE BOOL "" FORCE)
add_subdirectory("${SOLVER_SOURCE}" solver)
add_executable(rbe3 rbe3.cpp)
target_link_libraries(rbe3 PRIVATE oos::api oor::oos)
add_executable(mesh mesh.cpp)
target_link_libraries(mesh PRIVATE oos::api oor::oos)
