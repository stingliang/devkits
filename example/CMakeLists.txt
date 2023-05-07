# libdevcore demo
add_executable(libdevcore_demo libdevcore_demo.cpp)
target_link_libraries(libdevcore_demo devcore)

# gui demo
if (WITH_GUI)
    add_executable(libgui_demo libgui_demo.cpp)
    target_link_libraries(libgui_demo libgui)
    add_dependencies(libgui_demo libgui)
endif ()