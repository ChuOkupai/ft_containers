NAME		:= tester
BUILD_DIR	:= .build
SRC_DIR		:= test
CXX			:= clang++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 -MMD -I./inc
LDFLAGS		:= -lCppUTest -lCppUTestExt
SRC			:= $(wildcard $(SRC_DIR)/*.cpp)
OBJ			:= $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

all: $(NAME)

bonus: all

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$< -c

$(BUILD_DIR):
	mkdir $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all bonus clean fclean re run

-include $(OBJ:.o=.d)
