cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)
include(pico_extras_import.cmake)

project(pico-post-bot C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

if (DEFINED ENV{PICO_SSID} AND (NOT WIFI_SSID))
    set(WIFI_SSID $ENV{PICO_SSID})
    message("WIFI_SSID is set from environment to ${WIFI_SSID}")
endif ()

if (DEFINED ENV{PICO_SSID_PASSWORD} AND (NOT WIFI_PASSWORD))
    set(WIFI_PASSWORD $ENV{PICO_SSID_PASSWORD})
    message("WIFI_PASSWORD is set from environment")
endif ()

if (DEFINED ENV{PICO_IFTTT_KEY} AND (NOT IFTTT_KEY))
    set(IFTTT_KEY $ENV{PICO_IFTTT_KEY})
    message("IFTTT_KEY is set from environment")
endif ()

set(WIFI_SSID "${WIFI_SSID}" CACHE INTERNAL "WiFi SSID for examples")
set(WIFI_PASSWORD "${WIFI_PASSWORD}" CACHE INTERNAL "WiFi password for examples")
set(IFTTT_KEY "${IFTTT_KEY}" CACHE INTERNAL "IFTTT key for examples")


add_executable(postbot
    main.cpp
)

pico_enable_stdio_usb(postbot 1)
pico_enable_stdio_uart(postbot 0)

pico_add_extra_outputs(postbot)

target_include_directories(postbot PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    network
    )

target_link_libraries(postbot
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_mbedtls
    pico_mbedtls
    pico_stdlib
    hardware_sleep
    )

target_compile_definitions(postbot PRIVATE
    PICO_BOARD="pico_w"
    WIFI_SSID=\"${WIFI_SSID}\"
    WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
    IFTTT_KEY=\"${IFTTT_KEY}\"
    )


# Ignore warnings from lwip code
set_source_files_properties(
        ${PICO_LWIP_PATH}/src/apps/altcp_tls/altcp_tls_mbedtls.c
        PROPERTIES
        COMPILE_OPTIONS "-Wno-unused-result"
        )
