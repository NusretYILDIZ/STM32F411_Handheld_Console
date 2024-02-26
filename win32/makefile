CXX = gcc
# Update these paths as necessary to match your installation
SDL_LIB = -L./sdl2/lib -lSDL2main -lSDL2
SDL_INCLUDE = -I./sdl2/include
STM_INCLUDE := ../STM32F411CEU_Handheld_Console/Core/STM32_Handheld_Console/
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CXXFLAGS = -Wall -c -std=c99 $(SDL_INCLUDE) $(STM_INCLUDE)
LDFLAGS = -lmingw32 -mwindows -mconsole $(SDL_LIB)
EXE = ./Release/STM32F411CEU_Handheld_Console_Emulator.exe

all: $(EXE) clean

$(EXE): main.o display_driver.o glcdfont.o file_system.o instructions.o script_engine.o syscalls.o input_driver.o menu.o popup.o system_main.o
	$(CXX) $^ $(LDFLAGS) -o $@

main.o: main.c
	$(CXX) $(CXXFLAGS) $< -o $@

display_driver.o: $(STM_INCLUDE)display/display_driver.c
	$(CXX) $(CXXFLAGS) $^ -o $@

glcdfont.o: $(STM_INCLUDE)display/glcdfont.c
	$(CXX) $(CXXFLAGS) $^ -o $@

file_system.o: $(STM_INCLUDE)file_system/file_system.c
	$(CXX) $(CXXFLAGS) $^ -o $@

instructions.o: $(STM_INCLUDE)game_engine/script/instructions.c
	$(CXX) $(CXXFLAGS) $^ -o $@

script_engine.o: $(STM_INCLUDE)game_engine/script/script_engine.c
	$(CXX) $(CXXFLAGS) $^ -o $@

syscalls.o: $(STM_INCLUDE)game_engine/script/syscalls.c
	$(CXX) $(CXXFLAGS) $^ -o $@

input_driver.o: $(STM_INCLUDE)input/input_driver.c
	$(CXX) $(CXXFLAGS) $^ -o $@

menu.o: $(STM_INCLUDE)system_menu/menu.c
	$(CXX) $(CXXFLAGS) $^ -o $@

popup.o: $(STM_INCLUDE)system_menu/popup.c
	$(CXX) $(CXXFLAGS) $^ -o $@

system_main.o: $(STM_INCLUDE)system_menu/system_main.c
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	del /q *.o
	copy .\sdl2\bin\SDL2.dll /y .\Release