add_library(client client.cc client.h)
target_link_libraries(client PUBLIC person PUBLIC person PUBLIC basket)
target_include_directories(client PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_executable(client-main client-main.cc)
target_link_libraries(client-main PUBLIC client)