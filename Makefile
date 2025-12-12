NAME = scop

SHELL = /bin/bash

COMPILER = c++

FLAGS = -Wall -Werror -Wextra -std=c++2b

SRC_DIR = src

OBJ_DIR = obj

LIB_DIR = libs

INC_DIR = inc

SRCS = $(shell find $(SRC_DIR) -type f -name "*.cpp")

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(COMPILER) $(FLAGS) -I $(INC_DIR) $(GLFW_INC) -c $< -o $@

C_SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")

C_OBJS = $(C_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(COMPILER) $(FLAGS) -I $(INC_DIR) $(GLFW_INC) -c $< -o $@
all: $(NAME)

################################################################################
#                                                                              #
#                                GLFW3 / GLAD                                  #
#                                                                              #
################################################################################

GLFW_DIR = $(LIB_DIR)/glfw

GLFW_INC = -I $(GLFW_DIR)/include/GLFW

GLFW_LINK = -L $(GLFW_DIR)/src -lglfw3 -lGL -ldl -lpthread -lX11 -lXrandr 

GLFW = $(GLFW_DIR)/src/libglfw3.a

$(GLFW): $(GLFW_DIR)
	cd $(GLFW_DIR) && cmake . && make

$(GLFW_DIR):
	git clone https://github.com/glfw/glfw.git $(GLFW_DIR)

$(NAME): $(GLFW) $(OBJS)
	$(COMPILER) $(FLAGS) $(OBJS) $(GLFW_LINK) -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -rf $(LIB_DIR)

re: fclean all

.ONESHELL: run
run: all
	./scop

.PHONY: all clean fclean re run
