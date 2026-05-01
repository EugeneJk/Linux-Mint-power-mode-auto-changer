from gi.repository import Gtk # pyright: ignore[reportAttributeAccessIssue]

def createLabel(name, isBold=False, centered=False):
    label = Gtk.Label()

    if isBold:
        label.set_markup(f"<span weight='bold'>{name}</span>")
    else:
        label.set_markup(f"<span>{name}</span>")

    if centered:
        label.set_xalign(0.5)
        label.set_justify(Gtk.Justification.CENTER)
    else:
        label.set_xalign(0)

    return label
