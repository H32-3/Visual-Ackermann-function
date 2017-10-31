INPUT=main.c
OPTIONS=-Wall -Wextra -O2
CMDOPTIONS=
LIBS=-lncurses -ltinfo
ODIRS=
COMPILER=gcc
OUTPUT=a.out
INSTALL_DIR=/usr/bin/

all:$(INPUT)
	$(COMPILER) $(LIBS) $(ODIRS) $(OPTIONS) $(CMDOPTIONS) $(INPUT) -o $(OUTPUT)
clean:$(OUTPUT)
	rm $(OUTPUT)
install:$(OUTPUT)
	mv $(OUTPUT) $(INSTALL_DIR)/$(OUTPUT)
