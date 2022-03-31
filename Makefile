objects	= main.o dcl.o gettoken.o bsearch.o
header = src/dcl.h

SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin
EXE		:= bin/dcl
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP 
CFLAGS   := -Wall              

all	:	$(EXE)
.PHONY	:	all clean

$(EXE): $(OBJ)
	    $(CC)  $^ -o $@
clean:
	    @$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
				$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
-include $(OBJ:.o=.d)$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

