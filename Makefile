#common makefile header

DIR_INC = ./
DIR_BIN = ./bin/
DIR_LIB = 

TARGET = asr
BIN_TARGET = $(DIR_BIN)/$(TARGET)

OBJ := $(patsubst %.c, %.o, $(wildcard *.c))

$(TARGET) : $(OBJ)
		gcc -o $@ $<
		@mv $(TARGET) $(DIR_BIN)

%.o : %.c
		gcc -c $< -o $@


clean: 
		@rm -f $(OBJ) $(TARGET) $(BIN_TARGET) 


.PHONY:clean




