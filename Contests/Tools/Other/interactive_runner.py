# for GCJ

# This is a small program that runs two processes, connecting the
# stdin of each one to the stdout of the other.
# It doesn't perform a lot of checking, so many errors may
# be caught internally by Python (e.g., if your command line has incorrect
# syntax) or not caught at all (e.g., if the judge or solution hangs).
#
# Run this as:
# python interactive_runner.py <cmd_line_judge> -- <cmd_line_solution>
#
# For example:
# python interactive_runner.py python testing_tool.py 0 -- ./my_binaRy
#
# this will run the first test set of a python judge called "testing_tool.py"
# that receives the test set number (starting from 0) via command line parameter
# with a solution compiled into a binary called "my_binary".
#
# This is only intended as a convenient tool to help contestants test solutions
# locally. In particular, it is not identical to the implementation on our
# server, which is more complex.

from __future__ import print_function
import sys, subprocess, threading

class SubprocessThread(threading.Thread):
  def __init__(self,
               args,
               stdin_pipe=subprocess.PIPE,
               stdout_pipe=subprocess.PIPE,
               stderr_pipe=subprocess.PIPE):
    threading.Thread.__init__(self)
    self.p = subprocess.Popen(
        args,
        stdin=stdin_pipe,
        stdout=stdout_pipe,
        stderr=stderr_pipe)

  def run(self):
    try:
      self.return_code = self.p.wait()
      self.stdout = "" if self.p.stdout is None else self.p.stdout.read()
      self.stderr = "" if self.p.stderr is None else self.p.stderr.read()
    except (SystemError, OSError):
      self.return_code = -1
      self.stdout = ""
      self.stderr = "The process crashed or produced too much output."

assert sys.argv.count("--") == 1, (
    "There should be exactly one instance of '--' in the command line.")
sep_index = sys.argv.index("--")
judge_args = sys.argv[1:sep_index]
sol_args = sys.argv[sep_index + 1:]

t_sol = SubprocessThread(sol_args)
t_judge = SubprocessThread(judge_args, stdin_pipe=t_sol.p.stdout,
                           stdout_pipe=t_sol.p.stdin)
t_sol.start()
t_judge.start()
t_sol.join()
t_judge.join()
print("Judge return code:", t_judge.return_code)
print("Judge standard error:", t_judge.stderr.decode())
print("Solution return code:", t_sol.return_code)
print("Solution standard error:", t_sol.stderr.decode())
