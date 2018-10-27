include_directories(${gtest_SOURCE_DIR}/googletest/include ${gtest_SOURCE_DIR})

macro(package_add_test TESTNAME)
	add_executable(${TESTNAME} ${ARGN})
	target_link_libraries(${TESTNAME} spotifyapilib gtest gtest_main)
	# add_test(${TESTNAME} ${TESTNAME})
	# set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

add_executable(spotifyapitests SpotifyAPIEndpointTests.cpp)
target_link_libraries(spotifyapitests spotifyapilib gtest gtest_main)

# message("done generating tests")

# package_add_test(SpotifyAPIEndpointTests SpotifyAPIEndpointTests.cpp)

# add_executable(spotifyapitests SpotifyAPIEndpointTests.cpp)
# target_link_libraries(spotifyapitests spotifyapilib gtest gtest_main)

# add_test(spotifyapitests spotifyapitests)
# set_target_properties(spotifyapitests PROPERTIES FOLDER tests)
# add_executable(${TESTNAME

	# include_directories(BEFORE ${GTEST_INCLUDE_DIRS})
	# add_test(NAME SpotifyAPITests COMMAND SpotifyAPITests.cpp)
	# target_link_libraries(SpotifyAPITests pthread gtest gmock gtest_main)
