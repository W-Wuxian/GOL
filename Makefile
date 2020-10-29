#--------------------------------------------------------------------------
# The compiler: g++ for C++ program:
COMP = g++
#--------------------------------------------------------------------------
#--------------------------------------------------------------------------
# Version of g++:
VER = -std=c++17
#--------------------------------------------------------------------------
#**************************************************************************
# Compiler flags:
#**************************************************************************
# -g    -> adds debugging informations to the executable file
# -pg   -> add valdrind
# -Wall -> turn on most compiler warnings
#**************************************************************************
#--------------------------------------------------------------------------
DEBUG = no
CASE = 0
# Options en mode optimisé - La variable NDEBUG est définie:
OPTIM_FLAG = -O3 -DNDEBUG -DCASE=$(CASE) -Wall
# Options en mode debig - La variable NDEBUG n'est pas définie:
DEBUG_FLAG = -pg -g -DCASE=$(CASE) -O0 -Wall
ifeq ($(DEBUG), yes)
	OPTION_FLAG = $(DEBUG_FLAG)
else
	OPTION_FLAG = $(OPTIM_FLAG)
endif
#--------------------------------------------------------------------------
# On choisit comment on compile:
CXX_FLAGS = $(VER) $(OPTION_FLAG)
#--------------------------------------------------------------------------
# Le nom de l'exécutable:
EXEC = GOL
RUN = ./$(EXEC)
ifeq ($(DEBUG), yes)
	RUN = valgrind --leak-check=yes ./$(EXEC)
else
	RUN = ./$(EXEC)
endif

#--------------------------------------------------------------------------
# Les fichiers source à compiler:
SRC = main.cc GOL.cpp
#--------------------------------------------------------------------------
# La commande complète: compile ssi une fichier a été modifié:
$(EXEC): $(SRC)
	$(COMP) $(CXX_FLAGS) $(SRC) -o $(EXEC)
#--------------------------------------------------------------------------
# MAKEFILE COMMAND:
.PHONY: help
help :
	@echo "**************************************************************************"
	@echo "************** make all cmd : for compilation: ***************************"
	@echo "**************************************************************************"
	@echo "make all : to compile in optimization mode (default: DEBUG=no)"
	@echo "make all DEBUG=yes : to compile in debug mode"
	@echo "make all CASE={0,1,2,>2} : to set the init case (default is 0) such that:"
	@echo "CASE=0  |---> Random pattern initialization (Default)"
	@echo "CASE=1  |---> Clown pattern initialization (Show Clown at iteration 110)"
	@echo "CASE=2  |---> Canon pattern initialization"
	@echo "CASE>2  |---> Custom pattern initialization (From a file (IJV) )"
	@echo "        |---> In this case the path file need to be give from argc"
	@echo "        |---> when using make run cmd"
	@echo "**************************************************************************"
	@echo "************** make run cmd : for execution: *****************************"
	@echo "**************************************************************************"
	@echo "make run : to run the execution file in optim mode (default: DEBUG=no)"
	@echo "make run DEBUG=yes : to run in debug mode (only if: make all DEBUG=yes)"
	@echo "make run dir file : to give the Custom pattern initialization using a file"
	@echo "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
	@echo "EXAMPLES:"
	@echo "1/ make clean3 all run DEBUG=yes CASE=3 Custom mat.txt"
	@echo "2/ make clean3 && make all DEBUG=yes CASE=3 && make run DEBUG=yes Custom"
	@echo "default file is mat.txt"
	@echo "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
	@echo "**************************************************************************"
	@echo "************** make Rrun cmd : to execute Rscript: ***********************"
	@echo "**************************************************************************"
	@echo "make Rrun : to run Rscript (args[1]:)dirpath without ./ (args[2]:)filename"
	@echo "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
	@echo "EXAMPLES:"
	@echo "make Rrun Canon data or make Rrun dir1/Canon data"
	@echo "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
	@echo "**************************************************************************"
	@echo "************** make Grun cmd : to execute gprof: *************************"
	@echo "**************************************************************************"
	@echo "make Grun :  only if DEBUG=yes, to call gprof"
	@echo "**************************************************************************"
	@echo "************** make clean cmd : to clean : *******************************"
	@echo "**************************************************************************"
	@echo "make clean1 : to clean *.o *~ $(EXEC)"
	@echo "make clean2 : to clean *.mp4 *.gif"
	@echo "make clean3 : to do clean1 and clean2"
	@echo "**************************************************************************"
# 1/ Evite de devoir connaitre le nom de l'exécutable: compilation:
.PHONY: all opt deb clean1 clean2 clean3
all : $(EXEC)
	@echo "DEBUG="$(DEBUG)
#--------------------------------------------------------------------------
# 2/ Exécute :
run :
	$(RUN) $(filter-out clean3 all run,$(MAKECMDGOALS))
	@echo "DEBUG="$(DEBUG)
%:
	@:
#--------------------------------------------------------------------------
# 3/ Run R script for Post-treatment Data:
Rrun :
	Rscript RGOL.R $(filter-out Rrun,$(MAKECMDGOALS))
# 4/ Run gprof for time call functions:
Grun :
	gprof -l $(EXEC) gmon.out > analysis.txt
#--------------------------------------------------------------------------
# 4/ Supprime l'exécutable, les fichiers binaires (.o) et les fichiers
# temporaires de sauvegarde (~):
clean1 :
	rm -f *.o *~ $(EXEC)
#--------------------------------------------------------------------------
# 5/ Supprime les fichiers .mp4 .gif;
clean2 :
	rm -f *.mp4 *.gif
# 6/ Supprime via clean1 et clean2:
clean3 :
	rm -f *.o *~ $(EXEC) *.mp4 *.gif
#**************************************************************************
#**************************************************************************
