set(GTEST_ROOT $ENV{HOME}/ev3rt-beta7-release/hrps/sdk/etrobocon2017/str/googletest/googletest)
include_directories(
	${GTEST_ROOT}/include
	)
add_executable(SonarAlertTest SonarAlertTest.cpp)
target_link_libraries(SonarAlertTest
	pthread
	${GTEST_ROOT}/libgtest.a
	)
