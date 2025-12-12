NAME = scop

SHELL = /bin/bash

CXX = c++

CXX_FLAGS = -Wall -Werror -Wextra -std=c++2b -g

CC = cc

CC_FLAGS = -Wall -Werror -Wextra -g

SRC_DIR = src

OBJ_DIR = obj

LIB_DIR = libs

INC_DIR = inc

SRCS = $(shell find $(SRC_DIR) -type f -name "*.cpp")

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) -I $(INC_DIR) -I $(GLFW_INC) -I $(GLAD_INC) -c $< -o $@

all: $(NAME)

GLAD_DIR = $(LIB_DIR)/glad

GLAD_INC = $(GLAD_DIR)

GLAD_SRC = $(GLAD_DIR)/glad.c

GLAD_OBJ = $(GLAD_SRC:.c=.o)

GLAD_LINK = -L $(GLAD_DIR) -lglad

GLAD = $(GLAD_DIR)/libglad.a

$(GLAD): $(GLAD_OBJ)
	$(AR) rcs $(GLAD) $(GLAD_OBJ)

%.o: %.c
	$(CC) $(CC_FLAGS) -I $(GLAD_INC) -c $< -o $@

$(GLFW_DIR):
	git clone https://github.com/glfw/glfw.git $(GLFW_DIR)

################################################################################
#                                                                              #
#                                GLFW3 / GLAD                                  #
#                                                                              #
################################################################################

GLFW_DIR = $(LIB_DIR)/glfw

GLFW_INC = $(GLFW_DIR)/include/GLFW

GLFW_LINK = -L $(GLFW_DIR)/src -lglfw3 -lGL -ldl -lpthread -lX11 -lXrandr

GLFW = $(GLFW_DIR)/src/libglfw3.a

$(GLFW): $(GLFW_DIR)
	cd $(GLFW_DIR) && cmake . && make

$(GLFW_DIR):
	git clone https://github.com/glfw/glfw.git $(GLFW_DIR)

$(NAME): $(GLFW) $(GLAD) $(OBJS)
	$(CXX) $(CXX_FLAGS) $(OBJS) $(GLAD_LINK) $(GLFW_LINK) -o $@

clean:
	rm -rf $(OBJ_DIR) $(GLAD_OBJ)

fclean: clean
	rm -f $(NAME) $(GLAD)

hclean: fclean
	rm -rf $(GLFW_DIR)

re: fclean all

.ONESHELL: run
run: all
	./scop

.PHONY: all clean fclean re run
