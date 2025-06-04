# === Configurable paths ===
ACL_ROOT := ./ComputeLibrary
ACL_BUILD := $(ACL_ROOT)/build
ACL_INCLUDE := $(ACL_ROOT)/include

# Compiler and flags
CXX := aarch64-linux-gnu-g++
CXXFLAGS := -std=c++17 -O2 -I$(ACL_INCLUDE) -I$(ACL_ROOT)

# Static Linking
#LDFLAGS := $(ACL_BUILD)/libarm_compute-static.a
LDFLAGS := -static $(ACL_BUILD)/libarm_compute-static.a -lstdc++ -lm -lpthread

# Dynamic Linking
# LDFLAGS := -L$(ACL_BUILD) -larm_compute
#-larm_compute_core

# Target binary
TARGET := fully_connected_acl

# Source file
SRC := MWFCLayer_ACL.cpp

.PHONY: all run clean

# === Build rule ===
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $@

# === Run with QEMU ===
run: $(TARGET)
	qemu-aarch64 ./$<

# === Clean ===
clean:
	rm -f $(TARGET)
