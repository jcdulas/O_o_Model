include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(sdk_libraries)
foreach(module IN ITEMS base io deck model results analysis query core)
    set(target oor_${module})
    set_target_properties(${target} PROPERTIES EXPORT_NAME ${module})
    target_compile_features(${target} PUBLIC cxx_std_20)
    list(APPEND sdk_libraries ${target})
endforeach()
set(config_dir "${CMAKE_INSTALL_LIBDIR}/cmake/oo-model")
install(TARGETS ${sdk_libraries} EXPORT SdkTargets ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")
install(DIRECTORY include/oor DESTINATION include)
install(EXPORT SdkTargets FILE oo-model-targets.cmake NAMESPACE oor:: DESTINATION "${config_dir}")
configure_package_config_file("cmake/oo-model-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/oo-model-config.cmake" INSTALL_DESTINATION "${config_dir}")
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/oo-model-config-version.cmake"
    VERSION "${PROJECT_VERSION}" COMPATIBILITY SameMinorVersion)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/oo-model-config.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/oo-model-config-version.cmake" DESTINATION "${config_dir}")
