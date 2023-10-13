aux_source_directory(. Lib_Src)

add_library(ColorPrint ${Lib_Src})

install(TARGETS ColorPrint DESTINATION bin)
install(FILES myPrint.h DESTINATION include)
