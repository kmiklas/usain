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
const std::string version("2.1.1");
const std::string date("08 Aug 2016");

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
	Usain u, decoy;
	long long int ticksPerSecond(0), maxTicksPerSecond(0), n(0), d(0), delay(0);
	double a(0), timePerTick(0), throttle(0);
	bool verbose(true);
	if (argc == 1) { //usage
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

		// Take 1000000 tick measurements for an reasonable guess at max tick speed
		std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
		for (long int i=0; i<1000000; ++i) {
				u.tick();
		}
		std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> tickTime = (end - start)/1000000;
		int maxTicksPerSecond = (int)(round(1/tickTime.count()));

		// set ticks per second
		if (!std::strcmp(argv[1],"bolt") || !std::strcmp(argv[1],"BOLT")) {
			ticksPerSecond = maxTicksPerSecond; // "I feel the need.. the need, for speed"
		} else {
			ticksPerSecond = atoi(argv[1]);
		}
	    std::chrono::duration<double> desiredTickDuration(1./ticksPerSecond);
		std::cout << "~ Maximum ticks your rig can generate in one second: " << std::fixed << maxTicksPerSecond << std::endl;
		std::cout << "~ Your specified ticks per second: " << ticksPerSecond << std::endl;
	    std::cout << "~ Time per tick, in seconds: " << desiredTickDuration.count() << std::endl;
		std::cout << "~ NOTE: Screen writing is expensive; generally, anything over 100mcs must be run in quiet mode. " << std::endl;
		std::cout << "~ Usain Bolt set the 100m dash world record on 8/16/2009 with a time of 9.58 seconds." << std::endl << std::endl;
		// set quiet or verbose mode
		if (argc > 2) {
			verbose = (!strcmp(argv[2],"quiet")) ? false : true;
		}
		if (!verbose) {
			std::cout << "~ Quiet mode is on. Generating ticks..." << std::endl;
		}
		std::chrono::high_resolution_clock::time_point prevTickTime = std::chrono::high_resolution_clock::now();
		std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::duration<double> > nextTickTime = std::chrono::high_resolution_clock::now() + desiredTickDuration;
	    std::chrono::duration<double, std::ratio<1, 1>> actualTickDuration(0.);
	    while(1) {
	    	prevTickTime = std::chrono::high_resolution_clock::now();
	    	while (std::chrono::high_resolution_clock::now() < nextTickTime) {
	    		// wait...
	    	};
	    	// A little tuning
	    	actualTickDuration = std::chrono::high_resolution_clock::now() - prevTickTime;
	    	if (actualTickDuration > desiredTickDuration) { // A little slow; subtract the difference
		    	nextTickTime = std::chrono::high_resolution_clock::now() + desiredTickDuration - (0.5 * (actualTickDuration - desiredTickDuration));
	    	} else { // A little fast; add the difference
		    	nextTickTime = std::chrono::high_resolution_clock::now() + desiredTickDuration + (0.5 * (desiredTickDuration - actualTickDuration));
	    	}
			if (verbose) {
			   	std::cout << std::setprecision(2) << u.tick() << "\t\t"; // price
				std::cout << std::setprecision(12) << (std::chrono::high_resolution_clock::now().time_since_epoch().count() - prevTickTime.time_since_epoch().count()) << std::endl; // time in seconds
				if (n>20) {
					std::cout << "_price\t\t_tick_time_in_nanoseconds" << std::endl;
					n=0;
				}
			} else {
				u.tick();
			}
	    	++n;
	    }
	}
	std::cout << "\n";
	return(0);
}