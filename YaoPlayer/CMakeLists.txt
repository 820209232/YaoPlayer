include_directories (../)

link_directories(${CMAKE_SOURCE_DIR}/3rdpart/ffmpeg-4.1.3/lib)

add_library(
    YaoPlayer
    YaoPlayer.cpp
    YaoPlayerReaderThread.cpp
    YaoDecodeThread.cpp
    YaoPlayerCtr.cpp
)

target_link_libraries(YaoPlayer YaoPlayer)
target_link_libraries(YaoPlayer YaoThread)
target_link_libraries(YaoPlayer YaoAV)

target_link_libraries(YaoPlayer avcodec)
target_link_libraries(YaoPlayer avformat)
target_link_libraries(YaoPlayer avdevice)
target_link_libraries(YaoPlayer avfilter)
target_link_libraries(YaoPlayer avutil)
target_link_libraries(YaoPlayer postproc)
target_link_libraries(YaoPlayer swresample)
target_link_libraries(YaoPlayer swscale)
