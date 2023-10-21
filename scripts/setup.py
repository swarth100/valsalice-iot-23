import sys
from common import (
    ADMIN_USERNAME,
    GOLDEN_REPO,
    HEADERS,
    REPO_NAME,
    get_admin_url,
    get_user_url,
)
import requests
import json
import click
import subprocess
import tempfile
import shutil


def create_user(username: str, password: str):
    # Deleting the user is idempotent and should always be performed
    requests.delete(f"{get_admin_url()}/api/v1/admin/users/{username}?purge=true")

    user_creation_response = requests.post(
        f"{get_admin_url()}/api/v1/admin/users",
        headers=HEADERS,
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
        headers=HEADERS,
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
            headers=HEADERS,
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


@click.command()
@click.option("--username", help="Username", required=False)
@click.option(
    "--all", is_flag=True, help="Run for all usernames in the JSON file", required=False
)
def main(username: str, all: bool):
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
        clone_repository(user, password)
        print("-----------------------------------------------")


if __name__ == "__main__":
    main()
