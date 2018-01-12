INPUT=main.c
OPTIONS=-Wall -Wextra -Ofast
CMDOPTIONS=
LIBS=-lncurses -ltinfo
ODIRS=
COMPILER=gcc
OUTPUT=ackermann
INSTALL_DIR=/usr/bin/

all:$(INPUT)
	$(COMPILER) $(LIBS) $(ODIRS) $(OPTIONS) $(CMDOPTIONS) $(INPUT) -o $(OUTPUT)
clean:$(OUTPUT)
	rm $(OUTPUT)
install:$(OUTPUT)
	mv $(OUTPUT) $(INSTALL_DIR)/$(OUTPUT)
