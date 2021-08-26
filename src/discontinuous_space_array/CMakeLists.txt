add_executable(tree_and_list tree_and_list.cpp)
target_link_libraries(tree_and_list ${GTEST_BOTH_LIBRARIES} glog pthread)

add_executable(majority_element majority_element.cpp)

target_link_libraries(majority_element ${GTEST_BOTH_LIBRARIES} glog pthread)