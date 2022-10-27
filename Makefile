CC = g++

FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations \
		-Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual        \
		-Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op                 \
		-Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192         \
		-Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE

SRC = main.cpp src/io.cpp src/sort.cpp src/poem.cpp src/test.cpp

BUILDDIR = obj

$(foreach SOURCE,$(SRC),$(eval $(call CC_RULE,$(SOURCE))))

OBJ = $(addprefix $(BUILDDIR)/,$(subst /,_,$(patsubst %.cpp,%.o,$(SRC))))

NAME = do

all: $(SRC) $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

define CC_RULE =
$(BUILDDIR)/$(subst /,_,$(patsubst %cpp,%o,$(SOURCE))): $(SOURCE)
	$(CC) $(FLAGS) -c -o $@ $<
endef

clean:
	rm $(OBJ) do.exe
	
