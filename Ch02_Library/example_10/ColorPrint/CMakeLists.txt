aux_source_directory(. Lib_Src)

add_library(${Lib_Name} ${Lib_Src})

install(TARGETS ColorPrint DESTINATION bin/${Lib_Name})
install(FILES myPrint.h DESTINATION include/${Lib_Name})
