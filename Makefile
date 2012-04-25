SHELL=/bin/bash

CC = gcc
LINK = gcc
LEX = flex
BISON = bison

BISON_FLAGS = --debug -d
LEX_FLAGS = -dv -ll
CFLAGS = -std=c99 -g -I../prosopon-core/include -I../prosopon-stdlib/include -I./include -Isrc
LFLAGS = -lprosopon -lprosopon-stdlib

SRC_DIR = src

OBJS = pro_actor_expr.o pro_become_expr.o pro_case_expr.o pro_constructor_expr.o pro_expr.o \
    pro_expr_list.o pro_expr_type.o pro_identifier_expr.o pro_let_expr.o pro_list_expr.o \
    pro_message_expr.o pro_number_expr.o pro_send_expr.o pro_string_expr.o  \
    pro_capture_identifier_expr.o prosopon_interpreter.o pro_interpreter_state.o gram.tab.o lex.yy.o 

OUT_DIR = build
OUT_OBJS = $(addprefix $(OUT_DIR)/,$(OBJS))


all : $(OUT_OBJS)
	$(LINK) $(LFLAGS) -shared $^ -lc -Wl,-install_name,libprosopon-interpreter.so.1 -o libprosopon-interpreter.so.1

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/lex.yy.c : $(SRC_DIR)/scan.l
	$(LEX) $(LEX_FLAGS) -o $@ $<

$(OUT_DIR)/gram.tab.c : $(SRC_DIR)/gram.y
	$(BISON) $(BISON_FLAGS) -o $@ $<



install:
	cp libprosopon-interpreter.so.1 /usr/local/lib/


.PHONY : doc
doc :
	doxygen Doxyfile


.PHONY : clean
clean :
	rm -f $(OUT_DIR)/*
	if [ -f libprosopon-interpreter.so.1 ]; then rm libprosopon-interpreter*; fi

