# Template Notes

 * The header files will not compile with clang; use gcc instead.
 * .bashrc:
   * clr in comes from [here](https://superuser.com/questions/122911/what-commands-can-i-use-to-reset-and-clear-my-terminal). \033 denotes ESC.
   * On mac, use g++-9 and add -Wl,-stack_size -Wl,0x10000000 to co to avoid stack size issues.
 * stress.sh:
   * Source: [Errichto - testing sols](https://www.youtube.com/watch?v=JXTVOyQpSGM)

TopCoder:

[New Java Applet](https://codeforces.com/blog/entry/64597) (use ctrl-c instead of command-c on mac ...)

# CF Hacking

  * [Java Arrays.sort()](https://codeforces.com/blog/entry/4827)
	* [One that actually works?](https://codeforces.com/contest/1324/submission/73058869)
  * [Blowing up unordered_map](https://codeforces.com/blog/entry/62393)