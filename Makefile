VERSION=2.0.0
PACKAGE=power-mode-auto-changer
BUILD_DIR=build

.PHONY: build install uninstall clean

build:
	mkdir -p $(BUILD_DIR)
	dpkg-deb --build --root-owner-group deb $(BUILD_DIR)/$(PACKAGE)_$(VERSION).deb

install:
	sudo dpkg -i $(BUILD_DIR)/$(PACKAGE)_$(VERSION).deb

uninstall:
	sudo apt-get remove -y $(PACKAGE)

clean:
	rm -rf $(BUILD_DIR)
