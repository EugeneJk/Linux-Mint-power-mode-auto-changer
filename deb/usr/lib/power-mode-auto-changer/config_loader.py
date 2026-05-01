import configparser
import io
import os

def loadConfigFile(file: str):
    config_path = os.path.expanduser(file)

    # If config does not exist — create default
    if not os.path.exists(config_path):
        return None

    config = configparser.RawConfigParser()

    with open(config_path, "r", encoding="utf-8") as f:
        file_content = f.read()

    # Add fake section header
    file_content = "[DEFAULT]\n" + file_content

    config.read_file(io.StringIO(file_content))
    return config["DEFAULT"]
