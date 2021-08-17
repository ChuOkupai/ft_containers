NAME		:= tester
TESTER_FT	:= ft_tester
TESTER_STD	:= std_tester
BUILD_DIR	:= .build
SRC_DIR		:= test
CXX			:= clang++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 -MMD -I./inc
LDFLAGS		:= -lCppUTest -lCppUTestExt
SRC			:= $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FT		:= $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/ft_%.o)
OBJ_STD		:= $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/std_%.o)
OBJ			:= $(OBJ_FT) $(OBJ_STD)

$(NAME): all

all: $(TESTER_FT) $(TESTER_STD)

bonus: all

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(TESTER_FT) $(TESTER_STD)

re: fclean all

run: $(NAME)
	./$(TESTER_FT) -c
	./$(TESTER_STD) -c

$(TESTER_FT): $(OBJ_FT)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(TESTER_STD): $(OBJ_STD)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR):
	mkdir $@

$(BUILD_DIR)/ft_%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -DNAMESPACE=ft -c $< -o $@

$(BUILD_DIR)/std_%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -DNAMESPACE=std -c $< -o $@

.PHONY: $(NAME) all bonus clean fclean re run

-include $(OBJ:.o=.d)
