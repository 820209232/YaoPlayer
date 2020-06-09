include_directories (../)

link_directories(${CMAKE_SOURCE_DIR}/3rdpart/ffmpeg-4.1.3/lib)
link_directories(${CMAKE_SOURCE_DIR}/3rdpart/glfw/lib/)

include_directories(../3rdpart/glad/include/)
include_directories(../3rdpart/glfw/include/)

add_executable(
    PlayerMain
    mainGL.cpp
)

target_link_libraries(PlayerMain YaoPlayer)
target_link_libraries(PlayerMain YaoThread)
target_link_libraries(PlayerMain YaoAV)
target_link_libraries(PlayerMain YaoGL)
target_link_libraries(PlayerMain YaoImg)

target_link_libraries(PlayerMain avcodec)
target_link_libraries(PlayerMain avformat)
target_link_libraries(PlayerMain avdevice)
target_link_libraries(PlayerMain avfilter)
target_link_libraries(PlayerMain avutil)
target_link_libraries(PlayerMain postproc)
target_link_libraries(PlayerMain swresample)
target_link_libraries(PlayerMain swscale)

target_link_libraries(PlayerMain glfw3)


