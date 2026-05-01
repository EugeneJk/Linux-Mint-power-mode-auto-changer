from typing import Callable
from gi.repository import Gtk # pyright: ignore[reportAttributeAccessIssue]

def createCheckBox(label):
    entry = Gtk.CheckButton()

    checkbox_label = Gtk.Label(label=label)
    checkbox_label.set_margin_start(5)

    box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=0)
    box.pack_start(checkbox_label, False, False, 0)

    entry.add(box)

    return entry

class Checkbox:
    def __init__(
        self,
        label,
        getVal: Callable[[], bool],
        setVal: Callable[[bool], None],
    ):
        self.getVal = getVal
        self.setVal = setVal

        self.element = createCheckBox(label)

        # Set initial value
        self.element.set_active(self.getVal())

        # Change event
        self.element.connect("toggled", self._on_toggled)
        
    def _on_toggled(self, checkbox):
        new_value = checkbox.get_active()
        self.setVal(new_value)