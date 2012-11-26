########### target ###############
set(rcssnet3D_LIB_HDRS
    addr.hpp
    exception.hpp
    handler.hpp
    iosocketstream.hpp
    isocketstream.hpp
    osocketstream.hpp
    socket.hpp
    socketstreambuf.hpp
    tcpsocket.hpp
    udpsocket.hpp
    rcssnet3D_defines.h 
)

set(rcssnet3D_LIB_SRCS
    addr.cpp
    exception.cpp
    handler.cpp
    socket.cpp
    tcpsocket.cpp
    udpsocket.cpp
)

add_library(rcssnet3D ${rcssnet3D_LIB_SRCS} ${rcssnet3D_LIB_HDRS})

target_link_libraries(rcssnet3D ${NET_LIBS})

set_target_properties(rcssnet3D PROPERTIES VERSION ${RCSSNET_VERSION}
    SOVERSION ${RCSSNET_SO_VERSION})
install(TARGETS rcssnet3D DESTINATION ${LIBDIR}/${CMAKE_PROJECT_NAME})


########### install files ###############

install(DIRECTORY ./ DESTINATION ${INCLUDEDIR}/${CMAKE_PROJECT_NAME}/rcssnet
          FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h" PATTERN ".svn" EXCLUDE)
