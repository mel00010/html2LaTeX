add_library(elements_test INTERFACE)

target_sources(elements_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/Element_test.cpp
)
target_link_libraries(elements_test
	INTERFACE
		elements
		escapablerawtext
		escapablerawtext_test
		foreign
		foreign_test
		normal
		normal_test
		rawtext
		rawtext_test
		void
		void_test
)
add_subdirectory(EscapableRawText)
add_subdirectory(Foreign)
add_subdirectory(Normal)
add_subdirectory(RawText)
add_subdirectory(Void)