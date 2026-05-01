from typing import Callable
from gi.repository import Gtk # pyright: ignore[reportAttributeAccessIssue]
from power_mode import PowerMode, PowerModeText, getPowerMode
from main_window_components.textbox import Textbox

def createDropdown():
    combo = Gtk.ComboBoxText()

    combo.append(PowerMode.POWER_SAVER.value, PowerModeText.POWER_SAVER.value)
    combo.append(PowerMode.BALANCED.value, PowerModeText.BALANCED.value)
    combo.append(PowerMode.PERFORMANCE.value, PowerModeText.PERFORMANCE.value)

    combo.set_size_request(180, -1)

    return combo

class Dropdown:
    textbox: Textbox | None = None
    def __init__(
        self,
        getVal: Callable[[], PowerMode],
        setVal: Callable[[PowerMode], None]
    ):
        self.getVal = getVal
        self.setVal = setVal
        self.element = createDropdown()
        self.element.set_active_id(getVal())
        self.element.connect("changed", self._on_changed)
        
    def _on_changed(self, combo):
        selected_value = getPowerMode(combo.get_active_id())

        if selected_value is not None:
            self.setVal(selected_value)
        
        if self.textbox != None:
            self.textbox.updatePlaceholder();