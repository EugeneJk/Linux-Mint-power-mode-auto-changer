#!/bin/bash

echo "STATUS!!";

if systemctl --user is-enabled --quiet power-mode-auto-changer.service; then
    START_UP_AUTO_SYNC_ENABLED=1
else
    START_UP_AUTO_SYNC_ENABLED=0
fi

