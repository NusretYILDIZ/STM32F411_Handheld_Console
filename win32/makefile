CXX = gcc

SDL_LIB = -L./sdl2/lib -lSDL2main -lSDL2
SDL_INCLUDE = -I./sdl2/include
STM_INCLUDE := ../STM32F411CEU_Handheld_Console/Core/STM32_Handheld_Console/

#CXXFLAGS = -Wall -c -std=c99 -O3 $(SDL_INCLUDE) $(STM_INCLUDE)
CXXFLAGS = -c -std=c99 -O3 $(SDL_INCLUDE) $(STM_INCLUDE)
#LDFLAGS = -lmingw32 -mwindows -mconsole $(SDL_LIB)
LDFLAGS = -lmingw32 -mwindows $(SDL_LIB)
EXE = ./Release/STM32F411CEU_Handheld_Console_Emulator.exe

all: $(EXE) clean

$(EXE): main.o display_driver.o glcdfont.o file_system.o game_engine.o instructions.o script_engine.o syscalls.o editor.o compiler.o input_driver.o menu.o popup.o timer.o system_main.o
	$(CXX) $^ $(LDFLAGS) -o $@

main.o: main.c
	$(CXX) $(CXXFLAGS) $< -o $@

display_driver.o: 		$(STM_INCLUDE)display/display_driver.c
	$(CXX) $(CXXFLAGS) $^ -o $@

glcdfont.o: 			$(STM_INCLUDE)display/glcdfont.c
	$(CXX) $(CXXFLAGS) $^ -o $@

file_system.o: 			$(STM_INCLUDE)file_system/file_system.c
	$(CXX) $(CXXFLAGS) $^ -o $@

game_engine.o: 			$(STM_INCLUDE)game_engine/game_engine.c
	$(CXX) $(CXXFLAGS) $^ -o $@

instructions.o: 		$(STM_INCLUDE)game_engine/script/instructions.c
	$(CXX) $(CXXFLAGS) $^ -o $@

script_engine.o: 		$(STM_INCLUDE)game_engine/script/script_engine.c
	$(CXX) $(CXXFLAGS) $^ -o $@

syscalls.o: 			$(STM_INCLUDE)game_engine/script/syscalls.c
	$(CXX) $(CXXFLAGS) $^ -o $@

editor.o: 				$(STM_INCLUDE)game_engine/editor/editor.c
	$(CXX) $(CXXFLAGS) $^ -o $@

compiler.o: 			$(STM_INCLUDE)game_engine/editor/compiler/compiler.c
	$(CXX) $(CXXFLAGS) $^ -o $@

input_driver.o: 		$(STM_INCLUDE)input/input_driver.c
	$(CXX) $(CXXFLAGS) $^ -o $@

menu.o: 				$(STM_INCLUDE)system/menu.c
	$(CXX) $(CXXFLAGS) $^ -o $@

popup.o: 				$(STM_INCLUDE)system/popup.c
	$(CXX) $(CXXFLAGS) $^ -o $@

timer.o: 				$(STM_INCLUDE)system/timer.c
	$(CXX) $(CXXFLAGS) $^ -o $@

system_main.o: 			$(STM_INCLUDE)system/system_main.c
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	del /q *.o
	@echo.
	@echo.
	@echo *** Compilation successfully completed. ***
	@echo.