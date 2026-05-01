import os
from lang import _ # pyright: ignore[reportAttributeAccessIssue]
from power_mode import PowerMode, PowerModeText, getPowerMode, getPowerModeText
from config_loader import loadConfigFile

class Config:
    def __init__(self):
        self.__onAc = PowerMode.BALANCED
        self.__onAcText = PowerModeText.BALANCED.value
        self.__onAcTextDefault = self.__onAcText
        self.__onBattery = PowerMode.POWER_SAVER
        self.__onBatteryText = PowerModeText.POWER_SAVER.value
        self.__onBatteryTextDefault = self.__onBatteryText
        self.__isPerformanceAvailable = False
        self.__configPath = '~/.config/power-mode-auto-changer/power-modes.conf'
        self.__systemConfigPath = '/etc/power-mode-auto-changer/config'
        self.__load()

    def __load(self):
        systemConfig = loadConfigFile(self.__systemConfigPath);

        if systemConfig == None :
            exit(F"Error! System config not found: {self.__systemConfigPath}")
        else:
            self.__isPerformanceAvailable = "IS_PERFORMANCE_AVAILABLE" in systemConfig and systemConfig["IS_PERFORMANCE_AVAILABLE"] == '1'

        userConfig = loadConfigFile(self.__configPath)
        if userConfig == None :
            # save defaults
            self.__saveConfig()
        else:
            self.__setLoadedConfig(userConfig)

    def __setLoadedConfig(self, values):
        isBrokenConfig = False
        # Set AC config
        if "ON_AC" in values :
            val = getPowerMode(values["ON_AC"])

            if val != None:
                self.__onAc = val
                self.__onAcTextDefault = getPowerModeText(val).value
            else:
                isBrokenConfig = True
            
        else:
            isBrokenConfig = True
        
        if "ON_AC_TEXT" in values:
            self.__onAcText = values["ON_AC_TEXT"]

        # Set Battery config
        if "ON_BATTERY" in values :
            val = getPowerMode(values["ON_BATTERY"])

            if val != None:
                self.__onBattery = val
                self.__onBatteryTextDefault = getPowerModeText(val).value
            else:
                isBrokenConfig = True
            
        else:
            isBrokenConfig = True
        
        if "ON_BATTERY_TEXT" in values:
            self.__onBatteryText = values["ON_BATTERY_TEXT"]

        if isBrokenConfig:
            self.__saveConfig()

        print(self)

    def getOnBattery(self):
        return self.__onBattery

    def setOnBattery(self, value: PowerMode):
        self.__onBattery = value
        self.__onBatteryTextDefault = getPowerModeText(value).value
        self.__saveConfig()

    def getOnAc(self):
        return self.__onAc

    def setOnAc(self, value: PowerMode):
        self.__onAc = value
        self.__onAcTextDefault = getPowerModeText(value).value
        self.__saveConfig()

    def getOnAcText(self):
        return self.__onAcText

    def setOnAcText(self, value: str):
        self.__onAcText = value
        self.__saveConfig()

    def getOnAcTextDefault(self):
        return self.__onAcTextDefault

    def getOnBatteryText(self):
        return self.__onBatteryText

    def setOnBatteryText(self, value: str):
        self.__onBatteryText = value
        self.__saveConfig()

    def getOnBatteryTextDefault(self):
        return self.__onBatteryTextDefault

    def getIsSyncOn(self):
        return True
    
    def setIsSyncOn(self, value: bool):
        print('set sync', value)

    def __saveConfig(self):
        config_path = os.path.expanduser(self.__configPath)

        # Create directory if missing
        os.makedirs(os.path.dirname(config_path), exist_ok=True)

        config = f"""ON_AC={self.__onAc.value}
ON_BATTERY={self.__onBattery.value}
ON_AC_TEXT={self.__onAcText if self.__onAcText else self.__onAcTextDefault}
ON_BATTERY_TEXT={self.__onBatteryText if self.__onBatteryText else self.__onBatteryTextDefault}
"""
        with open(config_path, "w", encoding="utf-8") as f:
            f.write(config)

    def isPerformanceModeAvailable(self):
        return self.__isPerformanceAvailable;

    def __repr__(self):
        return (
            f"Config("
            f"onAc={self.__onAc}, "
            f"onAcText={self.__onAcText}, "
            f"onAcTextDefault={self.__onAcTextDefault}, "
            f"onBattery={self.__onBattery}, "
            f"onBatteryText={self.__onBatteryText}, "
            f"onBatteryTextDefault={self.__onBatteryTextDefault}, "
            f"isPerformanceAvailable={self.__isPerformanceAvailable}"
            f")"
        )