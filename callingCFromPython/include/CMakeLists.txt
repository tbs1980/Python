FILE(GLOB Square_SRCS "*.h")

INSTALL(FILES
  ${Square_SRCS}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include COMPONENT Devel
  )
