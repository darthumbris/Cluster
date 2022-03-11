# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ngerrets <ngerrets@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/07/15 14:47:03 by ngerrets      #+#    #+#                  #
#    Updated: 2022/03/10 14:58:55 by ngerrets      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

MAIN ?= main.c

NAME := cluster
COMPILE_FLAGS ?= -Wall -Wextra -Werror -O3
LINKING_FLAGS ?= libmlx42.a -lglfw -ldl -lm -O3 -L "/Users/$(USER)/.brew/opt/glfw/lib/"

ifdef BOTS
	COMPILE_FLAGS += -DBOTS=true
endif

ifdef NO_GRID
	COMPILE_FLAGS += -DNO_GRID=$(NO_GRID)
endif

ifdef NO_GUI
	COMPILE_FLAGS += -DNO_GUI=$(NO_GUI)
endif

ifdef NO_ANIM
	COMPILE_FLAGS += -DNO_ANIM=$(NO_ANIM)
endif

ifdef NO_BG_TILES
	COMPILE_FLAGS += -DNO_BG_TILES=$(NO_BG_TILES)
endif

ifdef ANIM_SPEED_MODIFIER
	COMPILE_FLAGS += -DANIM_SPEED_MODIFIER=$(ANIM_SPEED_MODIFIER)
endif


ifdef SCREEN_WIDTH
	COMPILE_FLAGS += -DSCREEN_WIDTH=$(SCREEN_WIDTH)
endif

ifdef SCREEN_HEIGHT
	COMPILE_FLAGS += -DSCREEN_HEIGHT=$(SCREEN_HEIGHT)
endif

ifdef SCREEN_TITLE
	COMPILE_FLAGS += -DSCREEN_TITLE=$(SCREEN_TITLE)
endif

ifdef SCREEN_RESIZE
	COMPILE_FLAGS += -DSCREEN_RESIZE=$(SCREEN_RESIZE)
endif


ifdef SIDE_LENGTH
	COMPILE_FLAGS += -DSIDE_LENGTH=$(SIDE_LENGTH)
endif

ifdef BOARD_WIDTH
	COMPILE_FLAGS += -DBOARD_WIDTH=$(BOARD_WIDTH)
endif


ifdef COLORS_TO_PLAY
	COMPILE_FLAGS += -DCOLORS_TO_PLAY=$(COLORS_TO_PLAY)
endif

ifdef COLOR_AMOUNT_PER_TURN
	COMPILE_FLAGS += -DCOLOR_AMOUNT_PER_TURN=$(COLOR_AMOUNT_PER_TURN)
endif

ifdef COLORS_SETS_IN_BAG
	COMPILE_FLAGS += -DCOLORS_SETS_IN_BAG=$(COLORS_SETS_IN_BAG)
endif

ifdef TOTAL_TOKENS
	COMPILE_FLAGS += -DTOTAL_TOKENS=$(TOTAL_TOKENS)
endif


ifdef TO_WIN
	COMPILE_FLAGS += -DTO_WIN=$(TO_WIN)
endif


ifdef P1_IN
	COMPILE_FLAGS += -DP1_IN=$(P1_IN)
endif

ifdef P2_IN
	COMPILE_FLAGS += -DP2_IN=$(P2_IN)
endif

ifdef P1_OUT
	COMPILE_FLAGS += -DP1_OUT=$(P1_OUT)
endif

ifdef P2_OUT
	COMPILE_FLAGS += -DP2_OUT=$(P2_OUT)
endif


ifdef DELAY_US
	COMPILE_FLAGS += -DDELAY_US=$(DELAY_US)
endif


ifdef HEX_HEIGHT
	COMPILE_FLAGS += -DHEX_HEIGHT=$(HEX_HEIGHT)
endif

ifdef BACKGROUND_COLOR
	COMPILE_FLAGS += -DBACKGROUND_COLOR=$(BACKGROUND_COLOR)
endif

ifdef HEX_OUTLINE_COLOR
	COMPILE_FLAGS += -DHEX_OUTLINE_COLOR=$(HEX_OUTLINE_COLOR)
endif

ifdef WHITE
	COMPILE_FLAGS += -DWHITE=$(WHITE)
endif

ifdef ANGLE
	COMPILE_FLAGS += -DANGLE=$(ANGLE)
endif

ifdef HIGHLIGHT
	COMPILE_FLAGS += -DHIGHLIGHT=$(HIGHLIGHT)
endif

ifdef TAN_ANGLE
	COMPILE_FLAGS += -DTAN_ANGLE=$(TAN_ANGLE)
endif

SRC_DIR ?= src
HDR_DIR ?= include
OBJ_DIR ?= obj

SOURCES :=
include make/sources.mk
HEADERS :=
include make/headers.mk

SOURCES += main/$(MAIN)
OBJECTS := $(patsubst %,$(OBJ_DIR)/%,$(SOURCES:.c=.o))

.PHONY: all files
all: libmlx42.a $(NAME)

bots:
	@make BOTS=1

files:
	./make/make_sources.sh

$(NAME): $(HEADERS) $(OBJECTS)
	@echo "\nLinking files..."
	@$(CC) $(OBJECTS) -o $(NAME) $(LINKING_FLAGS)
	@echo "Done!"

libmlx42.a:
	@make -C lib/MLX42 DEBUG=1
	@cp lib/MLX42/libmlx42.a .

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@echo "Compiling: $@"
	@mkdir -p $(@D)
	@$(CC)  $(COMPILE_FLAGS) $(patsubst %,-I%,$(dir $(HEADERS))) -c -o $@ $<

.PHONY: clean fclean re
clean:
	@rm -Rf $(OBJ_DIR)/
	@make -C lib/MLX42 clean
	@echo "Objects cleaned."

fclean: clean
	@rm -f $(NAME)
	@make -C lib/MLX42 fclean
	@rm -f libmlx42.a
	@echo "Binaries cleaned."

re: fclean all

.PHONY: print
print:
	@echo "---HEADERS: $(HEADERS)" | xargs -n1
	@echo "---SOURCES: $(SOURCES)" | xargs -n1
	@echo "---OBJECTS: $(OBJECTS)" | xargs -n1

.PHONY: run
run: all
	./$(NAME)
