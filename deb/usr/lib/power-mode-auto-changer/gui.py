#!/usr/bin/env python3

import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk # pyright: ignore[reportAttributeAccessIssue]
from main_window import MainWindow
from config import Config


def main():
    win = MainWindow(Config())
    win.connect("destroy", Gtk.main_quit)
    win.show_all()
    Gtk.main()

if __name__ == "__main__":
    main()