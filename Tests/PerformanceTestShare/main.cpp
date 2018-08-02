#include <SSCodeEngine.h>
#include <SSFile.h>
#include <algorithm> 
#include <iostream>
#include <fstream>
#include <chrono>

//#define __PRINT__
/**
 * parameters 
 */
#define MAX_FILE_SIZE	1000000

#define MAX_CODE_SIZE	1000

#define MIN_CODE_SIZE	1

#define MAX_DENSITY_SIZE 3

#define MIN_DENSITY_SIZE 0

#define MAX_FIELD_SIZE	255

#define MIN_FIELD_SIZE	1

#define CODE_SIZE	200

#define TEST_SIZE	100

#define MIN_REDUNDANCY	3

#define MAX_REDUNDANCY	3

#define FIELD_SIZE	3

/**
 */
typedef struct __result__ {

	__result__(float_t p, time_t t) : prob(p), time(t) {
	}
	float_t prob;
	time_t time;
} Result;

/**
 * 
 */
Result process(ListBuffer& data, ListDensity& density, uint32_t framesize, uint32_t redundancy) {
	int n_fail = 0;
	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < TEST_SIZE; ++i) {
#ifdef __PRINT__
		std::cout << "i=" << i << std::endl;
		auto start = std::chrono::steady_clock::now();
#endif
		SSCodeEngine e(framesize, data.size(), data.size() + redundancy, data.size() + redundancy, density);

#ifdef __PRINT__
		std::cout << "start" << std::endl;
		auto start_e = std::chrono::steady_clock::now();
#endif
		auto coded = e.Encode(data);
#ifdef __PRINT__
		auto end_e = std::chrono::steady_clock::now();
		std::cout << "encode=" << std::chrono::duration_cast<std::chrono::microseconds>(end_e - start_e).count() << std::endl;
		auto start_d = std::chrono::steady_clock::now();
#endif
		auto result = e.Decode(coded);

#ifdef __PRINT__
		auto end = std::chrono::steady_clock::now();
		auto end_d = std::chrono::steady_clock::now();
		std::cout << "decode=" << std::chrono::duration_cast<std::chrono::microseconds>(end_d - start_d).count() << std::endl;
		std::cout << "finish=" << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
#endif
		/**
		 * 
		 * @return 
		 */
		if (result.size() != data.size()) {
#ifdef __PRINT__
			std::cout << "fail(size " << result.size() << "!=" << data.size() << ")" << std::endl;
#endif
			n_fail++;
		}
	}
	auto end = std::chrono::steady_clock::now();
	return Result(
		float(float(TEST_SIZE - n_fail) / float(TEST_SIZE)),
		time_t(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count())
		);
}

/**
 * 
 */
time_t process2(ListBuffer& data, ListDensity& density, uint32_t framesize, uint32_t redundancy) {
	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < TEST_SIZE; ++i) {
		SSCodeEngine e(framesize, data.size(), data.size() + redundancy, data.size() + redundancy, density);
		auto coded = e.Encode(data);
		auto result = e.Decode(coded);
		if (result.size() != data.size()) {
			return 0;
		}
	}
	auto end = std::chrono::steady_clock::now();
	return time_t(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}

/**
 * 
 */
time_t process3(ListBuffer& data, uint32_t code_size, uint32_t framesize, uint32_t redundancy) {
	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < TEST_SIZE; ++i) {
		SSCodeEngine e(
			framesize,
			data.size(),
			data.size() + redundancy,
			data.size() + redundancy,
			SSCodeEngine::GetDensityReference(code_size)
			);
		auto coded = e.Encode(data);
		auto result = e.Decode(coded);
		if (result.size() != data.size()) {
			return 0;
		}
	}
	auto end = std::chrono::steady_clock::now();
	return time_t(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}

/**
 */
