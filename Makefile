VERSION=2.0.3
PACKAGE=power-mode-auto-changer
BUILD_DIR=build

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -O2 -Isrc
BUILD_DIR = build
SRC_DIR = src
DEB_USR_LOCAL_BIN_DIR = deb/usr/local/bin

SERVICE_TARGET = power-mode-auto-changer-service
CLI_TARGET = power-mode-auto-changer-cli
DEB_TARGET = build-deb
COPY_LANG_TARGET = copy-translaction

COMMON_SOURCES := $(shell find $(SRC_DIR) -mindepth 2 -name "*.cpp")
SERVICE_SOURCE := $(SRC_DIR)/service.cpp
CLI_SOURCE := $(SRC_DIR)/cli.cpp
TEST_SOURCE := $(SRC_DIR)/test.cpp

all: $(SERVICE_TARGET) $(CLI_TARGET) $(COPY_LANG_TARGET) $(DEB_TARGET)

$(SERVICE_TARGET):
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SERVICE_SOURCE) $(COMMON_SOURCES) -o $(BUILD_DIR)/$(SERVICE_TARGET)
	mkdir -p $(DEB_USR_LOCAL_BIN_DIR)
	cp $(BUILD_DIR)/$(SERVICE_TARGET) $(DEB_USR_LOCAL_BIN_DIR)/$(SERVICE_TARGET)

$(CLI_TARGET):
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CLI_SOURCE) $(COMMON_SOURCES) -o $(BUILD_DIR)/$(CLI_TARGET)
	cp $(BUILD_DIR)/$(CLI_TARGET) $(DEB_USR_LOCAL_BIN_DIR)/$(CLI_TARGET)

$(DEB_TARGET):
	@SIZE=$$(du -sk deb/ | cut -f1); \
	sed -i "s/^Installed-Size:.*/Installed-Size: $$SIZE/" deb/DEBIAN/control; \
	sed -i "s/^Version:.*/Version: $(VERSION)/" deb/DEBIAN/control; \
	dpkg-deb --build --root-owner-group deb $(BUILD_DIR)/$(PACKAGE)_$(VERSION).deb
	
$(COPY_LANG_TARGET):
	cp ./lang/ru.mo  ./deb/usr/share/locale/ru/LC_MESSAGES/${PACKAGE}.mo

install:
	sudo dpkg -i $(BUILD_DIR)/$(PACKAGE)_$(VERSION).deb

uninstall:
# 	sudo apt-get remove -y $(PACKAGE)
	sudo apt-get purge -y $(PACKAGE)


clean:
	rm -rf $(BUILD_DIR)
