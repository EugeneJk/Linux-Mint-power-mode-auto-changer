import subprocess
import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk, Gdk # pyright: ignore[reportAttributeAccessIssue]
from lang import _ # pyright: ignore[reportAttributeAccessIssue]
from config import Config
from main_window_components.label import createLabel
from main_window_components.dropdown import Dropdown
from main_window_components.textbox import Textbox
from main_window_components.grid import createGrid, setGridStyles, wrapCell
from main_window_components.checkbox import Checkbox

class MainWindow(Gtk.Window):
    def __init__(self, config: Config):
        super().__init__(title=_("Power Mode Auto Changer"))
        self.set_default_icon_name("preferences-system-power")
        
        self._setWindowParams()
        setGridStyles()

        main_box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=15)
        self.add(main_box)

        grid = createGrid()
        main_box.pack_start(grid, False, False, 0)

        # Header row
        empty_header = createLabel("")
        ac_header = createLabel(_("On A/C power"), True, centered=True)
        battery_header = createLabel(_("On battery power"), True, centered=True)

        grid.attach(wrapCell(empty_header), 0, 0, 1, 1)
        grid.attach(wrapCell(ac_header), 1, 0, 1, 1)
        grid.attach(wrapCell(battery_header), 2, 0, 1, 1)

        # Profile row
        profile_label = createLabel(_("Profile mode"))
        ac_profile = Dropdown(config.getOnAc, config.setOnAc, config.isPerformanceModeAvailable())
        battery_profile = Dropdown(config.getOnBattery, config.setOnBattery, config.isPerformanceModeAvailable())

        grid.attach(wrapCell(profile_label), 0, 1, 1, 1)
        grid.attach(wrapCell(ac_profile.element), 1, 1, 1, 1)
        grid.attach(wrapCell(battery_profile.element, last_col=True), 2, 1, 1, 1)

        # Notification row
        notification_label = createLabel(_("Notification text"))
        ac_notification = Textbox(config.getOnAcText, config.setOnAcText, config.getOnAcTextDefault)
        battery_notification = Textbox(config.getOnBatteryText, config.setOnBatteryText, config.getOnBatteryTextDefault)

        ac_profile.textbox = ac_notification;
        battery_profile.textbox = battery_notification;

        grid.attach(wrapCell(notification_label, last_row=True), 0, 2, 1, 1)
        grid.attach(wrapCell(ac_notification.element, last_row=True), 1, 2, 1, 1)
        grid.attach(
            wrapCell(battery_notification.element, last_row=True, last_col=True),
            2, 2, 1, 1
        )

        # Column sizing
        grid.get_child_at(0, 0).set_hexpand(True)
        grid.get_child_at(1, 0).set_size_request(200, -1)
        grid.get_child_at(2, 0).set_size_request(200, -1)

        # Sync checkbox
        sync_checkbox = Checkbox(
            _("Sync on start up"),
            config.getIsSyncOn,
            config.setIsSyncOn
        ).element

        sync_button = Gtk.Button(label=_("Sync now"))
        sync_button.connect("clicked", self._on_sync_clicked)

        bottom_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL)
        bottom_box.pack_start(sync_checkbox, False, False, 0)
        spacer = Gtk.Box()
        spacer.set_hexpand(True)
        bottom_box.pack_start(spacer, True, True, 0)
        bottom_box.pack_end(sync_button, False, False, 0)
        main_box.pack_start(bottom_box, False, False, 0)

    def _on_sync_clicked(self, button):
        subprocess.run(
            ["power-mode-auto-changer-service"],
            capture_output=True,
            text=True
        )

    def _setWindowParams(self):
        self.set_border_width(15)
        self.set_default_size(800, 200)
        self.set_size_request(700, 200)
        self.set_position(Gtk.WindowPosition.CENTER)
