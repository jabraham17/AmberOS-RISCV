-include $(ROOT_PROJECT_DIRECTORY)options.mk
-include $(ROOT_PROJECT_DIRECTORY)src/dependencies.mk
LIBRARIES= $(main)
TARGET=$(BIN_DIRECTORY)kernel.elf
override LDFLAGS+= -T link.ld --whole-archive
-include $(ROOT_PROJECT_DIRECTORY)src/executable.mk
