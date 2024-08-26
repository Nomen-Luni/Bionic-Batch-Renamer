# Bionic Batch Renamer

A powerful batch file renaming utility built with the Qt technology stack.

Interface heavily inspired by [Thunar's 'bulk renamer'](https://docs.xfce.org/xfce/thunar/bulk-renamer/start) plugin.

<img title="" src="./Images/Bionic_Batch_Renamer.png" alt="Bionic_Batch_Renamer.png" width="441">

#### Creation of installer:

- Build the release executable in QtCreator.

- For Ubuntu and other Debian based Linux distributions:
  
  - Navigate to the ''Deb Packaging' directory and run ''MakeDeb' to create the .deb distribution package.

#### Installation:

- From Dolphin File Manager in KDE Plasma:
  
  - From the Dolphin menu select 'Settings->Configure Dolphin->Context Menu->Download New Services' and search for 'Bionic Batch Renamer.'
    - Select the .deb file to install on Ubuntu and Debian based distros.
    - Select the .tar file to install on Arch based distros.
  - This will add the option 'Batch rename' to the right-click menu in the file manager when multiple files are selected.

- On Ubuntu and other Debian based Linux distributions:
  - Double-click the .deb installation file and install via your package manager. The executable will be located at /usr/local/bin/Batch_Renamer.

- On Arch based Linux distributions:
  - Double-click the .tar installation file and install via your package manager  
    or use the [AUR package](https://aur.archlinux.org/packages/bionic-batch-renamer-git)

#### Authors:

- Lee Cooper
- Heimen Stoffels (Dutch translation)
- Carl F (Arch installer)
