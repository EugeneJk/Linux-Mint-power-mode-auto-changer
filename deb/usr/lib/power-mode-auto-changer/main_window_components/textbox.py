from typing import Callable
from gi.repository import Gtk # pyright: ignore[reportAttributeAccessIssue]

def createTextBox():
    entry = Gtk.Entry()
    entry.set_size_request(180, -1)
    return entry

class Textbox:
    def __init__(
        self,
        getVal: Callable[[], str],
        setVal: Callable[[str], None],
        getDefaultVal: Callable[[], str],
    ):
        self.getVal = getVal
        self.setVal = setVal
        self.getDefaultVal = getDefaultVal
        
        self.element = createTextBox()
        self.updatePlaceholder()
        self.element.set_text(getVal())
        self.element.connect("focus-out-event", self.__on_focus_out)

    def updatePlaceholder(self):
        self.element.set_placeholder_text(self.getDefaultVal())
        
    def __on_focus_out(self, widget, event):
        value = widget.get_text()
        self.setVal(value)