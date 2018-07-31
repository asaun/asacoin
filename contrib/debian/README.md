
Debian
====================
This directory contains files used to package asacoind/asacoin-qt
for Debian-based Linux systems. If you compile asacoind/asacoin-qt yourself, there are some useful files here.

## asacoin: URI support ##


asacoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install asacoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your asacoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/asacoin128.png` to `/usr/share/pixmaps`

asacoin-qt.protocol (KDE)

