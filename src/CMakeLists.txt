include_directories (${bloomfilter_SOURCE_DIR}/include)
add_library (bloom bloom.c)
target_link_libraries(bloom m)
