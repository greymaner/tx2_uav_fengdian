execute_process(COMMAND dsdl/tools/gen.sh
                RESULT_VARIABLE CMD_ERROR
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                )
if(CMD_ERROR)
        set(RESULT_STR "ERROR")
else()
        set(RESULT_STR "OK")
endif()

message(STATUS "MMC DSDL generation: ${RESULT_STR}")