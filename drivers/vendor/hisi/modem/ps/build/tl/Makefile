
# What are targets ?
$(warning The targets are $(MAKECMDGOALS).)

# guess the Top dir
BALONG_TOPDIR ?= $(patsubst %modem/ps,%,$(CURDIR))

# Make sure that there are no spaces in the absolute path; the build system can't deal with them.
ifneq ($(words $(BALONG_TOPDIR)),1)
$(warning ************************************************************)
$(warning You are building in a directory whose absolute path contains a space character)
$(warning "$(BALONG_TOPDIR)")
$(warning Please move your source tree to a path that does not contain any spaces.)
$(warning ************************************************************)
$(error Directory names containing spaces not supported)
endif

# include the define at the top
include $(BALONG_TOPDIR)/build/scripts/make_base.mk

# process
.PHONY:all mcore acore bootrom bootloader
all: mcore acore bootrom bootloader
	@echo do [$@]
	
mcore : 
	$(MAKE)  $(OBB_JOBS)  -f makefile_mcore.mk
	
bootrom : 
	@echo do [$@]

acore : 
#	$(MAKE)  $(OBB_JOBS)  -f makefile_acore.mk

bootloader : 
	@echo do [$@]

# clean
.PHONY: clean
clean:
ifeq ($(OBB_CORE_NAME),all)
	$(MAKE)  $(OBB_JOBS)  -f makefile_mcore.mk $@
#	$(MAKE)  $(OBB_JOBS)  -f makefile_acore.mk $@
else
	$(MAKE)  $(OBB_JOBS)  -f makefile_$(OBB_CORE_NAME).mk $@
endif
	
	@echo "PS_CODE clean complete."
