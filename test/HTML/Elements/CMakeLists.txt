add_library(Elements_test INTERFACE)

target_sources(Elements_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/Element_test.cpp
)
target_link_libraries(Elements_test
	INTERFACE
		Elements
		EscapableRawText
		EscapableRawText_test
		Foreign
		Foreign_test
		Normal
		Normal_test
		RawText
		RawText_test
		Void
		Void_test
)
add_subdirectory(EscapableRawText)
add_subdirectory(Foreign)
add_subdirectory(Normal)
add_subdirectory(RawText)
add_subdirectory(Void)