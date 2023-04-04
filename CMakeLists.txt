# Copyright LIV Inc. 2019-2023

cmake_minimum_required(VERSION 3.20)

project(rotatoexpress VERSION 0.3)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/INSTALLOUT CACHE PATH "Force installation location" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/third-party/SDL)

file(GLOB rotatoexpress_src CONFIGURE_DEPENDS src/*)

set(TPDIR "${CMAKE_SOURCE_DIR}/third-party/")
set(IMDIR "${TPDIR}/imgui/")

file(GLOB ImGui
	${IMDIR}/imgui* 
	${IMDIR}/imstb* 
	${IMDIR}/backends/imgui_impl_sdlrenderer* 
	${IMDIR}/backends/imgui_impl_sdl2*
)

add_executable(rotatoexpress WIN32 ${rotatoexpress_src} ${ImGui} README.md LICENSE)
target_include_directories(rotatoexpress PRIVATE
	${TPDIR}/openvr/headers 
	${TPDIR}/glm/
	${IMDIR}
)

target_link_libraries(rotatoexpress 
	PUBLIC SDL2-static 
	SDL2main
	${TPDIR}/openvr/lib/win64/openvr_api.lib
)

add_custom_command(TARGET rotatoexpress 
	POST_BUILD COMMAND 
	${CMAKE_COMMAND} -E copy "${TPDIR}/openvr/bin/win64/openvr_api.dll" $<TARGET_FILE_DIR:rotatoexpress>
)

install(TARGETS rotatoexpress)
install(FILES "${CMAKE_SOURCE_DIR}/README.md" "${TPDIR}/openvr/bin/win64/openvr_api.dll" TYPE BIN)
