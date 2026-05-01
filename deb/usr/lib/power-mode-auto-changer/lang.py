import gettext
#Force language for testing
# import os
# os.environ["LANG"] = "ru_RU.UTF-8"
# os.environ["LANGUAGE"] = "ru"

APP_NAME = "power-mode-auto-changer"
LOCALE_DIR = "/usr/share/locale"

gettext.bindtextdomain(APP_NAME, LOCALE_DIR)
gettext.textdomain(APP_NAME)
_ = gettext.gettext
