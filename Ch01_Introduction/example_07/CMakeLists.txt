cmake_minimum_required(VERSION 3.0)
project("example_07")

message("==================================")
foreach(i RANGE 10)
	message("i: ${i}")	
endforeach(i RANGE 10)


message("==================================")
foreach(j RANGE -1 9 3)
	message("j: ${j}")
endforeach(j RANGE -1 9 3)

message("==================================")
list(APPEND l "Dog" "Bird" "Cat")
foreach(e IN LISTS l)
	message("Element: ${e}")
endforeach()

message("==================================")
set(A "C")
set(B "C++")
set(C "Python")
set(D "Java")
foreach(e IN LISTS A B C D)
	message("Language: ${e}")
endforeach(e IN LISTS A B C D)

message("==================================")
