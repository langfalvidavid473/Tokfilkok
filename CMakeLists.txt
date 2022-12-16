cmake_minimum_required(VERSION 3.23)
project(Tokfilkok)

set(CMAKE_CXX_STANDARD 20)

add_executable(Tokfilkok main.cpp)
# Sztori fájlok kijelölése
set(StoryFiles "txtFiles/bevezeto.txt;txtFiles/lose.txt;txtFiles/victory.txt")
# A sztori fájlokon végigiterálás és másolás
foreach(storyfile ${StoryFiles})
    # Iterált fájl másolása
    add_custom_command(TARGET Tokfilkok POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E
            copy ${CMAKE_SOURCE_DIR}/${storyfile} ${CMAKE_CURRENT_BINARY_DIR}
            DEPENDS ${storyfile}
            )

endforeach(storyfile)