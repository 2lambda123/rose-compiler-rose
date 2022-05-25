include(ExternalProject)

string(REPLACE "." "-" Local_EDG_Version "${EDG_VERSION}")

# Detect platform
set(platform "")
if(APPLE)
  set(platform "i686-apple-darwin")
elseif(UNIX)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(platform "x86_64-pc-linux-gnu")
  else()
    set(platform "i686-pc-linux-gnu")
  endif()
endif()
if(platform STREQUAL "")
  message(FATAL_ERROR
    "Unable to detect platform when attempting to download EDG binary tarball")
endif()

# Detect compiler by asking GCC what version it is
execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
                OUTPUT_VARIABLE GCC_version)
# strip patch version; we only care about major & minor
string(REGEX MATCH "^([0-9]+\\.[0-9]+)" GCC_version ${GCC_version})
set(compiler "gnu-${GCC_version}")


# Get binary compatibility signature
set(EDG_SIG_OUTPUT_DIR
  "${CMAKE_BINARY_DIR}/src/frontend/CxxFrontend"
)
set(EDG_SIG_OUTPUT
  "${CMAKE_BINARY_DIR}/src/frontend/CxxFrontend/edg-generate-sig.output"
)
#ADD_CUSTOM_COMMAND(TARGET EDG_tarball
#  PRE_BUILD
#  COMMAND "${CMAKE_SOURCE_DIR}/scripts/edg-generate-sig" "${CMAKE_SOURCE_DIR}" " ${CMAKE_BINARY_DIR}" " >" ${EDG_SIG_OUTPUT}
#  COMMAND "cat" ${EDG_SIG_OUTPUT}  ">" signature
#  DEPENDS roseUtil rosetta_generated "${CMAKE_SOURCE_DIR}/scripts/edg-generate-sig"
#)
add_custom_target(get_EDG_name
#  COMMENT "EDG NAME: ${CMAKE_SOURCE_DIR}/scripts/edg-generate-sig ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}
#    > ${EDG_SIG_OUTPUT}"
  COMMAND ${CMAKE_SOURCE_DIR}/scripts/edg-generate-sig ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}
    > ${EDG_SIG_OUTPUT}
  #DEPENDS roseUtil rosetta_generated)
  )
  # TODO switch EDG version
  # since EDG version 5, the EDG signature no longer depends on generated code,
  # so we can fetch EDG before building
#set(signature "")

#add_custom_target( EDGSignature
##    COMMENT "EDGSignature arguments ${EDG_SIG_OUTPUT} ${Local_EDG_Version} ${platform} ${compiler}"
#    COMMAND ${CMAKE_COMMAND} -P ${PROJECT_SOURCE_DIR}/cmake/ProcessEDGBinary.cmake ${EDG_SIG_OUTPUT} ${Local_EDG_Version} ${platform} ${compiler} 
#    DEPENDS get_EDG_name
#)

# download EDG now
# TODO switch EDG version
# since EDG version 5, the EDG signature no longer depends on generated code,
# so we can fetch EDG before building

# FIXME edg-generate-sig?

message(STATUS "Generating EDG signature")
# TODO remove mkdir? not needed?
execute_process(
  COMMAND mkdir -p "${EDG_SIG_OUTPUT_DIR}"
  COMMAND_ECHO STDOUT
  COMMAND_ERROR_IS_FATAL ANY
)
execute_process(
  COMMAND "${CMAKE_SOURCE_DIR}/scripts/edg-generate-sig" "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}"
  OUTPUT_FILE ${EDG_SIG_OUTPUT}
  COMMAND_ECHO STDOUT
  COMMAND_ERROR_IS_FATAL ANY
)

message(STATUS "Fetching EDG tarball")
execute_process(
  COMMAND ${CMAKE_COMMAND} -P ${PROJECT_SOURCE_DIR}/cmake/ProcessEDGBinary.cmake ${EDG_SIG_OUTPUT} ${Local_EDG_Version} ${platform} ${compiler}
  COMMAND_ECHO STDOUT
  COMMAND_ERROR_IS_FATAL ANY
)

#set(tarball_site "http://edg-binaries.rosecompiler.org")
# example url
# http://edg-binaries.rosecompiler.org/roseBinaryEDG-5-0-x86_64-pc-linux-gnu-gnu-8-5.0.11.80.1.tar.gz
#set(tarball_filename "roseBinaryEDG-${Local_EDG_Version}-${platform}-${compiler}-${signature}.tar.gz")

#add_custom_target(EDG_tarball
#COMMAND wget ${tarball_site}/roseBinaryEDG-${Local_EDG_Version}-${platform}-${compiler}-${signature}.tar.gz ${CMAKE_BINARY_DIR}/src/frontend/CxxFrontend/EDG.tar.gz
#COMMENT "Untar EDG"
#COMMAND tar zxvf ${CMAKE_BINARY_DIR}/src/frontend/CxxFrontend/EDG.tar.gz -C ${CMAKE_BINARY_DIR}/src/frontend/CxxFrontend 
#DEPENDS EDGSignature
#)
#ExternalProject_Add(EDG_tarball
#  COMMENT "EDG signature = ${signature}"
#  URL ${tarball_site}/roseBinaryEDG-${Local_EDG_Version}-${platform}-${compiler}-${signature}.tar.gz
#  SOURCE_DIR ${CMAKE_BINARY_DIR}/src/frontend/CxxFrontend/EDG
#  CONFIGURE_COMMAND ""
#  BUILD_COMMAND ""
#  INSTALL_COMMAND ""
#  DEPENDS EDGSignature 
#  )

