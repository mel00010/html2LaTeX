add_library(escapablerawtext STATIC "")
target_sources(escapablerawtext
	PRIVATE
		EscapableRawText.cpp
		TextArea.cpp
		Title.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/EscapableRawText.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/TextArea.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Title.hpp
)
target_link_libraries(escapablerawtext
	PUBLIC
		htmltypes
)