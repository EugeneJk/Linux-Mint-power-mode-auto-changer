import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk, Gdk # pyright: ignore[reportAttributeAccessIssue]
from lang import _ # pyright: ignore[reportAttributeAccessIssue]


class MainWindow(Gtk.Window):
    def __init__(self):
        super().__init__(title=_("Power Mode Auto Changer"))

        self._setWindowParams()
        self._setStyles()

        main_box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=15)
        self.add(main_box)

        grid = self._createGrid()
        main_box.pack_start(grid, False, False, 0)

        # Header row
        empty_header = self._createLabel("")
        ac_header = self._createLabel(_("On A/C power"), True, centered=True)
        battery_header = self._createLabel(_("On battery power"), True, centered=True)

        grid.attach(self._wrap_cell(empty_header), 0, 0, 1, 1)
        grid.attach(self._wrap_cell(ac_header), 1, 0, 1, 1)
        grid.attach(self._wrap_cell(battery_header), 2, 0, 1, 1)

        # Profile row
        profile_label = self._createLabel(_("Profile mode"))
        ac_profile = self._createDropdown()
        battery_profile = self._createDropdown()

        grid.attach(self._wrap_cell(profile_label), 0, 1, 1, 1)
        grid.attach(self._wrap_cell(ac_profile), 1, 1, 1, 1)
        grid.attach(self._wrap_cell(battery_profile, last_col=True), 2, 1, 1, 1)

        # Notification row
        notification_label = self._createLabel(_("Notification text"))
        ac_notification = self._createTextBox()
        battery_notification = self._createTextBox()

        grid.attach(self._wrap_cell(notification_label, last_row=True), 0, 2, 1, 1)
        grid.attach(self._wrap_cell(ac_notification, last_row=True), 1, 2, 1, 1)
        grid.attach(
            self._wrap_cell(battery_notification, last_row=True, last_col=True),
            2, 2, 1, 1
        )

        # Column sizing
        grid.get_child_at(0, 0).set_hexpand(True)
        grid.get_child_at(1, 0).set_size_request(200, -1)
        grid.get_child_at(2, 0).set_size_request(200, -1)

        # Sync checkbox
        sync_checkbox = Gtk.CheckButton()

        checkbox_label = Gtk.Label(label=_("Sync on start up"))
        checkbox_label.set_margin_start(5)

        box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=0)
        box.pack_start(checkbox_label, False, False, 0)

        sync_checkbox.add(box)
        main_box.pack_start(sync_checkbox, False, False, 0)

    def _setWindowParams(self):
        self.set_border_width(15)
        self.set_default_size(800, 200)
        self.set_size_request(700, 200)
        self.set_position(Gtk.WindowPosition.CENTER)

    def _setStyles(self):
        css = b"""
        .custom-grid {
            background-color: white;
            border: 1px solid #bfbfbf;
        }

        .frame-cell {
            padding: 10px;
            border-bottom: 1px solid #d9d9d9;
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

    def _createDropdown(self):
        combo = Gtk.ComboBoxText()
        combo.append_text(_("Power saver"))
        combo.append_text(_("Balanced"))
        combo.append_text(_("Performance"))
        combo.set_active(1)
        combo.set_size_request(180, -1)
        return combo

    def _createLabel(self, name, isBold=False, centered=False):
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

    def _createTextBox(self):
        entry = Gtk.Entry()
        entry.set_placeholder_text("Enter configuration name")
        entry.set_size_request(180, -1)
        return entry

    def _createGrid(self):
        grid = Gtk.Grid()
        grid.get_style_context().add_class("custom-grid")
        grid.set_row_spacing(0)
        grid.set_column_spacing(0)
        grid.set_vexpand(False)
        grid.set_hexpand(True)

        return grid

    def _wrap_cell(self, widget, last_row=False, last_col=False):
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