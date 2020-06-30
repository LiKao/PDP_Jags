INCLUDE( FindPackageHandleStandardArgs )

IF( DEFINED ENV{JAGS_DIR} )
  SET( JAGS_DIR "$ENV{JAGS_DIR}" )
ENDIF()

find_path(
	JAGS_INCLUDE_BASE_DIR 
		JAGS/version.h
	HINTS
		${JAGS_DIR}
		/usr/include
		/usr/local/include
)

IF(${JAGS_INCLUDE_BASE_DIR} STREQUAL "JAGS_INCLUDE_BASE_DIR-NOTFOUND") 
	MESSAGE("-- Error: JAGS/version.h not found")
	SET(JAGS_FOUND NO)
	return()
ENDIF()

SET(JAGS_INCLUDE_DIR ${JAGS_INCLUDE_BASE_DIR}/JAGS)

try_run(
	JAGS_VERSION_RUN
	JAGS_VERSION_COMPILED 
	${CMAKE_CURRENT_BINARY_DIR}/ 
	${CMAKE_SOURCE_DIR}/cmake/tests/read_jags_version.cpp
	RUN_OUTPUT_VARIABLE JAGS_MAJOR
	CMAKE_FLAGS "-DINCLUDE_DIRECTORIES=${JAGS_INCLUDE_DIR}"
)

IF(${JAGS_VERSION_COMPILED})
	MESSAGE("-- JAGS major version: ${JAGS_MAJOR}")
ELSE()
	MESSAGE("-- Error: JAGS version not detected")
	SET(JAGS_FOUND NO)
	return()
ENDIF()

find_path(
	JAGS_MODULES_BASE_DIR 
		JAGS/modules-${JAGS_MAJOR}/bugs.la
	HINTS
		${JAGS_DIR}
		/usr/lib
		/usr/lib64
)


SET(JAGS_MODULE_DIR ${JAGS_MODULES_BASE_DIR}/JAGS/modules-${JAGS_MAJOR})

FIND_PACKAGE_HANDLE_STANDARD_ARGS(JAGS DEFAULT_MSG JAGS_MODULE_DIR JAGS_INCLUDE_DIR)

IF( JAGS_FOUND )
  SET( JAGS_INCLUDE_DIRS ${JAGS_INCLUDE_DIR} )

  MARK_AS_ADVANCED(
    JAGS_INCLUDE_DIR
    JAGS_DIR
  )
ELSE()
  SET( JAGS_DIR "" CACHE STRING
    "An optional hint to a directory for finding `JAGS`"
  )
ENDIF()
