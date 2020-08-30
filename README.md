# Terminal App Launcher

### Building
This depends on:
ncurses and gtk3 (both dev versions)
##### Ubuntu (And Debian Probably):
    sudo apt install libncurses-dev libgtk-3-dev
##### Fedora / RHEL / Centos
    sudo dnf install ncurses-devel gtk3-devel

##### Compilation
    mkdir build
    cd build
    cmake ..
    make
    sudo make install

### Setup
Place a file in your home directory with the name "launcher.conf".
The contents should be in the same format as in the included "launcher_example.conf".
The format is "NAME_OF_PROGRAM:COMMAND"
##### The config file must not be more than 64 lines, after that they will not be read.
##### To Allow more data in the file, increase the the definition MAX_FILE_LEN in the parser.c file