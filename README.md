<p align="center">
  <a href="#english">🇬🇧 English</a>
  &nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;
  <a href="#русский">🇷🇺 Русский</a>
</p>

## English
# Linux Mint power mode auto changer

Adds the ability to **automatically change the power mode** in Linux Mint on laptops depending on the power source state (AC or battery).

The tool monitors power connection events and:
- automatically switches to a **power-saving (or user-selected) mode** when the laptop is **disconnected from AC power and running on battery**;
- automatically switches to a **performance (or user-selected) mode** when the laptop is **connected to AC power**.

This helps optimize **battery life**, **performance**, and **power consumption** without manual interaction.

## Installation / Update Current Settings
Run the installation script in the terminal:

```
./install.sh
```
*Note: Do **not** run the script with `sudo`. The script will use `sudo` where necessary.*

## Uninstallation
Run the uninstallation script in the terminal:

```
./uninstall.sh
```
## Prerequisites
- TLP is **not supported**.
- The **standard Linux Mint power manager** should be installed on your system.
  
<br>
<p align="center">◆ ◆ ◆</p>

## Русский
# Автопереключение режимов питания Linux Mint

Добавляет возможность **автоматического переключения режимов питания** в Linux Mint на ноутбуках в зависимости от источника питания (сеть или батарея).

Инструмент отслеживает события подключения питания и:
- автоматически переключает систему в режим **энергосбережения (или выбранный пользователем)** при **отключении от сети и работе от батареи**;
- автоматически переключает систему в режим **производительности (или выбранный пользователем)** при **подключении к сети**.

Это позволяет оптимизировать **время работы от батареи**, **производительность** и **энергопотребление** без ручного вмешательства.

## Установка / Обновление настроек
Запустите скрипт установки в терминале:

```
./install.sh
```
*Примечание: **Не** запускайте скрипт в режиме `sudo`. Скрипт выполнит нужние команды в режиме `sudo` где это необходимо.*

## Удаление
Запустите скрипт удаления в терминале:

```
./uninstall.sh
```
## Необходимые условия
- TLP **не поддерживается**.
- На системе должен быть установлен **стандартный менеджер питания Linux Mint**.