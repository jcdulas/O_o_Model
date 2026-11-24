# Each adapter depends on the in-memory model. The core has no dependency on any adapter.
add_library(oor_api STATIC ReaderFiles.cpp)
add_library(oor::api ALIAS oor_api)
target_link_libraries(oor_api PUBLIC oor_core)
oor_enable_warnings(oor_api)

function(oor_file_adapter name)
    add_library(oor_format_${name} STATIC ${ARGN})
    add_library(oor::${name} ALIAS oor_format_${name})
    target_link_libraries(oor_format_${name} PUBLIC oor_core)
    target_link_libraries(oor_api PUBLIC oor_format_${name})
    string(TOUPPER "${name}" symbol)
    target_compile_definitions(oor_api PRIVATE OOR_WITH_${symbol})
    oor_enable_warnings(oor_format_${name})
endfunction()

if("oos" IN_LIST OOR_FORMATS)
    oor_file_adapter(oos Oos.cpp ../deck/records/ModelFileLexer.cpp
        ../model/core/ModelFileReader.cpp ../model/core/ModelFileWriter.cpp)
endif()
if("ooh5" IN_LIST OOR_FORMATS)
    oor_file_adapter(ooh5 Ooh5.cpp ../results/core/ReadResults.cpp
        ../results/archive/ArchiveModel.cpp ../results/archive/ArchiveResultFile.cpp
        ../results/archive/ArchiveWriter.cpp ../query/table/Hdf5Export.cpp
        ../io/hdf5/Hdf5.cpp ../io/hdf5/Hdf5GlobalHeapCheck.cpp ../io/hdf5/Hdf5Internal.cpp
        ../io/hdf5/Hdf5Table.cpp ../io/hdf5/Hdf5Tree.cpp ../io/hdf5/Hdf5Writer.cpp
        ../io/hdf5/Hdf5StreamWriter.cpp)
    target_link_libraries(oor_format_ooh5 PRIVATE HDF5::HDF5 ZLIB::ZLIB)
endif()
if("xlsx" IN_LIST OOR_FORMATS)
    oor_file_adapter(xlsx ../results/xlsx/XlsxWriter.cpp ../io/zip/Zip.cpp)
    target_link_libraries(oor_format_xlsx PRIVATE ZLIB::ZLIB)
endif()
