project ("octetos-verso")

cmake_minimum_required (VERSION 3.8)

# Habilite Recarga activa para los compiladores de MSVC si se admiten.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()



# Agregue un origen al ejecutable de este proyecto.
ADD_LIBRARY(verso-sdl-1 STATIC "scenary.cpp" "sdl/scenary.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  SET_PROPERTY(TARGET verso-sdl-1 PROPERTY CXX_STANDARD 20)
endif()

FIND_PACKAGE(SDL2 CONFIG REQUIRED)
FIND_PACKAGE(SDL2_image CONFIG REQUIRED)
FIND_PACKAGE(GLEW CONFIG REQUIRED)
find_package(sdl2-gfx CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
TARGET_LINK_LIBRARIES(verso-sdl-1
PRIVATE
$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
$<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
GLEW::GLEW
SDL2::SDL2_gfx
glm::glm-header-only
)

ADD_SUBDIRECTORY(devel)