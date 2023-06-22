#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#ifdef OS_WINDOWS
#	include <windows.h>
#else
#	include <time.h>
#endif

using FuncPtr = void (*)(std::chrono::nanoseconds);

std::chrono::nanoseconds testSleep(FuncPtr sleepFunction, std::chrono::nanoseconds sleepTime) {
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	sleepFunction(sleepTime);

	return std::chrono::steady_clock::now() - start;
}

void sleepFor(std::chrono::nanoseconds sleepTime) {
	std::this_thread::sleep_for(sleepTime);
}

void sleepUntil(std::chrono::nanoseconds sleepTime) {
	std::this_thread::sleep_until(std::chrono::steady_clock::now() + sleepTime);
}

void conditionVariableWaitFor(std::chrono::nanoseconds sleepTime) {
	std::mutex mutex;
	std::unique_lock< std::mutex > lock(mutex);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now() + sleepTime;

	std::condition_variable var;

	var.wait_for(lock, sleepTime, [&end]() { return std::chrono::steady_clock::now() >= end; });
}

void conditionVariableWaitUntil(std::chrono::nanoseconds sleepTime) {
	std::mutex mutex;
	std::unique_lock< std::mutex > lock(mutex);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now() + sleepTime;

	std::condition_variable var;

	var.wait_until(lock, end);
}

void spinWaitYield(std::chrono::nanoseconds sleepTime) {
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now() + sleepTime;

	while (std::chrono::steady_clock::now() < end) {
		std::this_thread::yield();
	}
}

void spinWaitBusy(std::chrono::nanoseconds sleepTime) {
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now() + sleepTime;

	while (std::chrono::steady_clock::now() < end) {
	}
}

#ifdef OS_WINDOWS
void osSleep(std::chrono::nanoseconds sleepTime) {
	Sleep(std::chrono::duration_cast< std::chrono::milliseconds >(sleepTime).count());
}
#else
void osSleep(std::chrono::nanoseconds sleepTime) {
	timespec spec;
	spec.tv_sec  = 0;
	spec.tv_nsec = sleepTime.count();
	nanosleep(&spec, nullptr);
}
#endif

std::string to_string(std::chrono::nanoseconds duration) {
	if (duration >= std::chrono::seconds(1)) {
		return std::to_string(std::chrono::duration_cast< std::chrono::seconds >(duration).count()) + "s";
	} else if (duration >= std::chrono::milliseconds(1)) {
		return std::to_string(std::chrono::duration_cast< std::chrono::milliseconds >(duration).count()) + "ms";
	} else if (duration >= std::chrono::microseconds(1)) {
		return std::to_string(std::chrono::duration_cast< std::chrono::microseconds >(duration).count()) + "us";
	} else {
		return std::to_string(std::chrono::duration_cast< std::chrono::nanoseconds >(duration).count()) + "ns";
	}
}

int main() {
	constexpr std::size_t repetitions = 20;

	std::cout << "Averaging sleep errors over " << repetitions << " repetitions" << std::endl;

	std::vector< FuncPtr > functions = {
		sleepFor, sleepUntil, conditionVariableWaitFor, conditionVariableWaitUntil, osSleep, spinWaitYield, spinWaitBusy
	};
	std::vector< std::string > functionNames = {
		"sleepFor",      "sleepUntil",  "conditionVariableWaitFor", "conditionVariableWaitUntil", "osSleep",
		"spinWaitYield", "spinWaitBusy"
	};

	if (functionNames.size() != functions.size()) {
		std::cerr << "Implementation error" << std::endl;

		return 1;
	}

	for (std::chrono::nanoseconds duration : std::vector< std::chrono::nanoseconds >{
			 std::chrono::nanoseconds(100), std::chrono::microseconds(100), std::chrono::milliseconds(1),
			 std::chrono::milliseconds(10), std::chrono::milliseconds(100) }) {
		std::cout << "Targeting a sleep of " << to_string(duration) << " - errors:" << std::endl;

		for (std::size_t i = 0; i < functions.size(); ++i) {
			std::chrono::nanoseconds diff(0);

			for (std::size_t k = 0; k < repetitions; k++) {
				std::chrono::nanoseconds actual = testSleep(functions[i], duration);

				diff += actual - duration;
			}

			diff /= repetitions;

			std::cout << "  " << to_string(diff) << " (" << (100 * diff.count() / duration.count()) << "%) - "
					  << functionNames[i] << std::endl;
		}
	}

	return 0;
}
