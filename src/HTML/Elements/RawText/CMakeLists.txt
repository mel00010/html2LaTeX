add_library(RawText STATIC "")
target_sources(RawText
	PRIVATE
		RawText.cpp
		Script.cpp
		Style.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/RawText.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Script.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Style.hpp
)
target_link_libraries(RawText
	PUBLIC
		HTML_types
)