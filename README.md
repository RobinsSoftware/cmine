## CMine

CMine is currently in the early stages of development. It intends to imitate the Notchian protocol as laid out by [wiki.vg](https://wiki.vg).

CMine is entirely written in C, and was created for me to learn more about socket & game server programming. In the end, if continued into the future, I intend to develop and contribute a fully working server program after I complete university.

If you are interested in contributing to CMine through code or feedback, feel free to send an email to [lola@robinssoftware.ca](mailto:lola@robinssoftware.ca), or, contact me on Discord @ `lola <3#5866`.

### Current Goals
* ~~Import libraries from old projects to handle memory management, etc.~~
* ~~Create thread & socket libraries.~~
* ~~Get console commands to work & implement safe server shutdown.~~
* Create a system for processing inbound and outbound packets.
* Working MOTD from file.
* Spawn players in a void.
* Send & receive chat, command parsing.

### Requirements
* CMake v3.16+.
* C compiler such as gcc or clang.
* POSIX-compliant operating system such as macOS, Linux, etc.

### Building
A simple build script exists to fully compile CMine.

 1. Make `build.sh` executable by executing `sudo chmod 775 ./build.sh` in the project's directory.
 2. Execute `build.sh`.
 3. Run CMine with `./CMine-server`.

### Launch Flags
* `-a <address>` Set the address to listen on.
* `-p <port` Set the port to listen on.
* `-c` Disabled colored/formatted terminal output.
* `-d` Show debug logging.
* `-h` Show available flags & help for executing CMine.