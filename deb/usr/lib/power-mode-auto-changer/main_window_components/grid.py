from gi.repository import Gtk, Gdk # pyright: ignore[reportAttributeAccessIssue]

def setGridStyles():
    css = b"""
    .custom-grid {
        background-color: @theme_base_color;
        border: 1px solid @borders;
    }

    .frame-cell {
        padding: 10px;
        border-bottom: 1px solid shade(@borders, 1.15);;
    }

    .last-row {
        border-bottom: none;
    }
    """

    css_provider = Gtk.CssProvider()
    css_provider.load_from_data(css)

    Gtk.StyleContext.add_provider_for_screen(
        Gdk.Screen.get_default(),
        css_provider,
        Gtk.STYLE_PROVIDER_PRIORITY_APPLICATION
    )


def createGrid():
    grid = Gtk.Grid()
    grid.get_style_context().add_class("custom-grid")
    grid.set_row_spacing(0)
    grid.set_column_spacing(0)
    grid.set_vexpand(False)
    grid.set_hexpand(True)

    return grid

def wrapCell(widget, last_row=False, last_col=False):
    frame = Gtk.Frame()
    frame.set_shadow_type(Gtk.ShadowType.NONE)

    style = frame.get_style_context()
    style.add_class("frame-cell")

    if last_row:
        style.add_class("last-row")

    if last_col:
        style.add_class("last-col")

    frame.add(widget)
    return frame