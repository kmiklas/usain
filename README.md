# USAIN

Welcome! This program will generate dummy stock ticks at user-specified speeds.

**Table of Contents**  *generated with [DocToc](http://doctoc.herokuapp.com/)*

- [USAIN](#)
- [Screen Shot](#)
- [Introduction](#)
- [Performance](#)
- [Usage](#)
- [Todo](#)
- [Usain Bolt](#)
- [Legal](#)
- [References](#)

# Screen Shot

![alt text](http://www.miklas.org/images/usain_verbose.png "usain tick generator image")

# Introduction

As a Financial Engineer, Computer Scientist, and Quantitative Analyist, I found myself in a dilemma.

I wanted to write algorithms to analyze stock data with statistical, cryptographic, pattern recognition, and other methods. Little did I realize the nasty surprise that awaited me. As it turns out, this usage of market data is highly restricted, and VERY expensive--it can easily cost tens of thousands of USD per month. These are called "non-display fees." In other words, if you simply pipe a data feed into a terminal, the fee is minimal; around $6. If you use an API, fees are thousands of dollars per exchange. [1][2][3]

What to do? I had to remain in compliance with regulations; however, a data feed was out of my price range. At the same time, I still wanted to develop quantitative algorithms for real-time analysis of tick data.

The only answer was to write a program to generate my own data. There, I faced no restrictions, and could write analytic algorithms to my heart's content.

Thus, was born Usain; and here it is for you to enjoy. John 3:16.

# Performance

In addition to avoiding exchange fees and regulations, Usain produces speeds far beyond that of almost all professional data feeds--even those leveraging computers collocated at exchanges. With the possible exception of those able to run their scripts *directly on exchange computers* (which is probably illegal, definitely mind-bogglyingly expensive, or both) Usain beats them all: this is *low* low latency.

Why? Because it runs locally on your machine; no fiber, cabling, ethernet, NIC, and all the associated delays.

On my relatively cheap rig, which sports an Intel I7-4790K LGA1150 Core Duo processor, ASUS Z-97 Pro Mobo, and Centos 7 Linux, I get tick speeds of about 1.5 nanoseconds--without any real optimization effort.

![alt text](http://www.miklas.org/images/usain_silent.png "usain tick generator image")

# Usage

The script is quite simple to use.
- For usage, just type "usain" or "./usain" if you do not have your path set.

Having struggled for decades to make things work with little or no documentation, I really try to make things as easy as possible.

Note that writing ticks to the screen is very expensive, and can easily slow your ticks down by a factor of 0.0001 or more. For optimal performance, quiet mode is required. Generally speaking, for tick speeds faster than 100mcs, quiet mode is required.

Here is usage copy, which includes some helpful examples.

![alt text](http://www.miklas.org/images/usain_usage.png "usain tick generator image")

# Todo

This is the first commit, and it works, but there's a lot more that I want to do with this program. I'm hoping that some of you C++ gurus out there might help:

1. Implement the client-server model. Usain is the server; a client is needed to receive and process the data. This would require creating an interface between the client and server. I plan to model this afer industry-standard interfaces. I'm about 50% done with this script as of 05 Aug 2016. 
2. Build some clients for data analysis. I intend to provide a simple example that pushes Usain data into a circular FIFO, and computes basic statistical information: mean, median, mode, standard deviation (aka volatility), skew, moments, etc.
3. Build a standard interface so that industry-standard terminals can connect to this feed (Ninjatrader&reg; Sierra Charts&reg;, even Bloomberg Terminal&reg;). Part of this would entail creating USAIN as a full-fledged ticker symbol, with historical data.
4. Rework the tick generation algorithm--I had to hack something together. Perhaps give the user the option to generate according to a mathematical model of their choice.<br>
Side note: Initially, I innocently wrote a random number generator to produce Brownian motion, using the rand() function. This did not work! After a few seconds and a trillion ticks, USAIN flew off the handle, and quickly either spiked up to an incredible value, or went either spectacularly out of business at a price of about +/-$4000.00. I leave it to the reader to decide what this says about the theories of Browninan motion.
5. Include a command-line parser, so that options can be specfied. Example: usain --tickspeed 10 --verbose --model stochastic.

# Usain Bolt

Usain Bolt is, at this time, the fastest human in the world.

He set the 100m dash world record on 8/16/2009 with a time of 9.58 seconds.

![alt text](http://www.miklas.org/images/usain_gold.jpg "usain tick generator image")

# Legal

This software is published under the MIT license, available at the following link:
https://opensource.org/licenses/MIT

A copy of this license is here provided as a courtesy, but may be dated. At the above link resides the document of record.

The MIT License (MIT)
Copyright (c) <year> <copyright holders>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

# References

1. NYSE fee schedule: http://www.nyxdata.com/Docs/Market-Data/Pricing
2. Nasdaq fee schedule: http://nasdaqtrader.com/Trader.aspx?id=DPUSdata
3. "U.S. Brokers Face Big Rise in Exchange Fees Thanks to SEC Ruling" [Bloomberg, July 31 2015] http://www.bloomberg.com/news/articles/2015-07-31/u-s-brokers-face-big-rise-in-exchange-fees-thanks-to-sec-ruling




  




