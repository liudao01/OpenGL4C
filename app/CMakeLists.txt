# For more information about using CMake with Android Studio, read the

cmake_minimum_required(VERSION 3.4.1)


file(GLOB my_source src/main/cpp/*.cpp src/main/cpp/*.c src/main/cpp/egl/*.cpp src/main/cpp/egl/*.c)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNO_CRYPTO")
add_library(
        native-lib

        SHARED

        src/main/cpp/native-lib.cpp

        ${my_source}
)


find_library(
        log-lib

        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib
        EGL
        GLESv2
        android

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})