enable_testing()

if(${Enable_Assert_Test})
	# 使用`asser.h`這個標頭檔來實現單元測試
	add_executable(testAsserter ./test_assert.c)
	target_link_libraries(testAsserter myMathLib)
	add_test(test_assert testAsserter)
else()
	# 新增變數`Exe_File`，用來表示可執行檔`myExe`
	set(Exe_File ${CMAKE_BINARY_DIR}/myExe)
	
	# 新增一項測試，並且使用回傳值來判斷這項測試是否成功
	add_test(test_3_2 ${Exe_File} 3 2)
	
	# 新增一項測試，透過可執行檔`myExe`在標準輸出印出的訊息來判斷這項測試是否成功
	add_test(test_7_3 ${Exe_File} 7 3)
	set_tests_properties(test_7_3 
		PROPERTIES PASS_REGULAR_EXPRESSION "is 343")
	
	# 使用巨集來來簡化單元測試
	macro(do_test arg1 arg2 result)
		add_test(macro_test_${arg1}_${arg2} ${Exe_File} ${arg1} ${arg2})
		set_tests_properties(macro_test_${arg1}_${arg2} 
			PROPERTIES PASS_REGULAR_EXPRESSION ${result})
	endmacro(do_test arg1 arg2 result)
	
	# 呼叫巨集來做單元測試
	do_test(5 2 "is 25")
	do_test(10 2 "is 100")
	do_test(2 10 "is 1024")
endif(${Enable_Assert_Test})

