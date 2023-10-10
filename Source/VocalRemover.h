#pragma once

#include "JuceHeader.h"

class VocalRemover
{
public:
	void process(juce::AudioBuffer<float> buffer)
	{
		if ((buffer.getNumChannels() != numRequiredChannels) || isBypassed)
			return;

		juce::AudioBuffer<float> tempBuffer;
		tempBuffer.setSize(numRequiredChannels, buffer.getNumSamples());
		
		for (int channel = 0; channel < numRequiredChannels; ++channel)
		{
			for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
			{
				float sampleToCopy = -1.f * buffer.getSample(channel, sample);
				tempBuffer.setSample(1 - channel, sample, sampleToCopy);
			}
		}

		for (int channel = 0; channel < numRequiredChannels; ++channel)
			buffer.addFrom(channel, 0, tempBuffer.getReadPointer(channel), buffer.getNumSamples());
		
		
	}

	void setBypassed(bool bypass)
	{
		isBypassed = bypass;
	}

private:
	const int numRequiredChannels = 2;
	bool isBypassed = true;
};
