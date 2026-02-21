#!/bin/bash

echo $NAME
PACKAGE="power-mode-auto-changer"
PACKAGE_VERSION=$(dpkg-query -W -f='${Version}' "$PACKAGE" 2>/dev/null)
echo "$VERSION_TITLE: $PACKAGE_VERSION"
