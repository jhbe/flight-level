#include <math.h>
#include <stdlib.h>
#include "stddev.h"

StdDev::StdDev(int size) {
	m_size = size;
	m_samples = (float *)malloc(sizeof (float) * m_size);
	Reset();
}

StdDev::~StdDev() {
	free((void *)m_samples);
	m_samples = 0;
	m_size = 0;
}

void StdDev::Reset() {
	m_numSamples = 0;
	m_nextSample = 0;
}

void StdDev::Put(float value) {
	m_samples[m_nextSample] = value;

	m_nextSample++;
	if (m_nextSample >= m_size) {
		m_nextSample = 0;
	}

	if (m_numSamples < m_size) {
		m_numSamples++;
	}
}

bool StdDev::Valid(void) {
	return m_numSamples >= m_size;
}

float StdDev::Get() {
	if (m_numSamples < m_size) {
		return 1000.0;
	}
	float average = 0;
	for (int i = 0; i < m_numSamples; i++) {
		average += m_samples[i];
	}
	average /= (float)m_numSamples;

	float stddev = 0;
	for (int i = 0; i < m_numSamples; i++) {
		float a = m_samples[i] - average;
		stddev += a*a;
	}

	return sqrt(stddev / float(m_numSamples - 1));
}
