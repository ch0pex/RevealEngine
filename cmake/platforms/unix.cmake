set(PLAT unix)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -O3 -ffast-math -ftree-vectorize -fprefetch-loop-arrays")
