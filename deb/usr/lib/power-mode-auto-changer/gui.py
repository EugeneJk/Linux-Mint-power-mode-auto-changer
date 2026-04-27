#!/usr/bin/env python3

import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk


class ConfiguratorWindow(Gtk.Window):
    def __init__(self):
        super().__init__(title="Power Mode Auto Changer")
        self.set_border_width(15)
        self.set_default_size(400, 200)

        main_box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=10)
        self.add(main_box)

        # Label
        label = Gtk.Label(label="Configuration Name:")
        label.set_xalign(0)
        main_box.pack_start(label, False, False, 0)

        # Text Entry
        self.entry = Gtk.Entry()
        self.entry.set_placeholder_text("Enter configuration name")
        main_box.pack_start(self.entry, False, False, 0)

        # Dropdown Label
        dropdown_label = Gtk.Label(label="Select Power Profile:")
        dropdown_label.set_xalign(0)
        main_box.pack_start(dropdown_label, False, False, 0)

        # Dropdown
        self.combo = Gtk.ComboBoxText()
        self.combo.append_text("Power Saver")
        self.combo.append_text("Balanced")
        self.combo.append_text("Performance")
        self.combo.set_active(1)
        main_box.pack_start(self.combo, False, False, 0)


def main():
    win = ConfiguratorWindow()
    win.connect("destroy", Gtk.main_quit)
    win.show_all()
    Gtk.main()


if __name__ == "__main__":
    main()