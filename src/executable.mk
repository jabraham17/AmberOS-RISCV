-include $(ROOT_PROJECT_DIRECTORY)src/sources.mk
$(TARGET): $(OBJECTS) $(LIBRARIES_FILE_NAMES) Makefile
	$(LD) $(OBJECTS) $(LDFLAGS) -L$(LIB_DIRECTORY) $(LDLIBS) -o $@
