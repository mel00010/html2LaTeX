add_library(void_test INTERFACE)

target_sources(void_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/Area_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Base_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Br_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Col_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Embed_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Hr_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Img_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Input_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Keygen_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Link_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Meta_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Param_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Source_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Track_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Void_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Wbr_test.cpp
)
target_link_libraries(void_test
	INTERFACE
		void
)
