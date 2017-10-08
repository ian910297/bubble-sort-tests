CC ?= gcc
CFLAGS_common ?= -Wall -std=gnu99 -g -DDEBUG -O0
RM = rm -f 

EXEC = test
GIT_HOOKS := .git/hooks/pre-commit

.PHONY: all
all: $(GIT_HOOKS) $(EXEC)
	$(CC) $(CFLAGS_common) -o $(EXEC) test.c

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o
