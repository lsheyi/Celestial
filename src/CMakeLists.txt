file(GLOB BASE_LIST ${CMAKE_CURRENT_SOURCE_DIR}/base/*.cc)
file(GLOB LOG_LIST ${CMAKE_CURRENT_SOURCE_DIR}/log/*.cc)
file(GLOB NET_LIST ${CMAKE_CURRENT_SOURCE_DIR}/net/*.cc)
file(GLOB TIMER_LIST ${CMAKE_CURRENT_SOURCE_DIR}/timer/*.cc)

add_library(network SHARED 
            ${BASE_LIST} 
            ${LOG_LIST} 
            ${NET_LIST} 
            ${TIMER_LIST})