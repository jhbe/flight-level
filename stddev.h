#ifndef STDDEV_H
#define STDDEV_H

/**
 * This class calculates the standard deviation of a set of provided numbers.
 *
 * Numbers are provided one at a time using the Put function. The Get function
 * calculates the standard deviation over the last NUM_SAMPLE provided number.
 * If less then NUM_SAMPLE numbers have been provided Get will return false
 * with no standard deviation calculated.
 */
class StdDev {
public:
	StdDev(int size);
	~StdDev();

	void Reset(void);
	void Put(float value);

	bool Valid();
	float Get();

public:
	int m_size;
	int m_numSamples;
	int m_nextSample;
	float *m_samples;
};

#endif
