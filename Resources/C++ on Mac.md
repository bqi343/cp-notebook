# C++

## Command Line (Mac)

### Option 1

```
brew install gcc
```
According to [this](https://stackoverflow.com/questions/30998890/installing-opencv-with-brew-never-finishes) if brew doesn't seem to finish for a long time then 
```
brew install gcc --force-bottle
```
probably suffices.

### Option 2 (Old))

Follow the instructions [here](https://wiki.helsinki.fi/display/HUGG/GNU+compiler+install+on+Mac+OS+X?fbclid=IwAR3bnM6A_kTgXD2p5nOfVbxRRQ4nHMj89jllNy1-zdtfXfcq1czbSoXiWgE). Step 4 will give errors but it should still install.

### Confirmation

You should be able to compile with g++ or maybe g++-#, where # is the version number (currently 9). Running the following command:
```
g++-9 --version
```
should display something like this:
```
g++-9 (Homebrew GCC 9.2.0_2) 9.2.0
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

## Shortcuts

Open your bash profile with a text editor such as gedit (or sublime).
```
brew install gedit
gedit ~/.zshenv
```
You can add aliases and functions here, such as the following:
```
alias clr="clear"
alias ZES='source ~/.zshenv'
alias ZEO='subl ~/.zshenv'
alias IMPL='cd ~/Documents/GitHub/USACO/Implementations/'
co() {
	g++-9 -std=c++11 -O2 -Wl,-stack_size -Wl,0x10000000 -Wall -Wextra -o $1 $1.cpp
}
run() {
	co $1 && ./$1
}
```
Now you can easily run C++ from the command line by calling run.
```
run [prog name]
```

## Troubleshooting

Make sure you have installed XCode command line tools.
```
xcode-select --install # make sure x-code command line tools are installed
softwareupdate --list
softwareupdate -i -a # installs everything
```

### OS X Mojave

Navigate to your bash profile
```
gedit ~/.bash_profile
```
and add the following line:
```
export CPLUS_INCLUDE_PATH="/usr/local/include/c++/8.1.0/:/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.14.sdk/usr/include:$CPLUS_INCLUDE_PATH"
```

### OS X Catalina

Maybe the following links are helpful?

 * [StackOverflow](https://stackoverflow.com/questions/58278260/cant-compile-a-c-program-on-a-mac-after-upgrading-to-catalina-10-15)
 * [SolarianProgrammer](https://solarianprogrammer.com/2019/10/12/compiling-gcc-macos/)

~~Whoops I couldn't figure out how to use g++ successfully D:~~ Turns out that g++ was linked to g++-8 instead of g++-9, changing it now works.

## Tools

### Online

 * [CSAcademy](https://csacademy.com/workspace/)
	 * I used this a lot until the queue time limits got rlly annoying
 * [Ideone](http://ideone.com/)
	 * seems okay if you use an ad blocker
	 * sometimes randomly erases your code when you first create it (so get in the habit of copying your code before creating it :P)

### Local IDEs

 * [Geany](https://www.geany.org/)
 * [Visual Studio Code](https://code.visualstudio.com/)
 * [XCode](https://developer.apple.com/xcode/)
	 * mac
 * [Codeblocks](http://www.codeblocks.org/)
	 * bad on mac :(

### Text Editors

 * [Sublime Text 3](https://www.sublimetext.com/)
	 * [Editing Build Settings](https://stackoverflow.com/questions/23789410/how-to-edit-sublime-text-build-settings)
	 * [FastOlympicCoding Addon](https://github.com/Jatana/FastOlympicCoding)
	 * [Symlink](https://www.sublimetext.com/docs/3/osx_command_line.html) 
		 * Using '/usr/local/bin/subl' instead of '~/bin/subl' worked for me on OS X Mojave.
 * [Atom](https://atom.io/)

## Useful Links

### Reference

 * [cplusplus](http://www.cplusplus.com/reference/)
 * [cppreference](http://en.cppreference.com/w/)

### Other

 * [Intro to Command Line](http://blog.teamtreehouse.com/introduction-to-the-mac-os-x-command-line)
 * [Command Line Shortcuts](https://jonsuh.com/blog/bash-command-line-shortcuts/)
 * [Run Python Script](https://stackoverflow.com/questions/7855996/cant-run-python-py-files-from-terminal-on-mac)
 * [Competitive C++ Style Guide](https://codeforces.com/blog/entry/64218)
