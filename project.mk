PROJECT_MODULES	= src/lld_control.c \
                  src/lld_encoder.c \
                  src/odometry.c    \
                  src/mpu6050.c

PROJECT_TESTS	= tests/test_lld_control.c \
                  tests/test_lld_encoder.c \
                  tests/test_odometry.c    \
                  tests/test_mpu6050.c
# C source files
PROJECT_CSRC 	= src/main.c src/common.c $(PROJECT_MODULES) $(PROJECT_TESTS)
# C++ source files
PROJECT_CPPSRC 	= 
# Directories to search headers in
PROJECT_INCDIR	= include
# Additional libraries
PROJECT_LIBS	= 
# Compiler options
PROJECT_OPT     =

# Additional .mk files are included here
