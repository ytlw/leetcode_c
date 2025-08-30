# https://support.leetcode.com/hc/en-us/articles/360011833974-What-are-the-environments-for-the-programming-languages-

# export MallocNanoZone=0 when encounter
# "malloc: nano zone abandoned due to inability to preallocate reserved vm space"

cmake_minimum_required(VERSION 3.14)
project(leetcode_c)
set(CMAKE_C_STANDARD 11)
if (NOT CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -fsanitize=address,undefined)    
else() 
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -fexec-charset=CP936)
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


include_directories(include)

function(compile source_dir)
    file(GLOB SRC_FILES "${source_dir}/*.c")
    foreach(FILE_PATH ${SRC_FILES})
        string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FILE_PATH})
        add_executable(${FILE_NAME} "${source_dir}/${FILE_NAME}.c")
        target_compile_definitions(${FILE_NAME} PRIVATE -DINPUT_FILE="${PROJECT_SOURCE_DIR}/${source_dir}/${FILE_NAME}.in")
    endforeach(FILE_PATH)
endfunction(compile)

compile(mains)
