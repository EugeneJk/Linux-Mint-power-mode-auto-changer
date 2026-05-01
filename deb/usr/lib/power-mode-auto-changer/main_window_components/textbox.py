from gi.repository import Gtk # pyright: ignore[reportAttributeAccessIssue]

def createTextBox():
    entry = Gtk.Entry()
    entry.set_placeholder_text("Enter configuration name")
    entry.set_size_request(180, -1)
    return entry
