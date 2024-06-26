# Install Docker Engine on Windows and Linux

## Table of Contents
- [Install Docker Engine on Windows and Linux](#install-docker-engine-on-windows-and-linux)
  - [Table of Contents](#table-of-contents)
  - [Install Docker Engine for Windows (with Docker Desktop)](#install-docker-engine-for-windows-with-docker-desktop)
  - [Install Docker Engine for Windows (with Rancher Desktop)](#install-docker-engine-for-windows-with-rancher-desktop)
    - [Using WSL](#using-wsl)
    - [Enable WSL](#enable-wsl)
    - [Install WSL and Upgrade WSL Version from 1 to 2](#install-wsl-and-upgrade-wsl-version-from-1-to-2)
    - [Proxy Settings](#proxy-settings)
    - [Install Docker CLI in WSL](#install-docker-cli-in-wsl)
    - [Install Docker-Compose](#install-docker-compose)
  - [Install Docker Engine for Linux](#install-docker-engine-for-linux)

---





## Install Docker Engine for Windows (with Docker Desktop)

**Note:** "Commercial use of Docker Desktop in larger enterprises (more than 250 employees OR more than $10 million USD in annual revenue) requires a paid subscription."

An alternative installation method is using [Docker Desktop](https://docs.docker.com/desktop/install/windows-install/).

---

## Install Docker Engine for Windows (with Rancher Desktop)

[Rancher Desktop](https://docs.rancherdesktop.io/getting-started/installation/) is an open-source alternative to Docker Desktop.

> ⚠️These steps are required for Rancher Desktop. If you prefer Docker Desktop, then you do not need to follow these steps.


### Using WSL

Windows Subsystem for Linux 2 (WSL2) provides a Linux kernel interface on Windows that allows you to run Linux containers.

### Enable WSL

1. Open the Start menu and search for **"Turn Windows features on or off."**
2. In the **Turn Windows features on or off** window, check the box next to **"Windows Subsystem for Linux."**
3. Click **"OK"** to enable the WSL feature.

or alternatively you should execute the commands below as administrator.

```bash
dism.exe /online /enable-feature /featurename:Microsoft-Hyper-V-All /all /norestart 
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart 
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
```

### Install WSL and Upgrade WSL Version from 1 to 2

1. Open **PowerShell** or **Command Prompt** as administrator.
2. Run the following command to install WSL with Ubuntu:

   ```sh
   wsl --install -d Ubuntu
   ```

3. Check your WSL version:

   ```sh
   wsl -l -v
   ```

4. If WSL version is not 2, update it using the following command:


   ```sh
   wsl.exe --update
   ```

   ```sh
   wsl.exe --set-version <distro_name> 2
   ```

   **Note:** You can list available distributions using:
   ```sh
   wsl --list --online
   ```

5. Set the default WSL version:

   ```sh
   wsl.exe --set-default-version 2
   wsl --set-default <distro_name>
   ```

### Proxy Settings

If you are using a proxied connection, set up your proxy server in WSL 2:

1. Open **PowerShell** or **Command Prompt** as administrator.
2. Execute WSL:
   ```sh
   wsl.exe
   ```
3. Open a configuration file using a text editor (e.g., nano or vi):
   ```sh
   sudo vi ~/.curlrc
   ```
4. Add your proxy settings:
   ```sh
   proxy=<proxy_server>:<port>
   ```

### Install Docker CLI in WSL

1. Open **WSL Terminal** and follow the Linux installation instructions:

   ```sh
   # Update package lists
   sudo apt update

   # Install Docker dependencies
   sudo apt install -y apt-transport-https ca-certificates curl software-properties-common

   # Add Docker GPG key
   curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg

   # Add Docker repository
   echo "deb [signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

   # Install Docker
   sudo apt update
   sudo apt install -y docker-ce docker-ce-cli containerd.io
   sudo apt install -y docker-compose
   ```

### Install Docker-Compose

Install the docker compose util from the link below.

https://github.com/docker/compose/releases/download/v2.35.0/docker-compose-windows-x86_64.exe


---

## Install Docker Engine for Linux

The easiest way to install Docker on Linux is by using the official Docker installation script:

```sh
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh
```

For more details, visit the [official Docker documentation](https://docs.docker.com/desktop/install/linux-install/).

