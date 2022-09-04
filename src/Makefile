-include $(ROOT_PROJECT_DIRECTORY)options.mk

TOPTARGETS=all clean cppcheck
SUBDIRS= bootloader kernel main

.PHONY: $(TOPTARGETS)
$(TOPTARGETS): $(SUBDIRS)

-include $(ROOT_PROJECT_DIRECTORY)src/dependencies.mk
$(call make_prereqs)

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	@printf "$(COLOR_RED)$(COLOR_BOLD)MAKE -C src/$@ $(MAKECMDGOALS)$(COLOR_RESET)\n"
	@$(MAKE) --no-print-directory -C $@ $(MAKECMDGOALS)
