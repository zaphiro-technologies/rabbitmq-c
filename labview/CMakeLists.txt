# Copyright 2007 - 2021, Alan Antonuk and the rabbitmq-c contributors.
# SPDX-License-Identifier: mit

set(RABBITMQ_LV_SOURCES
  labview_rabbitmq.c 
	utils.c utils.h
  unix/platform_utils.c
)

set(RMQ_VERSION 3.9.5)
set(RMQ_SOVERSION 3)

add_library(rabbitmq-lv SHARED ${RABBITMQ_LV_SOURCES})
target_link_libraries(rabbitmq-lv PRIVATE rabbitmq::rabbitmq)

if (THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(rabbitmq-lv PUBLIC "-pthread")
endif()

if (WIN32)
    set_target_properties(rabbitmq-lv PROPERTIES VERSION ${RMQ_VERSION} OUTPUT_NAME rabbitmq.${RMQ_SOVERSION})
else (WIN32)
    set_target_properties(rabbitmq-lv PROPERTIES VERSION ${RMQ_VERSION} SOVERSION ${RMQ_SOVERSION})
endif (WIN32)

install(TARGETS rabbitmq-lv
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

include_directories(/usr/local/natinst/LabVIEW-2020-64/cintools)