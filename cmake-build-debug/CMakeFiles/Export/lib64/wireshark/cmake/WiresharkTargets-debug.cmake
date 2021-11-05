#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "epan" for configuration "Debug"
set_property(TARGET epan APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(epan PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib64/libwireshark.so.14.0.5"
  IMPORTED_SONAME_DEBUG "libwireshark.so.14"
  )

list(APPEND _IMPORT_CHECK_TARGETS epan )
list(APPEND _IMPORT_CHECK_FILES_FOR_epan "${_IMPORT_PREFIX}/lib64/libwireshark.so.14.0.5" )

# Import target "wiretap" for configuration "Debug"
set_property(TARGET wiretap APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(wiretap PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib64/libwiretap.so.11.0.5"
  IMPORTED_SONAME_DEBUG "libwiretap.so.11"
  )

list(APPEND _IMPORT_CHECK_TARGETS wiretap )
list(APPEND _IMPORT_CHECK_FILES_FOR_wiretap "${_IMPORT_PREFIX}/lib64/libwiretap.so.11.0.5" )

# Import target "wsutil" for configuration "Debug"
set_property(TARGET wsutil APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(wsutil PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib64/libwsutil.so.12.0.0"
  IMPORTED_SONAME_DEBUG "libwsutil.so.12"
  )

list(APPEND _IMPORT_CHECK_TARGETS wsutil )
list(APPEND _IMPORT_CHECK_FILES_FOR_wsutil "${_IMPORT_PREFIX}/lib64/libwsutil.so.12.0.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)