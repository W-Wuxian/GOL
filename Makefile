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
# Options en mode optimisé - La variable NDEBUG est définie:
OPTIM_FLAG = -O3 -DNDEBUG -Wall
# Options en mode debig - La variable NDEBUG n'est pas définie:
DEBUG_FLAG = -pg -g -O0 -Wall
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
	@echo "make all : to compile in optimization mode (default: DEBUG=no)"
	@echo "make all DEBUG=yes : to compile in debug mode"
	@echo "make run : to run the execution file in optim mode (default: DEBUG=no)"
	@echo "make run DEBUG=yes : to run in debug mode (only if: make all DEBUG=yes)"
	@echo "make Rrun : to run Rscript"
	@echo "make Grun :  only if DEBUG=yes, to call gprof"
	@echo "make clean1 : to clean *.o *~ $(EXEC)"
	@echo "make clean2 : to clean *.mp4 *.gif"
	@echo "make clean3 : to do clean1 and clean2"
# 1/ Evite de devoir connaitre le nom de l'exécutable: compilation:
.PHONY: all opt deb clean1 clean2 clean3
all : $(EXEC)
	@echo "DEBUG="$(DEBUG)
#--------------------------------------------------------------------------
# 2/ Exécute :
run :
	$(RUN)
	@echo "DEBUG="$(DEBUG)
#--------------------------------------------------------------------------
# 3/ Run R script for Post-treatment Data:
Rrun :
	Rscript RGOL.R
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
