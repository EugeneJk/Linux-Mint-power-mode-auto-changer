from gi.repository import Gtk # pyright: ignore[reportAttributeAccessIssue]

def createCheckBox(label):
    entry = Gtk.CheckButton()

    checkbox_label = Gtk.Label(label=label)
    checkbox_label.set_margin_start(5)

    box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=0)
    box.pack_start(checkbox_label, False, False, 0)

    entry.add(box)

    return entry