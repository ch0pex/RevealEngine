import os
import subprocess
import sys
import platform
import shutil  # Used for finding executables robustly

VENV_DIR = ".venv"
BUILD_TYPES = ["Release", "Debug", "RelWithDebInfo"]
TARGET_PROFILES = ["windows_profile", "linux_profile"]


def check_command(command):
    """Checks if a command is available in the system's PATH or within the venv."""
    # shutil.which is the recommended way to find executables in Python 3.3+
    return shutil.which(command) is not None


def get_venv_executable_path(executable_name):
    """Gets the expected path for an executable within the virtual environment."""
    if platform.system() == "Windows":
        # On Windows, executables are in Scripts and often have .exe
        return os.path.join(VENV_DIR, "Scripts", f"{executable_name}.exe")
    else:
        # On Linux/macOS, executables are in bin
        return os.path.join(VENV_DIR, "bin", executable_name)


def setup_venv():
    """Creates the virtual environment if it doesn't exist."""
    if not os.path.isdir(VENV_DIR):
        print(f"Creating virtual environment in {VENV_DIR}...")
        try:
            # Use sys.executable to ensure we use the correct python interpreter for venv creation
            subprocess.run([sys.executable, "-m", "venv", VENV_DIR], check=True)
            print("Virtual environment created.")
        except subprocess.CalledProcessError as e:
            print(f"Error creating virtual environment: {e}")
            sys.exit(1)  # Exit if venv creation fails
    else:
        print(f"Virtual environment {VENV_DIR} already exists.")


def install_conan_in_venv():
    """Installs Conan within the virtual environment."""
    pip_venv_path = get_venv_executable_path("pip")

    # Check if the pip executable exists in the venv
    if not os.path.exists(pip_venv_path):
        print(f"Error: pip executable not found in virtual environment at {pip_venv_path}.")
        print("Please ensure the virtual environment was created correctly.")
        sys.exit(1)

    print("Installing Conan in the virtual environment...")
    try:
        # Run pip from the virtual environment's path
        subprocess.run([pip_venv_path, "install", "conan"], check=True)
        print("Conan installed in the virtual environment.")
    except subprocess.CalledProcessError as e:
        print(f"Error installing Conan in the virtual environment: {e}")
        sys.exit(1)  # Exit if conan installation fails


if __name__ == "__main__":
    conan_executable = None

    # 1. Check if Conan is available globally first (matches bash script logic)
    print("Checking for Conan...")
    if check_command("conan"):
        print("Using existing global Conan installation.")
        conan_executable = "conan"  # We can just use "conan" and rely on the system's PATH
    else:
        print("Conan not found globally.")
        # 2. If not found globally, set up Venv and install Conan in it
        setup_venv()
        install_conan_in_venv()
        # 3. After installing, the Conan executable should be in the venv
        conan_executable = get_venv_executable_path("conan")
        # Verify the executable exists after installation attempt
        if not os.path.exists(conan_executable):
            print(
                f"Error: Conan executable not found in virtual environment at {conan_executable} after installation attempt.")
            sys.exit(1)
        print(f"Using Conan from virtual environment: {conan_executable}")

    print("\nStarting Conan installations...")

    print(f"Installing for OS: {os.name}")
    profile = "windows_profile" if os.name != "posix" else "linux_profile"

    # Loop through the build types and run conan install
    for build_type in BUILD_TYPES:
        print(f"\n--- Running conan install for build_type: {build_type} ---")

        # Construct the conan install command
        command = [
            conan_executable,  # Use the determined conan executable path
            "install",
            ".",  # Assuming conanfile.txt or conanfile.py is in the current directory
            f"--profile:host={profile}",
            f"--profile:build={profile}",
            f"--settings=build_type={build_type}",
            "--build=missing"
        ]

        try:
            # Run the conan install command using subprocess.run
            # check=True will raise CalledProcessError if the command fails
            subprocess.run(command, check=True)
            print(f"Conan install successful for build_type {build_type}.")
        except subprocess.CalledProcessError as e:
            print(f"Error: conan install failed for build_type {build_type}.")
            print(f"Command: {' '.join(e.cmd)}")
            print(f"Return Code: {e.returncode}")
            # The bash script prints an error but continues the loop, so we do the same.
            # If you wanted to stop on the first error, you would add sys.exit(1) here.
    os.remove("../CMakeUserPresets.json")
    print("\nConan installation script finished.")
