add_library(WebAPI STATIC "")
target_sources(WebAPI
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/EventHandler.hpp
)
target_link_libraries(WebAPI
	PUBLIC	
)
set_target_properties(WebAPI PROPERTIES LINKER_LANGUAGE CXX)
