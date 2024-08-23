CC := g++
CFLAGS := -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

SOURCES := source\iosolver.cpp source\main.cpp source\read.cpp source\solve.cpp source\utilities.cpp source\testsys.cpp
OBJ := build\iosolver.o build\main.o build\read.o build\solve.o build\utilities.o build\testsys.o

BUILD := build

INCLUDES := include
OUTPUT := boot.exe

$(OUTPUT): $(OBJ)
	$(CC) $(OBJ) -o $@

build\iosolver.o:
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c source\iosolver.cpp -o $@

build\main.o:
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c source\main.cpp -o $@

build\read.o:
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c source\read.cpp -o $@

build\solve.o:
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c source\solve.cpp -o $@

build\utilities.o:
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c source\utilities.cpp -o $@

build\testsys.o:
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c source\testsys.cpp -o $@

clean:
	del build\*.o $(OUTPUT)
