# How to set up the

- Fork the qmk repository. IMPORTANT!!! The fork is public and you cannot
make it private. Do not store private info.
- Clone your fork
```
cd /data/www/projects/qmk
git clone --recurse-submodules https://github.com/nikolayivanovivanov/qmk_firmware.git

cd ./qmk_firmware
vagrant up
vagrant ssh
#cd /vagrant/keyboards/lily58/keymaps/nii
#touch config.h
#touch keymap.c
#touch rules.mk
# Copy https://github.com/splitkb/qmk_firmware/tree/lily58-splitkb/keyboards/lily58/keymaps/splitkb into the lily folder and

cd /vagrant
make lily58/nii


```


Copy of text after the vagrant up command below
- Log into the environment using 'vagrant ssh'. QMK directory synchronized with
host is located at /vagrant
- To compile the .hex files use make command inside this directory, e.g.
   cd /vagrant
   make <keyboard>:default

Examples:
   make planck/rev4:default:dfu
   make planck/rev4:default
