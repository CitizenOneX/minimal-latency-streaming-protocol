cmake_minimum_required(VERSION 3.0)

project(
    mlsp
)

if(WIN32)
  add_compile_definitions(_WINDOWS)
  find_library(WSOCK32_LIBRARY wsock32)
  find_library(WS2_32_LIBRARY ws2_32)
  list(APPEND EXTRA_WINSOCK_LIBS wsock32 ws2_32)
endif()

add_library(mlsp mlsp.c)
install(TARGETS mlsp DESTINATION lib)
install(FILES mlsp.h DESTINATION include)

# sample mlsp client and server - no need to build if you just need the lib
#add_executable(mlsp-example-server examples/mlsp_example_server.c)
#target_link_libraries(mlsp-example-server mlsp ${EXTRA_WINSOCK_LIBS})

#add_executable(mlsp-example-client examples/mlsp_example_client.c)
#target_link_libraries(mlsp-example-client mlsp ${EXTRA_WINSOCK_LIBS})
