# C++

## Command Line (Mac)

### Option 1

```
brew install gcc
```

Then you should be able to compile with g++-#, where # is the version number (currently 9).

### Option 2

Follow the instructions [here](https://wiki.helsinki.fi/display/HUGG/GNU+compiler+install+on+Mac+OS+X?fbclid=IwAR3bnM6A_kTgXD2p5nOfVbxRRQ4nHMj89jllNy1-zdtfXfcq1czbSoXiWgE). Step 4 will give errors but it should still install.

Running the following command should not display clang.

```
gcc --version
```

Then you should be able to compile with g++.

## Shortcuts

Open your bash profile with a text editor such as gedit.

```
brew install gedit
gedit ~/.bash_profile
```

Add the following functions.

```
co() {
    g++ -std=c++17 -Ofast -Wall -Wl,-stack_size -Wl,0x10000000 -o $1 $1.cpp
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
xcode-select --install
xcode-select --version
softwareupdate --list
softwareupdate -i -a
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

Whoops I can't figure out how to use g++ successfully D:
Maybe the following links are helpful?

 * [StackOverflow](https://stackoverflow.com/questions/58278260/cant-compile-a-c-program-on-a-mac-after-upgrading-to-catalina-10-15)
 * [SolarianProgrammer](https://solarianprogrammer.com/2019/10/12/compiling-gcc-macos/)

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
