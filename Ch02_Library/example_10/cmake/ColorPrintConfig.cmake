add_library(ColorPrint STATIC IMPORTED)

find_library(ColorPrint_Lib_Path ColorPrint HINTS "${CMAKE_CURRENT_LIST_DIR}/../../")
set_target_properties(ColorPrint PROPERTIES IMPORTED_LOCATION "${ColorPrint_Lib_Path}")
