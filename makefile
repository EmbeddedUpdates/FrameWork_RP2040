
#Compiler Executables (In $(PATH) or Absolute path)
AS = arm-none-eabi-as
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
BIN = arm-none-eabi-objcopy

#Makefile.project.part.defines and component specific make files should extend these
C_SOURCE_FILES = 
S_ASSEMBLY_FILES = 
C_OBJ_FILES = 
S_OBJ_FILES =
INCDIR = 
	
#define output folders e.g. obj/lst/ouput
OBJ_DIR = obj
LST_DIR = lst
OUT_DIR = out

#$(info Executing: $(PROJECT_NAME)/makefile)

#include project specific make configuration
include makefile.project.config
include makefile.project.part.defines

#include directories as compiler options
INC := -I$(INCDIR) -I/usr/local/include
INC += $(addprefix -I, $(INCLUDE_PATH))

#Compiler flags
COMPILER_DEFINES += 
CCFLAGS = -mthumb -mcpu=cortex-m0plus -ggdb $(INC) -Wall -DENABLE_BRS_ASSERT#$(COMPILER_DEFINES)
LDFLAGS = -T $(LINKER_COMMAND_FILE) -Map $(PROJECT_NAME).map
#-L/Library/Developer/CommandLineTools/usr/lib/clang/13.1.6/lib/darwin/libclang_rt.builtins-arm.a -lgcc
ASFLAGS = 

#----------------------------------------------------
# General Makefile configuration - not to be adjusted
#----------------------------------------------------

#list all object files from both C and S files

#object files of all compiled C files from components
#e.g. Component/brs_rp2040/source/brs_rp2040.c -> Components/brs_rp2040/Source/brs_rp2040.o
C_OBJS=$(C_SOURCE_FILES:.c=.o)

#object files of all compiled C files from local application source folder
#e.g. ./Source/main.c -> ./Source/main.o
TEMP_APP_OBJ=$(APP_SOURCE_LIST:.c=.o)
#Append root to appl prefix for use with obj directory
#e.g. ./Source/main.c -> ./Source/main.o -> Applications/rp2040_brsTest/Source/main.o
C_OBJS_APP_O=$(addprefix $(ROOT_TO_APPL)/, $(TEMP_APP_OBJ))
#Append relative path to root for use with CC
#e.g. ./Source/main.c -> ./Source/main.o -> Applications/rp2040_brsTest/Source/main.o -> 
#     ./../../Applications/rp2040_brsTest/Source/main.o
C_OBJS_APP_C=$(addprefix $(ROOT_DIR)/, $(C_OBJS_APP_O))

#Object files of all compiled assembly files
S_OBJS=$(S_ASSEMBLY_FILES:.s=.o)

#Collect all Object files for dependencies of LD (requires relative root from current folder)
LD_DEPEND_OBJS = $(C_OBJS) $(S_OBJS) $(C_OBJS_APP_C)
#Collect all object files for invoking LD, which is absolute within obj/ folder
OBJS = $(C_OBJS) $(S_OBJS) $(C_OBJS_APP_O)
#All objects that are located in the local artifact folder obj/. This should contain all 
#    .o files to be linked in LD
OBJOBJS = $(addprefix obj/, $(OBJS))

# report all obj/ objects for verification.
#$(info OBJOBJS: $(OBJOBJS))
#$(info OBJS: $(OBJS))
#$(info C_OBJS: $(C_OBJS))
#$(info S_OBJS: $(S_OBJS))
#$(info C_OBJS_APP_O: $(C_OBJS_APP_O))

#default make target
all: flash

rebuild: cleaner flash

flash : $(OUT_DIR)/$(PROJECT_NAME).elf $(OUT_DIR)/$(PROJECT_NAME).bin
	@mkdir -p $(OUT_DIR)
	$(info ELF2UF2: $(OUT_DIR)/$(PROJECT_NAME).bin)
	@$(ELF2UF2) $(OUT_DIR)/$(PROJECT_NAME).bin $(OUT_DIR)/$(PROJECT_NAME).uf2
	$(info Done!)

# notmain.uf2 : notmain.bin makeuf2
# 	./makeuf2 notmain.bin notmain.uf2

# start.o : start.s
# 	$(ARMGNU)-as $(AOPS) start.s -o start.o

# notmain.o : notmain.c
# 	$(ARMGNU)-gcc $(COPS) -mthumb -c notmain.c -o notmain.o

# notmain.bin :               memmap.ld start.o notmain.o
# 	$(ARMGNU)-ld $(LOPS) -T memmap.ld start.o notmain.o -o notmain.elf
# 	$(ARMGNU)-objdump -D notmain.elf > notmain.list
# 	$(ARMGNU)-objcopy -O binary notmain.elf notmain.bin

$(OUT_DIR)/$(PROJECT_NAME).bin : $(OUT_DIR)/$(PROJECT_NAME).elf
	@mkdir -p $(OUT_DIR)
	$(info OBJCOPY $(PROJECT_NAME))
	@arm-none-eabi-objcopy -O binary $(OUT_DIR)/$(PROJECT_NAME).elf $(OUT_DIR)/$(PROJECT_NAME).bin
	@arm-none-eabi-objcopy -O ihex $(OUT_DIR)/$(PROJECT_NAME).elf $(OUT_DIR)/$(PROJECT_NAME).hex
	@arm-none-eabi-objdump -d $(OUT_DIR)/$(PROJECT_NAME).elf > $(OUT_DIR)/$(PROJECT_NAME).list

$(OUT_DIR)/$(PROJECT_NAME).elf : $(OBJOBJS) $(LINKER_COMMAND_FILE)
	@mkdir -p $(OUT_DIR)
	@$(LD) -o $@ $(OBJOBJS) $(LDFLAGS)
	$(info LD: $(OUT_DIR)/$(PROJECT_NAME).elf $(LDFLAGS))

$(OBJOBJS): $(C_OBJS) $(C_OBJS_APP_O) $(S_OBJS)

$(C_OBJS):%.o:$(ROOT_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/$(@D)
	@$(CC) $(CCFLAGS) -c -o $(OBJ_DIR)/$@ $<
	$(info CC: $(OBJ_DIR)/$@ $<)

$(C_OBJS_APP_O):%.o:$(ROOT_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/$(@D)
	@$(CC) $(CCFLAGS) -c -o $(OBJ_DIR)/$@ $<
	$(info CC: $(OBJ_DIR)/$@ $<)

$(S_OBJS): $(ROOT_DIR)/$(S_OBJS:%.o=%.s)
	@mkdir -p $(OBJ_DIR)/$(@D)
	@$(AS) $(ASFLAGS) -g -o $(OBJ_DIR)/$@ $<
	$(info AS: $(OBJ_DIR)/$@ $<)

clean :
	@rm -f *.o $(PROJECT_NAME).elf $(PROJECT_NAME).list $(PROJECT_NAME).bin $(PROJECT_NAME).uf2 $(PROJECT_NAME).map 

cleaner: clean
	@rm -r -f $(OBJ_DIR)
	@rm -r -f $(OUT_DIR)
	@rm -r -f $(LST_DIR)
