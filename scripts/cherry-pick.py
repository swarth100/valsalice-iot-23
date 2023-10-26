import os
import sys
from common import (
    ADMIN_USERNAME,
    GOLDEN_REPO,
    REPO_NAME,
    get_admin_url,
    get_user_url,
)
import json
import click
import subprocess
import tempfile
import shutil
from contextlib import contextmanager


@contextmanager
def golden_repo_tempdir():
    """
    Create a temporary directory for golden repository as a context manager.
    Cleans up on exit.
    Creating the golden directory once significantly reduces cloning costs (time).
    """
    with tempfile.TemporaryDirectory() as golden_temp_dir:
        # Clone the GOLDEN_REPO to the temporary directory
        subprocess.run(
            [
                "git",
                "clone",
                f"{get_admin_url()}/{GOLDEN_REPO}",
                golden_temp_dir,
            ],
            cwd=golden_temp_dir,
        )

        try:
            yield golden_temp_dir
        finally:
            # Cleanup: Remove the temporary directories
            shutil.rmtree(golden_temp_dir)


def cherry_pick(
    *,
    username: str,
    password: str,
    commit_sha1: str,
    commit_message: str,
    golden_temp_dir: str,
):
    user_repo_url = f"{get_user_url(username, password)}/{username}/{REPO_NAME}"

    if user_repo_url:
        # Create a temporary directory for user's repository
        with tempfile.TemporaryDirectory() as user_temp_dir:
            # Clone the user's repository to the temporary directory
            subprocess.run(
                ["git", "clone", user_repo_url, user_temp_dir], cwd=user_temp_dir
            )

            # Switch to the specified commit in the GOLDEN_REPO
            subprocess.run(["git", "checkout", commit_sha1], cwd=golden_temp_dir)

            # Get the list of changed files in the commit
            changed_files = (
                subprocess.check_output(
                    ["git", "diff", "--name-only", "--diff-filter=AM", "HEAD~1..HEAD"],
                    cwd=golden_temp_dir,
                )
                .decode("utf-8")
                .splitlines()
            )

            # Copy the changed files to the user's repository
            for file in changed_files:
                # Get the directory path of the file and create it in the user's repository if it doesn't exist
                file_dir = os.path.dirname(file)
                user_file_dir = os.path.join(user_temp_dir, file_dir)
                os.makedirs(user_file_dir, exist_ok=True)

                # Copy the file
                shutil.copy2(
                    f"{golden_temp_dir}/{file}", os.path.join(user_temp_dir, file)
                )

            # Get the list of deleted files
            deleted_files: list[str] = (
                subprocess.check_output(
                    ["git", "diff", "--name-only", "--diff-filter=D", "HEAD~1..HEAD"],
                    cwd=golden_temp_dir,
                )
                .decode("utf-8")
                .splitlines()
            )

            # Apply deletions.
            # Deletions are idempotent, thus if the file to be deleted is not there it's okay, we can skip.
            for filename in deleted_files:
                try:
                    subprocess.run(["rm", filename], cwd=user_temp_dir, check=True)
                    print(f"Deleted file {filename}.")
                except subprocess.CalledProcessError:
                    print(f"Cannot find file {filename} to be deleted.")

            # Commit and push the changes to the user's repository
            subprocess.run(["git", "add", "."], cwd=user_temp_dir)
            subprocess.run(
                [
                    "git",
                    "commit",
                    "--author",
                    f"{ADMIN_USERNAME} <{ADMIN_USERNAME}@example.com>",
                    "--message",
                    commit_message,
                ],
                cwd=user_temp_dir,
            )
            subprocess.run(["git", "push", "origin", "master"], cwd=user_temp_dir)

            print(
                f"Copied changes from commit {commit_sha1} in GOLDEN_REPO to {username}'s repository"
            )

            # Cleanup: Remove the temporary directories
            shutil.rmtree(user_temp_dir)


@click.command()
@click.option("--username", help="Username", required=False)
@click.option(
    "--all", is_flag=True, help="Run for all usernames in the JSON file", required=False
)
@click.option("--commit-sha1", help="SHA1 of the commit to copy", required=True)
@click.option(
    "--commit-message",
    help="Message to use when copying the commits over",
    required=True,
)
def main(username: str, all: bool, commit_sha1: str, commit_message: str):
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

    with golden_repo_tempdir() as golden_temp_dir:
        for user, password in users.items():
            cherry_pick(
                username=user,
                password=password,
                commit_sha1=commit_sha1,
                commit_message=commit_message,
                golden_temp_dir=golden_temp_dir,
            )
            print("-----------------------------------------------")
    print(f"-------------- ✅ Complete [{len(users)} operations]--------------")


if __name__ == "__main__":
    main()
