from gi.repository import Gtk # pyright: ignore[reportAttributeAccessIssue]
from power_mode import PowerModeText

def createDropdown():
    combo = Gtk.ComboBoxText()
    combo.append_text(PowerModeText.POWER_SAVER.value)
    combo.append_text(PowerModeText.BALANCED.value)
    combo.append_text(PowerModeText.PERFORMANCE.value)
    combo.set_active(1)
    combo.set_size_request(180, -1)
    return combo
