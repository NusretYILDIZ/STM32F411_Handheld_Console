CXX = gcc

SDL_LIB = -L../sdl2/lib -lSDL2main -lSDL2
SDL_INCLUDE = -I../sdl2/include
STM_INCLUDE := ../../STM32F411_Handheld_Console/Core/STM32_Handheld_Console/

#CXXFLAGS = -Wall -c -std=c99 -O3 $(SDL_INCLUDE) $(STM_INCLUDE)
CXXFLAGS = -c -std=c99 -O3 $(SDL_INCLUDE) $(STM_INCLUDE)
LDFLAGS = -lmingw32 -mwindows -mconsole $(SDL_LIB)
#LDFLAGS = -lmingw32 -mwindows $(SDL_LIB)
EXE = ./Release/Gamepad_Input_Server_for_STM32_Handheld_Console.exe

all: $(EXE) clean

$(EXE): main.o input_driver.o
	$(CXX) $^ $(LDFLAGS) -o $@

main.o: main.c
	$(CXX) $(CXXFLAGS) $< -o $@

input_driver.o: 		$(STM_INCLUDE)input/input_driver.c
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	del /q *.o
	@echo.
	@echo.
	@echo *** Compilation successfully completed. ***
	@echo.