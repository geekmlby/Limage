#############################################################################################
#									The Makefile of Limage
#  Automatically compile the .h header files in the "inc" folder 
#  and the .cc source files in the "src" folder.
#  Link the .lib files in the "lib" folder. 
#  Generate the .o files and save them in the "obj" folder.
#  Generate the executable file and save it in the "bin" folder.
#  Modify TARGETS,CC,CFLAGS and LDFLAG will be able to complete the project configuration.
#
#																				by WangLi
#																				2017/01/22
#############################################################################################
PROJECT_TOP_DIR = $(shell pwd)
PROJECT_BIN_DIR = $(PROJECT_TOP_DIR)/bin
PROJECT_SRC_DIR = $(PROJECT_TOP_DIR)/src
PROJECT_INC_DIR = $(PROJECT_TOP_DIR)/inc
PROJECT_LIB_DIR = $(PROJECT_TOP_DIR)/lib
PROJECT_OBJ_DIR = $(PROJECT_TOP_DIR)/obj

CC := g++
TARGET := $(PROJECT_BIN_DIR)/Limage
CFLAGS := -g -I$(PROJECT_INC_DIR)
LFLAGS := -L$(PROJECT_LIB_DIR)
COPENCVFLAG := -I/usr/local/include/opencv -I/usr/local/include
LOPENCVFLAG := -L/usr/local/lib -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core 

srcfiles := $(wildcard $(PROJECT_SRC_DIR)/*.cc)
srcnames := $(notdir $(srcfiles))
objnames := $(patsubst %.cc,%.o,$(srcnames))
objfiles := $(addprefix $(PROJECT_OBJ_DIR)/,$(objnames))

all : $(objfiles)
	@echo "***********Start compile TARGET!***********"
	$(CC) $(COPENCVFLAG) $(objfiles) -o $(TARGET) $(LOPENCVFLAG)
$(PROJECT_OBJ_DIR)/%.o : $(PROJECT_SRC_DIR)/%.cc
	@echo "***********Start compile objfiles!***********"
	$(CC) -c $(CFLAGS) $(COPENCVFLAG) $< -o $@ $(LOPENCVFLAG)

.PHONY : clean
clean:
	@echo "***********Start clean!***********"	
	rm $(objfiles)
	rm $(TARGET)
	rm $(PROJECT_TOP_DIR)/*.txt


















