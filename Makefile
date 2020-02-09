PROJECTDIR = $(pwd)
DIRNAME = `basename $(PWD)`


all :
	@echo "Usage Makefile in "$(DIRNAME)
	@echo ""
	@echo "clean_all => clean up everything in project"
	@echo "archive => create targz archive in parent folder"
	@echo ""



.PHONY: clean_all

clean_all :
	cd code/Python &&\
	./clean.sh
	@echo "Python directory cleaned"
	cd code/CPP/TESTS/CNN_FULL_TEST &&\
	make mrproper
	cd code/CPP/TESTS/EdgeDetectorTest &&\
	make mrproper
	cd code/CPP/TESTS/AffichageMultiplev2_test &&\
	make mrproper
	@echo "C++ directory cleaned"
	@echo "Project directory cleaned"

archive :
	make clean_all
	cd .. && tar -czvf CNN_project-`whoami`-`date +%d-%m-%H-%M`.tgz $(DIRNAME) && cd $(DIRNAME) 
