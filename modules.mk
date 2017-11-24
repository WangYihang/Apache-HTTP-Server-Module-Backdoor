mod_backdoor.la: mod_backdoor.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_backdoor.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_backdoor.la
