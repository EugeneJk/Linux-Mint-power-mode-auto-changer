# Linux Mint power mode auto changer

Full documentation:

🇬🇧 English: https://github.com/EugeneJk/Linux-Mint-power-mode-auto-changer/wiki

🇷🇺 Русский: https://github.com/EugeneJk/Linux-Mint-power-mode-auto-changer/wiki/%D0%93%D0%BB%D0%B0%D0%B2%D0%BD%D0%B0%D1%8F

Adds the ability to **automatically change the power mode** in Linux Mint on laptops depending on the power source state (AC or battery).

The tool monitors power connection events and:

* automatically switches to a **power-saving (or user-selected) mode** when the laptop is **disconnected from AC power and running on battery**;
* automatically switches to a **performance (or user-selected) mode** when the laptop is **connected to AC power**;
* shows a **desktop notification** when the power mode is changed (except during system startup);
* does **not** switch the power mode if the current profile already matches the required one (for example, after a manual change).

This helps **optimize battery life, performance**, and **power consumption** without manual interaction.

## Installation
### Recommended — from release package
1. Download the latest .deb package from the Releases section.
2. Install it either via GUI (double-click the downloaded package) or from the command line:
```shellscript
sudo apt install ./power-mode-auto-changer_<version>.deb
```

### Build from source

Build the .deb package:
```shellscript
make
```
Install it:
```shellscript
make install
```
Note: Do **not** run `make` with `sudo`. The script will request `sudo` only where required.

## Configuration

After installation, use new menu entry:
* 🇬🇧 English: Power Mode Auto Changer
* 🇷🇺 Русский: Автопереключение режима питания

This will launch the interactive text-mode configurator,

or run the configuration script directly:

```shellscript
power-mode-auto-changer --configure
```

You can:
- select the power profile for **AC mode**;
- select the power profile for **battery mode**;
- enable or disable **startup synchronization**;
- view current **status and configuration**.

Configuration changes take effect immediately.

## Uninstallation

Remove the package:
```shellscript
sudo apt remove power-mode-auto-changer
```

## Prerequisites
- **TLP is not supported.**
- The **standard Linux Mint power manager** must be installed and active.