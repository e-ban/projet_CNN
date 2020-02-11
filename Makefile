PROJECTDIR = $(pwd)
DIRNAME = `basename $(PWD)`


all :
	@echo "Usage Makefile in "$(DIRNAME)
	@echo ""
	@echo "clean_all => clean up everything in project"
	@echo "archive => create targz archive in parent folder"
	@echo "install_ac_libs => install librairies ac_types and ac_maths in libs/"
	@echo "uninstall_ac_libs => uninstall librairies ac_types and ac_maths in libs/"


install_ac_libs :
	@echo "Installation of ac_types and ac_maths"
	mkdir -p libs
	cd libs && git clone https://github.com/hlslibs/ac_types.git &&\
	git clone https://github.com/hlslibs/ac_math.git


uninstall_ac_libs :
	rm -rf libs

.PHONY: clean_all cleaner
clean_all :
	rm -rf doc/doxygen
	cd code/Python &&\
	./clean.sh
	@echo "Python directory cleaned"
	cd code/CPP/TESTS/CNN_FULL &&\
	make mrproper
	cd code/CPP/TESTS/EdgeDetector &&\
	make mrproper
	cd code/CPP/TESTS/MultipleDisplay &&\
	make mrproper
	@echo "C++ directory cleaned"
	@echo "Project directory cleaned"

cleaner :
	make clean_all
	make uninstall_ac_libs

archive :
	make cleaner
	cd .. && tar -czvf CNN_project-`whoami`-`date +%d-%m-%H-%M`.tgz $(DIRNAME) && cd $(DIRNAME)
