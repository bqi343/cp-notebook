# Tools

Some written by me. Probably buggy, let me know about any issues.

 * grader.py
 	* Based off grader.sh. Outputs results in color!
 	* Given input and output files, check the correctness of a program.
 	* Given input files, compare two programs against each other.
 * cf.py:
 	* TLE's CF booster with some modifications.
 	* Downloads CF sample cases and parses input.
 	* Use during contest with grader.py and the -d flag.
 	* Test with the -t flag.
 * cf_subs.py:
 	* Downloads problem submissions.
 	* Use for Educational CF hacking with a test case generator and grader.py with the -g flag.
 * others parse problem statistics from various websites (codeforces, topcoder, ioi, usaco)

Some shortcuts which you might want to include in your bash profile if using these:

```
alias cf="python3 cf.py"
test() { # from folder $ run $.cpp against test cases
	python3 ../grader.py -d ${PWD##*/}
}
CD() { # navitage to folder containing $.cpp
	if [ ! -d "$1" ]
	then
		cd ..
	fi
	cd $1 && subl $1.cpp
}
```

There is also a USACO results script by Ethan Guo. Go to any results page (such as [this](http://www.usaco.org/current/data/dec19_platinum_results.html) one) and paste the code into the console.
