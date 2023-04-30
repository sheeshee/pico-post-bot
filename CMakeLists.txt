cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico-post-bot C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()


set(PICO_SSID $ENV{PICO_SSID})
set(PICO_SSID_PASSWORD $ENV{PICO_SSID_PASSWORD})

if (DEFINED PICO_SSID)
    add_definitions(-DWIFI_SSID="${PICO_SSID}")
    message(STATUS "PICO_SSID is set to ${PICO_SSID}")
else ()
    message(STATUS "PICO_SSID is not set")
endif ()

if (DEFINED PICO_SSID_PASSWORD)
    add_definitions(-DWIFI_PASSWORD="${PICO_SSID_PASSWORD}")
    message(STATUS "PICO_SSID_PASSWORD is set to ${PICO_SSID_PASSWORD}")
else ()
    message(STATUS "PICO_SSID_PASSWORD is not set")
endif ()

add_definitions(-DPICO_BOARD="pico_w")


add_executable(postbot
    main.c
)

pico_enable_stdio_usb(postbot 1)
pico_enable_stdio_uart(postbot 1)

pico_add_extra_outputs(postbot)

target_include_directories(postbot PRIVATE ${CMAKE_CURRENT_LIST_DIR} )

target_link_libraries(postbot
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_mbedtls
    pico_mbedtls
    pico_stdlib
    )


# Ignore warnings from lwip code
set_source_files_properties(
        ${PICO_LWIP_PATH}/src/apps/altcp_tls/altcp_tls_mbedtls.c
        PROPERTIES
        COMPILE_OPTIONS "-Wno-unused-result"
        )
