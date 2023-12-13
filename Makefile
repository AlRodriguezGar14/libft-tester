# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Werror

# Source files
SRC_DIR := .
CFILES := ${SRC_DIR}/test-functions.c ${SRC_DIR}/printers.c
LIB_DIR := ..

# Executable name
EXECUTABLE := test

# Main target
${EXECUTABLE}: ${CFILES}
	${CC} ${CFLAGS} -o $@ $^ -L${LIB_DIR} -lft
	@echo "Build complete: ./${EXECUTABLE}"

# Clean rule
clean:
	rm -f ${EXECUTABLE}

# Phony target to run the test
run_test: ${EXECUTABLE}
	./${EXECUTABLE}




# The `-lft` flag in the linker command (`-l` followed by `ft`) specifies that the linker should link with a library named `ft`. In the context of your project, it looks like your library file is named `libft.a`. The convention is to name the library file with a "lib" prefix and a file extension, so the library is typically named `libft.a`.
#
# When you use the `-l` flag, the linker assumes that the library file is named `lib<name>.a`. So, `-lft` corresponds to linking with `libft.a`. If your library is named differently, you would adjust the flag accordingly. For example, if your library is named `mylib.a`, you would use `-lmylib` in the linker command.
#
# In summary, the `-lft` flag is a way to tell the linker to link with a library named `libft.a` in this case.
