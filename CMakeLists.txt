cmake_minimum_required(VERSION 3.15)

project(SleepBenchmark
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(benchmark
	benchmark.cpp
)

if (WIN32)
	target_compile_definitions(benchmark PRIVATE OS_WINDOWS)
endif()