int test1() {
	ListBuffer data;
	Buffer frame;
	/**/
	std::ostream& os = std::cout;
	/**/
	os << "density; field; redundancy; probability; time" << std::endl;
	/**/
	for (int i = 0; i < CODE_SIZE; ++i) {
		data.push_back(frame);
	}
	/**/
	ListDensity density = {
		{1, 1},
		{1, 1},
		{1, 1},
		{1, 1},
		{1, 1},
		{1, 1},
		{1, 1},
		{1, 1},
		{1, 1},
		{1, 1}
	};
	for (int d = 8; d > 0; --d) {
		for (int i = 0; i < density.size(); ++i) {
			density[i].first = FIELD_SIZE;
			density[i].second = (1 << d) - 1;
		}
		for (int f = (int) density.size() - 1; f > 0; --f) {
			density[f].first = 1;
			/**/
			for (int r = MAX_REDUNDANCY; r > 0; --r) {
				/**/
				auto res = process(data, density, frame.size(), r);
				/**/
				os << (1 << d) - 1 << "; " << f << "; " << r << "; " << res.prob << "; " << res.time << std::endl;
			}
		}
	}
	return 0;
}

/**
 * 
 * @return 
 */
int test2() {
	ListBuffer data;
	Buffer frame;
	/**/
	std::ostream& os = std::cout;
	/**/
	os << "size; n; field; density; redundancy; time" << std::endl;

	/**/
	for (int s = MIN_CODE_SIZE; s <= MAX_CODE_SIZE; ++s) {
		/**/
		data.clear();
		for (int i = 0; i < s; ++i) {
			data.push_back(frame);
		}
		/**/
		for (int r = MIN_REDUNDANCY; r <= MAX_REDUNDANCY; ++r) {
			/**/
			ListDensity density = {
				{1, 1},
				{1, 1},
				{1, 1},
				{1, 1},
				{1, 1},
				{1, 1},
				{1, 1},
				{1, 1},
				{1, 1},
				{1, 1}
			};
			for (int n = MIN_DENSITY_SIZE; n <= MAX_DENSITY_SIZE; ++n) {
				/***/
				density[n].first = MAX_FIELD_SIZE;
				/***/
//				for (int f = MIN_FIELD_SIZE; f <= MAX_FIELD_SIZE; f = ((f << 1) | 1)) {
				for (int f = MIN_FIELD_SIZE; f <= MAX_FIELD_SIZE; f += (MAX_FIELD_SIZE - MIN_FIELD_SIZE)) {
					/**/
					density.front().first = f;
					/**/
					for (int d = 1; d <= UINT8_MAX; ++d) {
						/**/
						for (int i = 0; i < density.size(); ++i) {
							density[i].second = d;
						}

						/**/
						auto t = process2(data, density, frame.size(), r);
						/**/
						if (t) {
							os << s << "; " << n << "; " << f << "; " << d << "; " << r << "; " << t << std::endl;
							/**/
							f = MAX_FIELD_SIZE;
							r = MAX_REDUNDANCY;
							d = UINT8_MAX;
							n = MAX_DENSITY_SIZE;
						}
					}
				}
			}
		}
	}
	return 0;
}

/**
 * 
 * @return 
 */
Buffer BufferRandom(int size) {
	Buffer buf;
	buf.reserve(size);
	for (int i = 0; i < size; ++i) {
		buf.push_back(Buffer::value_type(rand()));
	}
	return buf;
}

int test3() {
	ListBuffer data;
	/**/
	std::ostream& os = std::cout;
	/**/
	os << "file; size; redundancy; time" << std::endl;
	/**/
	for (int s = 10000; s < MAX_FILE_SIZE; s += 10000) {
		/**/
		for (int n = 2; n < MAX_CODE_SIZE; ++n) {
			/**/
			data.clear();
			for (int i = 0; i < n; ++i) {
				data.push_back(BufferRandom(float(s + 1) / float(n)));
			}
			/**/
			for (int r = 1; r < MAX_REDUNDANCY; ++r) {
				/**/
				auto t = process3(data, n, data[0].size(), r);
				/**/
				if (t) {
					os << s << "; " << n << "; " << r << "; " << t << std::endl;
					/**/
					r = MAX_REDUNDANCY;
				}
			}
		}
	}
	return 0;
}

/**
 */
int main() {
	test3();
	return 0;
}
