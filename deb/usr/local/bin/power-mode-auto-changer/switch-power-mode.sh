#!/bin/bash

PATH=/usr/sbin:/usr/bin:/sbin:/bin

LOG_DIR="/var/tmp/power-mode-auto-changer"
LOG_FILE="$LOG_DIR/test.log"

mkdir -p "$LOG_DIR"

echo "$(date '+%Y-%m-%d %H:%M:%S') - service triggered" >> "$LOG_FILE"

exit 0