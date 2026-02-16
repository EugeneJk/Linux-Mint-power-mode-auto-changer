#!/bin/bash
 echo
echo "$ERROR_TEXT:"
echo "----------------------------"
case "$ERROR_TYPE" in
    MULTIPLE_ACTIONS)
        echo "$ERROR_TEXT_MULTIPLE_ACTION:"
        echo "  --help | --version | --configure | --status"
        ;;

    UNKNOWN_ARG=*)
        INVALID_ARG="${ERROR_TYPE#*=}"
        echo "$ERROR_TEXT_UNKNOWN_ARG:"
        echo "  $INVALID_ARG"
        ;;

    *)
        echo "$ERROR_TEXT_UNEXPECTED_ERROR:"
        echo "  $ERROR_TYPE"
        ;;
esac
echo