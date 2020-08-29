# Terminal App Launcher

### Building
This depends on:
ncurses and gtk3
(install these from your favourite package manager)

    mkdir build
    cd build
    cmake ..
    make
    sudo make install

### Setup
Place a file in your home directory with the name "launcher.conf".
The contents should be in the same format as in the included "launcher_example.conf".
The format is "NAME_OF_PROGRAM:COMMAND"
##### There must be exactly one newline at the end of the launcher.conf or the last program will not be read