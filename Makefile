KVERSION ?= `uname -r`
KERNEL_SRC ?= /lib/modules/${KVERSION}/build
MODULES_DIR ?= /lib/modules/${KVERSION}/kernel/drivers/hid
UDEVRULES_DIR ?= /etc/udev/rules.d

default:
	@echo -e "\n::\033[32m Compiling Fanatec kernel module\033[0m"
	@echo "========================================"
	$(MAKE) -C $(KERNEL_SRC) M=$$PWD

clean:
	@echo -e "\n::\033[32m Cleaning Fanatec kernel module\033[0m"
	@echo "========================================"
	$(MAKE) -C $(KERNEL_SRC) M=$$PWD clean

install:
	@echo -e "\n::\033[34m Installing Fanatec kernel module/udev rule\033[0m"
	@echo "====================================================="
	@install -p -v -m 0755 -D hid-fanatec.ko ${INSTALL_DIR}${MODULES_DIR}
	@install -p -v -m 0755 -D fanatec.rules ${INSTALL_DIR}${UDEVRULES_DIR}/99-fanatec.rules
	@if [ `id -u` -eq 0 ]; then depmod; fi

uninstall:
	@echo -e "\n::\033[34m Uninstalling Fanatec kernel module/udev rule\033[0m"
	@echo "====================================================="
	@rm -fv ${INSTALL_DIR}${MODULES_DIR}/hid-fanatec.ko
	@rm -fv ${INSTALL_DIR}${UDEVRULES_DIR}/99-fanatec.rules
	@if [ `id -u` -eq 0 ]; then depmod; fi

