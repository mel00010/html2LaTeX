add_library(EscapableRawText STATIC "")
target_sources(EscapableRawText
	PRIVATE
		EscapableRawText.cpp
		TextArea.cpp
		Title.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/EscapableRawText.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/TextArea.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Title.hpp
)
target_link_libraries(EscapableRawText
	PUBLIC
		HTML_types
)