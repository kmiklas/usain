# usain

Welcome! This program will generate dummy stock ticks at user-specified speeds.
Usain Bolt set the 100m dash world record on 8/16/2009 with a time of 9.58 seconds.

# Introduction

This program was born of frustration.

As a computer scientist and quantitative analyist, I wanted to write programs to analyze stock data with statistical, cryptographic, pattern recognition, and other methods. As it turns out, this usage of data is highly regulated, and VERY expensive--can easily cost tens of thousands of USD per month. These are called "non-display fees." [1][2]. 

So, what to do? I had to remain in compliance with regulations; however, a data feed was far beyond my price range. At the same time, I still wanted to develop quantitative algorithms for real-time analysis of tick data.

The only answer was to write a script to generate my own data. There, I faced no restrictions, and could write analytic algorithms to my heart's content.

# Usage

The script is quite simple to use.
- For usage, just type "usain" or "./usain" if you do not have your path set.

Here is usage copy:

[~/a/l/g/usain] $ ./usain
~ Usage: usain <(int)|bolt> <verbose|quiet>
~ Examples:
  "usain 10" generates 10 ticks per second (100ms tick time), and writes to screen
  "using 4 verbose" generates 4 ticks per second (250ms tick time), and writes to screen
  "usain 20 quiet" generates 4 ticks per second (50ms tick time), and writes nothing
  "usain 100000 quiet" generates 100000 ticks per second; e.g., 10mcs ticks, and writes nothing
  "usain 10000000 quiet" generates 10000000 ticks per second; e.g., 100ns ticks, and writes nothing
  "usain bolt" generates the fastest possible ticks for your rig. Quiet mode forced.
~ NOTE: Screen writing is expensive; generally, anything over 100mcs must be run in quiet mode. 







  




