#!/bin/bash

cat << EOF
$NAME

$HELP_USAGE:
  power-mode-auto-changer [ACTION] [OPTION]

$HELP_ACTIONS:
  --status        $HELP_STATUS_DESC
  --configure     $HELP_CONFIGURE_DESC
  --help          $HELP_HELP_DESC
  --version       $HELP_VERSION_DESC

$HELP_OPTIONS:
  --lang=ru       $HELP_LANG_RU_DESC
  --lang=en       $HELP_LANG_EN_DESC

$HELP_EXAMPLES:
  power-mode-auto-changer
  power-mode-auto-changer --status
  power-mode-auto-changer --configure
  power-mode-auto-changer --help
  power-mode-auto-changer --version
  power-mode-auto-changer --status --lang=ru

$HELP_NOTES:
  • $HELP_NOTE_ONE_ACTION
  • $HELP_NOTE_DEFAULT_STATUS
  • $HELP_NOTE_INTERACTIVE
EOF