import json
import shutil
from decouple import config


BASE_URL = "git.spina.me"
REPO_NAME = "valsalice-iot-23"
ADMIN_USERNAME = config("ADMIN_USERNAME")
ADMIN_PASSWORD = config("ADMIN_PASSWORD")
GOLDEN_REPO = f"{ADMIN_USERNAME}/{REPO_NAME}"
# GOLDEN_REPO = f"{ADMIN_USERNAME}/valsalice-contiki-lab"
# Set up headers with the API token
HEADERS = {
    "Content-Type": "application/json",
}


def get_user_url(username: str, password: str) -> str:
    return f"https://{username}:{password}@{BASE_URL}"


def get_admin_url() -> str:
    return f"https://{ADMIN_USERNAME}:{ADMIN_PASSWORD}@{BASE_URL}"
