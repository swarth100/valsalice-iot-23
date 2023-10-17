import sys
import requests
import json
import click
import subprocess
import tempfile
import shutil
from decouple import config

BASE_URL = "git.spina.me"
REPO_NAME = "valsalice-iot-23"
GOLDEN_REPO = f"aspina/{REPO_NAME}"
ADMIN_USERNAME = config("ADMIN_USERNAME")
ADMIN_PASSWORD = config("ADMIN_PASSWORD")

# Set up headers with the API token
headers = {
    "Content-Type": "application/json",
}


def get_user_url(username: str, password: str) -> str:
    return f"https://{username}:{password}@{BASE_URL}"


def get_admin_url() -> str:
    return f"https://{ADMIN_USERNAME}:{ADMIN_PASSWORD}@{BASE_URL}"


def create_user(username: str, password: str):
    # Deleting the user is idempotent and should always be performed
    requests.delete(f"{get_admin_url()}/api/v1/admin/users/{username}?purge=true")

    user_creation_response = requests.post(
        f"{get_admin_url()}/api/v1/admin/users",
        headers=headers,
        json={
            "username": username,
            "password": password,
            "must_change_password": False,
            "email": f"{username}@example.com",
        },
    )

    if user_creation_response.status_code != 201:
        print(
            f"Failed to create user {username}. "
            f"Reason: [{user_creation_response.status_code}] {user_creation_response.content}"
        )
        sys.exit(1)
    else:
        print(f"User {username} created successfully!")


def create_repository(username: str, password: str):
    repo_url = f"{get_user_url(username, password)}/{username}/{REPO_NAME}"

    # Clean existing repository if present
    repo_api_url: str = (
        f"{get_user_url(username, password)}/api/v1/repos/{username}/{REPO_NAME}"
    )
    repo_exists_response = requests.get(repo_api_url)
    if repo_exists_response.status_code == 200:
        print(
            f"Repository {REPO_NAME} already existed for user {username} and will be deleted."
        )
        requests.delete(repo_api_url)

    # Create a new repository with 'master' as the default branch
    response = requests.post(
        f"{get_user_url(username, password)}/api/v1/user/repos",
        headers=headers,
        json={
            "name": REPO_NAME,
            "private": True,
            "default_branch": "master",
        },
    )

    if response.status_code == 201:
        print(f"Created repository for {username}: {REPO_NAME}")

        # Grant access to the given user
        response = requests.put(
            f"{get_user_url(username, password)}/api/v1/repos/{username}/{REPO_NAME}/collaborators/{ADMIN_USERNAME}",
            headers=headers,
        )

        if response.status_code == 204:
            print(f"Granted access rights to {username}")
        else:
            print(f"Failed to grant access rights to {username}")

        return repo_url
    else:
        print(
            f"Failed to create repository for {username}. "
            f"Reason: [{response.status_code}] {response.content}"
        )
        return None


def clone_repository(username: str, password: str):
    create_user(username, password)

    user_repo_url = create_repository(username, password)

    if user_repo_url:
        # Create a temporary directory
        with tempfile.TemporaryDirectory() as temp_dir:
            # Clone the GOLDEN_REPO to the temporary directory
            subprocess.run(
                ["git", "clone", f"{get_admin_url()}/{GOLDEN_REPO}", temp_dir],
                cwd=temp_dir,
            )

            # Clone the user's repository to the temporary directory
            subprocess.run(["git", "remote", "remove", "origin"], cwd=temp_dir)
            subprocess.run(
                ["git", "remote", "add", "origin", user_repo_url], cwd=temp_dir
            )
            subprocess.run(["git", "remote", "--verbose"], cwd=temp_dir)

            # Push the cloned GOLDEN_REPO to the user's repository
            subprocess.run(["git", "push", "origin", "master"], cwd=temp_dir)

            print(f"Cloned and pushed GOLDEN_REPO to {username}'s repository")

            # Cleanup: Remove the temporary directory
            shutil.rmtree(temp_dir)


def deploy_changes(username: str, password: str, sha1_hash: str):
    # Create a temporary directory
    with tempfile.TemporaryDirectory() as temp_dir:
        # Clone the user's repository to the temporary directory
        user_repo_url = f"{BASE_URL}/{username}/{REPO_NAME}"
        subprocess.run(["git", "clone", user_repo_url, temp_dir])

        # Fetch changes from the golden repository
        subprocess.run(
            ["git", "fetch", f"{BASE_URL}/{GOLDEN_REPO}", sha1_hash], cwd=temp_dir
        )

        # Merge changes into the user's repository
        subprocess.run(["git", "checkout", "master"], cwd=temp_dir)
        subprocess.run(["git", "merge", f"FETCH_HEAD"], cwd=temp_dir)

        # Push changes to the user's repository
        subprocess.run(["git", "push"], cwd=temp_dir)

        print(f"Deployed changes to {username}'s repository")

        # Cleanup: Remove the temporary directory
        shutil.rmtree(temp_dir)


@click.command()
@click.option(
    "--command",
    prompt="Enter command (setup/deploy)",
    help="Command (setup/deploy)",
    required=True,
)
@click.option("--username", help="Username", required=False)
# @click.option("--sha1_hash", prompt="Enter SHA1 hash", help="SHA1 hash (required for 'deploy')", default="", required=False)
@click.option(
    "--all", is_flag=True, help="Run for all usernames in the JSON file", required=False
)
def main(command: str, username: str, all: bool):
    users: dict[str, str]

    with open(".credentials.json", "r") as file:
        user_credentials: dict[str, str] = json.load(file)

    if all:
        users = user_credentials.copy()
    else:
        if username is None:
            print("Username argument must not be None! Use --all to run for all users.")
            sys.exit(1)
        if username not in user_credentials:
            print(
                f"Selected user '{username}' does not have an entry in the credentials file!"
            )
            sys.exit(1)
        users = {username: user_credentials[username]}

    for user, password in users.items():
        if command == "setup":
            clone_repository(user, password)
        elif command == "deploy":
            sha1_hash = "foo"
            deploy_changes(user, password, sha1_hash)
        else:
            click.echo(f"Invalid command for {user}. Use 'setup' or 'deploy'.")

        print("-----------------------------------------------")


if __name__ == "__main__":
    main()