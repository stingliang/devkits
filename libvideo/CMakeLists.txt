set(submodule_name "video")
add_library(${submodule_name} STATIC BaseCapture.cpp OpencvCapture.cpp)
target_link_libraries(${submodule_name} PUBLIC devcore ${OpenCV_LIBS})
