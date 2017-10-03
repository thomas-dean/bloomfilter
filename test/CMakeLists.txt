enable_testing ()
include_directories (${bloomfilter_SOURCE_DIR}/include)
add_executable (runUnitTests
    bloom_tests.c
)
target_link_libraries (runUnitTests
    bloom
)
add_executable (runPerfTests
    bloom_perf.c
)
target_link_libraries (runPerfTests
    bloom
)
