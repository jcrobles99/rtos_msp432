# invoke SourceDir generated makefile for release.pem4f
release.pem4f: .libraries,release.pem4f
.libraries,release.pem4f: package/cfg/release_pem4f.xdl
	$(MAKE) -f C:\Users\jcarl\workspace_v8\Proyecto_final_eq_v2\tirtos_builds_MSP_EXP432P401R_release_ccs/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\jcarl\workspace_v8\Proyecto_final_eq_v2\tirtos_builds_MSP_EXP432P401R_release_ccs/src/makefile.libs clean

