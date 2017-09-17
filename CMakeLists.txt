project(ipstats)

cmake_minimum_required(VERSION 2.8)

add_library(pq SHARED IMPORTED)
set_property(TARGET pq PROPERTY IMPORTED_LOCATION /usr/lib64/libpq.so)

add_executable(ipstats main.cpp IpNeigh.cpp NetReport.cpp SendPing.cpp dbConnect.c)

add_executable(runipstats runipstats.c)

add_executable(pingip pingip.cpp SendPing.cpp)

target_link_libraries(ipstats pq popt)
