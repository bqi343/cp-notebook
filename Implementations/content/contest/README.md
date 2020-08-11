# Template Notes

 * The header files will not compile with clang; use gcc instead.
 * .bashrc:
   * clr in comes from [here](https://superuser.com/questions/122911/what-commands-can-i-use-to-reset-and-clear-my-terminal). \033 denotes ESC.
  
TopCoder:

[New Java Applet](https://codeforces.com/blog/entry/64597) (use ctrl-c instead of command-c on mac ...)

## Generating Random Numbers

```cpp
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
```

See [neal's blog](https://codeforces.com/blog/entry/61587) about why `rand()` is bad. Use `rng()` instead.

## Generating Sublime Snippets

<Resources>
	<Resource
		source="ST"
		url="https://docs.sublimetext.io/guide/extensibility/snippets.html#snippets-file-format"
		title="Snippets"
		starred
	>
		documentation
	</Resource>
</Resources>

I use [this python script](https://github.com/bqi343/USACO/blob/master/Implementations/content/contest/makeSnip.py) to automatically update snippets for all of my templates.

Instructions (Mac):

1. Install `python3`.
2. Clone [my USACO repository](https://github.com/bqi343/USACO) to `~/Documents/USACO`.
3. Add the following to your `~/.zshenv`.


    ```
    export USACO=~/Documents/USACO
    makeSnip() {
      cd $USACO/Implementations/content/contest
      python3 genShort.py
      python3 genLong.py
      python3 $USACO/Contests/Tools/Other/makeSnip.py
    }
    ```

4. Run `makeSnip` from terminal. It should display a list of the templates that will be added as snippets.
5. If this succeeded, then typing `Temp` in a cpp file will automatically load my template!

<Info title="Pro Tip">

Instead of copy pasting algorithms into snippets, it's a good idea to write
the algorithm yourself first. Knowing how to write the algorithm is not only
important because you can't use snippets in USACO contests, but also helps
your understanding of the algorithm!

</Info>
