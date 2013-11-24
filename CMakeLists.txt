cmake_minimum_required (VERSION 2.6) 
project (proj) 

set(PROJ_NAME "proj")
set(PROJ_NAME_TEST "test")
set(INCLUDE_DIRECTORIES 
	/home/dev/proj/cpp/v8/include/
	/home/dev/proj/cpp/gtest/include/
        /home/dev/proj/cpp/fastcgi/include
	/usr/local/include
)

set(TARGET_LINK_LIBRARIES 
	/home/dev/proj/cpp/v8/out/x64.release/obj.target/tools/gyp/libv8_base.x64.a
	/home/dev/proj/cpp/v8/out/x64.release/obj.target/tools/gyp/libv8_snapshot.a
	/home/dev/proj/cpp/v8/out/x64.release/obj.target/third_party/icu/libicui18n.a
	/home/dev/proj/cpp/v8/out/x64.release/obj.target/third_party/icu/libicuuc.a
	/home/dev/proj/cpp/v8/out/x64.release/obj.target/third_party/icu/libicudata.a
	/home/dev/proj/cpp/gtest/lib/.libs/libgtest_main.a
        /home/dev/proj/cpp/gtest/lib/.libs/libgtest.a
	pthread
        fcgi
        fcgi++
)

FILE(GLOB FILES_CPP "*.cpp")


add_executable (${PROJ_NAME} 
    ${FILES_CPP}
    main.cc
)

add_executable (${PROJ_NAME_TEST}
    ${FILES_CPP}
    main_test.cc
)

include_directories (
	${INCLUDE_DIRECTORIES}
)
 
TARGET_LINK_LIBRARIES(${PROJ_NAME} ${TARGET_LINK_LIBRARIES})
TARGET_LINK_LIBRARIES(${PROJ_NAME_TEST} ${TARGET_LINK_LIBRARIES}) 

