// usain
// Keith Miklas, keith@algorithmicquantitative.com
//
// Published under the OSI MIT license:
// https://opensource.org/licenses/MIT
//
// This program will generate a random stream of stock prices at incredibly fast speeds.
//

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>
#include <cstring>

#define _USE_MATH_DEFINES
const std::string version("1.2.1");
const std::string date("05 Aug 2016");

class Usain {
public:
	Usain():price_(100),m_(100),move_(0) {
		srand(time(NULL));
	};
	Usain(int price):price_(price),m_(price),move_(0) {
		srand(time(NULL));
	};
	~Usain() {};
	double tick();
private:
	double 		price_;
	double 		m_; 	// Measure of central tendency.
	double 		move_;
};


double Usain::tick() {
	double move_;
	move_ = ((double)((rand() % 101) - 50))/1000;
	if (price_ < m_) {
		if (move_ < 0) { // If the price is below m, reduce a downmove by a ratio of price to m.
			move_ = move_ * price_ / m_;
		}
	} else { // price >= m
		if (move_ > 0) { // If the price is above m, reduce an upmove by a similar ratio.
			move_ = move_ * (2 * m_ - price_) / m_;
		}
	}
	price_ += move_;
	return price_;
}

int main(int argc, char** argv) {
	Usain hound, decoy;
	long long int specifiedTicksPerSecond(0), maxTicksPerSecond(0), n(0), d(0), delay(0);
	double a(0), timePerTick(0), throttle(0);
	bool verbose(true);
	if (argc == 1) {
		std::cout << "~ Usage: usain <(int)|bolt> <verbose|quiet>" << std::endl;
		std::cout << "~ Examples:" << std::endl;
		std::cout << "  \"usain 10\" generates 10 ticks per second (100ms tick time), and writes to screen" << std::endl;
		std::cout << "  \"using 4 verbose\" generates 4 ticks per second (250ms tick time), and writes to screen" << std::endl;
		std::cout << "  \"usain 20 quiet\" generates 4 ticks per second (50ms tick time), and writes nothing" << std::endl;
		std::cout << "  \"usain 100000 quiet\" generates 100000 ticks per second; e.g., 10mcs ticks, and writes nothing" << std::endl;
		std::cout << "  \"usain 10000000 quiet\" generates 10000000 ticks per second; e.g., 100ns ticks, and writes nothing" << std::endl;
		std::cout << "  \"usain bolt\" generates the fastest possible ticks for your rig. Quiet mode forced." << std::endl;
		std::cout << "~ NOTE: Screen writing is expensive; generally, anything over 100mcs must be run in quiet mode. ";

	} else {
		std::cout << "~ usain v" << version << ", " << date << std::endl;
		std::cout << "~ https://opensource.org/licenses/MIT" << std::endl;

		// Take 1000 tick measurements for an educated guess at initial throttling
		// It's dynamically adjusted anyway, but we try to get close
		auto dummyStart = std::chrono::high_resolution_clock::now();
		auto dummyEnd = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> dummyTickTime = (dummyEnd - dummyStart);	
		double dummyTick;
		auto start = std::chrono::high_resolution_clock::now();
		for (int i=0; i<1000; ++i) {
				decoy.tick();
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> tickTime = (end - start)/1000;
		int maxTicksPerSecond = (int)(round(1/tickTime.count()));

		// set ticks per second

		if (!std::strcmp(argv[1],"bolt") || !std::strcmp(argv[1],"BOLT")) {
			specifiedTicksPerSecond = maxTicksPerSecond; // "I feel the need.. the need, for speed"
			verbose = false;
		} else {
			specifiedTicksPerSecond = atoi(argv[1]);
		}
		std::cout << "~ Maximum ticks your rig can generate in one second: " << std::fixed << maxTicksPerSecond << std::endl;
		std::cout << "~ Your specified ticks per second: " << specifiedTicksPerSecond << std::endl;
		std::cout << "~ Usain Bolt set the 100m dash world record on 8/16/2009 with a time of 9.58 seconds." << std::endl << std::endl;

		// set quiet or verbose mode
		if (argc > 2) {
			verbose = (!strcmp(argv[2],"quiet")) ? false : true;
		}
		if (!verbose) {
			std::cout << "~ Quiet mode is on. Generating ticks..." << std::endl;
		}
		// We calculate dummy ticks to pace ticks according to User specification
		// Another alternative would be to specify a <chrono> time interval here.
		timePerTick = (1./specifiedTicksPerSecond);
		int sleepTicks = trunc(maxTicksPerSecond/specifiedTicksPerSecond);
	    double adjustment(0);
		while(1) {
			start = std::chrono::high_resolution_clock::now();
		    for (int i=0; i<sleepTicks; ++i) {
		    	decoy.tick();
	   		}
			end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> tickTime = end - start;
			if (verbose) {
		   		std::cout << std::setprecision(2) << hound.tick() << "\t\t"; // price
				std::cout << std::setprecision(12) << tickTime.count() << std::endl; // time in seconds
			}
			throttle = (1./specifiedTicksPerSecond) - tickTime.count();
			sleepTicks = sleepTicks + (int)(throttle * sleepTicks);
			if ((verbose) && (n > 25)) {
				std::cout << "_price\t\t_tick_time_in_seconds" << std::endl;
				n = 0;
			} else {
				++n;			
			}

	   	}
		std::cout << std::endl;
		std::cout << "Process running, ticks being generated on port XXXX. Press Ctrl+c to halt." << std::endl;
	}
	std::cout << "\n";
	return(0);
}