from enum import Enum
from lang import _ # pyright: ignore[reportAttributeAccessIssue]

class PowerMode(str, Enum):
    BALANCED = "balanced"
    POWER_SAVER = "power-saver"
    PERFORMANCE = "performance"

class PowerModeText(str, Enum):
    BALANCED = _("Balanced")
    POWER_SAVER = _("Power saver")
    PERFORMANCE = _("Performance")

def getPowerMode(val: str):
    if val == PowerMode.BALANCED.value :
        return PowerMode.BALANCED
    if val == PowerMode.POWER_SAVER.value :
        return PowerMode.POWER_SAVER
    if val == PowerMode.PERFORMANCE.value :
        return PowerMode.PERFORMANCE

    return None

def getPowerModeText(val: PowerMode):
    if val == PowerMode.BALANCED:
        return PowerModeText.BALANCED
    if val == PowerMode.POWER_SAVER :
        return PowerModeText.POWER_SAVER
    if val == PowerMode.PERFORMANCE :
        return PowerModeText.PERFORMANCE

    return None