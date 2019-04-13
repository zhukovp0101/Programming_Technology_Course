cmake_minimum_required (VERSION 3.8)
project(Game)

set(RUN_TEST FALSE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SFML_DIR "Libs/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 COMPONENTS graphics audio window REQUIRED)

#file(GLOB_RECURSE MAIN_SOURCES *.cpp *.h)
if (RUN_TEST)
    add_subdirectory(Libs/googletest-master)
    include_directories(Libs/googletest-master/googletest/include)
    include_directories(Libs/googletest-master/googlemock/include)
    add_executable(Tests/BaseTestIncludes.h Tests/Normal/Tests.cpp)
    target_link_libraries(Game gtest gtest_main)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
endif()
include_directories(Classes/Scene/ Classes/Object/ Classes/GUI/ Classes/Building/ Classes/Unit Classes/Tools Classes/Scene/Level Classes/Factories Classes Tests)
add_executable (Game Classes/Object/IObject.cpp Classes/Object/IObject.h main.cpp Classes/Scene/Scene.cpp Classes/Scene/Scene.h Classes/Building/Castle.cpp Classes/Building/Castle.h Classes/Object/ILivingObject.cpp Classes/Object/ILivingObject.h Classes/Building/IBuilding.cpp Classes/Building/IBuilding.h Classes/Scene/Level/Level.cpp Classes/Scene/Level/Level.h Classes/Scene/Menu.cpp Classes/Scene/Menu.h Classes/GUI/Button.cpp Classes/GUI/Button.h Classes/Object/IEventObject.cpp Classes/Object/IEventObject.h Classes/Unit/Unit.cpp Classes/Unit/Unit.h Classes/BaseIncludes.h Classes/GUI/IMenuItem.cpp Classes/GUI/IMenuItem.h Classes/Tools/Parser.cpp Classes/Tools/Parser.h Classes/Factories/ItemFactory.cpp Classes/Factories/ItemFactory.h Classes/Factories/LevelFactory.h Classes/Factories/SceneFactory.h Classes/Factories/MenuFactory.cpp Classes/Factories/MenuFactory.h Classes/Scene/Level/Map.cpp Classes/Scene/Level/Map.h Classes/Unit/Skeleton.cpp Classes/Unit/Skeleton.h Classes/Unit/Witch.cpp Classes/Unit/Witch.h Classes/Factories/UnitFactory.cpp Classes/Factories/UnitFactory.h)

#add_executable(Game ${MAIN_SOURCES})

target_link_libraries(Game sfml-graphics sfml-audio sfml-window)

