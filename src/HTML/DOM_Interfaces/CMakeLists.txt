add_library(DOM_Interfaces STATIC "")
target_sources(DOM_Interfaces
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Document.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/DocumentFragment.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/DocumentType.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/DOMImplementation.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/DOMString.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Node.hpp
)
target_link_libraries(DOM_Interfaces
	PUBLIC	
)
set_target_properties(DOM_Interfaces PROPERTIES LINKER_LANGUAGE CXX)
