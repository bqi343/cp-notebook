#!/bin/sh
# This file should build and run your code.
# It will run if you're in nodocker mode on Mac or Linux,
# or if you're running in docker.

# Compile our code.
echo javac $(find . -name '*.java') -classpath ../battlecode/java
javac $(find . -name '*.java') -classpath ../battlecode/java

# Run our code.
echo java -classpath .:../battlecode/java Player
java -classpath .:../battlecode/java Player
