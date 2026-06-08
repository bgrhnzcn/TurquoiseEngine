NAME = scop

SHELL = /bin/bash

CXX = c++

CXX_FLAGS = -Wall -Werror -Wextra -std=c++26 -freflection -MD -g

CC = cc

CC_FLAGS = -Wall -Werror -Wextra -g

SRC_DIR = src

OBJ_DIR = obj

LIB_DIR = libs

INC_DIR = inc

DEP_DIR = deps

SRCS = $(shell find $(SRC_DIR) -type f -name "*.cpp")

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

DEPS = $(OBJS:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

all: $(NAME)

################################################################################
#                                                                              #
#                                Object Rule                                   #
#                                                                              #
################################################################################

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	mkdir -p $(dir $(DEP_DIR)/$*.d)
	$(CXX) $(CXX_FLAGS) -I $(INC_DIR) -I $(GLFW_INC) -I $(GLAD_INC) \
		-MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@

################################################################################
#                                                                              #
#                                GLFW3 / GLAD                                  #
#                                                                              #
################################################################################

GLAD_DIR = $(LIB_DIR)/glad

GLAD_INC = $(GLAD_DIR)

GLAD_SRC = $(GLAD_DIR)/glad.c

GLAD_OBJ = $(GLAD_SRC:.c=.o)

GLAD_LINK = -L $(GLAD_DIR) -lglad

GLAD = $(GLAD_DIR)/libglad.a

GLFW_DIR = $(LIB_DIR)/glfw

GLFW_INC = $(GLFW_DIR)/include

GLFW_LINK = -L $(GLFW_DIR)/src -lglfw3 -lGL -ldl -lpthread -lX11 -lXrandr

GLFW = $(GLFW_DIR)/src/libglfw3.a

$(GLAD): $(GLAD_OBJ)
	$(AR) rcs $@ $<

%.o: %.c
	$(CC) $(CC_FLAGS) -I $(GLAD_INC) -c $< -o $@

$(GLFW): $(GLFW_DIR)
	cd $< && cmake . && make

$(GLFW_DIR):
	git clone https://github.com/glfw/glfw.git $@

$(NAME): $(GLFW) $(GLAD) $(OBJS)
	$(CXX) $(CXX_FLAGS) $(OBJS) $(GLAD_LINK) $(GLFW_LINK) -o $@

clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean: clean
	rm -f $(NAME)

hclean: fclean
	rm -rf $(GLFW_DIR) $(GLAD)

re: fclean all

.ONESHELL: run
run: all
	./scop

-include $(DEPS)

.PHONY: all clean fclean re run

help:
	@echo 
