# CMakeList.txt: Projekt CMake pro scientific-calculator, sem přidejte logiku zdrojového
# kódu a definic specifickou pro projekt.
#
cmake_minimum_required (VERSION 3.8)

project ("scientific-calculator")

# Přidejte zdrojový kód ke spustitelnému souboru tohoto projektu.
add_executable (scientific-calculator "scientific-calculator.cpp" "scientific-calculator.h" "variables.h" "variables.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET scientific-calculator PROPERTY CXX_STANDARD 20)
endif()

# TODO: V případě potřeby přidejte testy a cíle instalace.
