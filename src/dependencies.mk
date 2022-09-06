

kernel=stdlib drivers uart custom_instruction
main=bootloader uart stdlib custom_instruction drivers kernel firmware 
uart=stdlib
custom_instruction=firmware
firmware=stdlib uart

define make_depen
$(eval $1: $($1))
endef
map = $(foreach a,$(2),$(call $(1),$(a)))
define make_prereqs
$(call map,make_depen,main,bootloader,uart,stdlib,custom_instruction,drivers,kernel,firmware)
endef
