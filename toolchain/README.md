# Skrunix toolchain

## Requirements

###### macOS
- Xcode and Command line tools
- Homebrew
- `brew install bash make wget`

###### Ubuntu
- `apt-get -qq update`
- `apt-get -qq --no-install-recommends install wget ca-certificates build-essential`

## Docker

Might require more ram

- ``docker run --volume `pwd`:/Skrunix/toolchain -w/Skrunix/toolchain -it ubuntu:18.04 bash``
