# C++ 

## Command Line (Mac)

Install the latest version of gcc with homebrew.

```
brew install gcc
```

Open your bash profile with a text editor such as gedit (you might need to install this with homebrew as well). 

```
gedit ~/.bash_profile
```

Add the following functions.

```
co() { 
    g++-8 -std=c++17 -Ofast -Wall -Wl,-stack_size -Wl,0x10000000 -o $1 $1.cpp
}
run() {
    co $1 && ./$1
}
```

Now you can easily run C++ from the command line by calling run.

```
run [prog name]
```

## IDE 

### Online

* [CSAcademy](https://csacademy.com/workspace/)
	* I use this the most.
* [Ideone](http://ideone.com/)
* [Cloud9](https://c9.io/)

### Local

 * [Sublime Text 3](https://www.sublimetext.com/)
   * [Editing Build Settings](https://stackoverflow.com/questions/23789410/how-to-edit-sublime-text-build-settings)
   * [FastOlympicCoding Addon](https://github.com/Jatana/FastOlympicCoding)
 * [Geany](https://www.geany.org/)
 * [Visual Studio Code](https://code.visualstudio.com/)
 * [XCode](https://developer.apple.com/xcode/)
   * mac
 * [Codeblocks](http://www.codeblocks.org/)
   * bad on mac :(


## Useful Links

### Reference

* [cplusplus](http://www.cplusplus.com/reference/)
* [cppreference](http://en.cppreference.com/w/)


### Other

 * [Intro to Command Line](http://blog.teamtreehouse.com/introduction-to-the-mac-os-x-command-line)
 * [Command Line Shortcuts](https://jonsuh.com/blog/bash-command-line-shortcuts/)
 * [Run Python Script](https://stackoverflow.com/questions/7855996/cant-run-python-py-files-from-terminal-on-mac)
