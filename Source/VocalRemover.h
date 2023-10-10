#pragma once

#include "JuceHeader.h"

class VocalRemover
{
public:
	void prepare(juce::dsp::ProcessSpec spec)
	{
		processSpec.maximumBlockSize = spec.maximumBlockSize;
		processSpec.numChannels = spec.numChannels;
		processSpec.sampleRate = spec.sampleRate;

		//prepare and initialise filters
		bandpassFilter.prepare(processSpec);
		bandpassFilter.get<lowCut>().setType(juce::dsp::LinkwitzRileyFilterType::highpass);	//set filter type
		bandpassFilter.get<lowCut>().setCutoffFrequency(50.f);								//set cut off frequency

		bandpassFilter.get<highCut>().setType(juce::dsp::LinkwitzRileyFilterType::lowpass);	//set filter type
		bandpassFilter.get<highCut>().setCutoffFrequency(20000.f);							//set cut off frequency


	}

	void setLowCutFrequency(float lowCutFreq)
	{
		bandpassFilter.get<lowCut>().setCutoffFrequency(lowCutFreq);
	}

	void setHighCutFrequency(float highCutFreq)
	{
		bandpassFilter.get<highCut>().setCutoffFrequency(highCutFreq);
	}

	void process(juce::AudioBuffer<float> buffer)
	{
		//process incoming audio data if channel setup is stereo, otherwise return
		if ((buffer.getNumChannels() != numRequiredChannels) || isBypassed)
			return;

		//create a temporary buffer to store and process the data
		juce::AudioBuffer<float> tempBuffer;
		tempBuffer.setSize(numRequiredChannels, buffer.getNumSamples());
		
		//copy samples to tempBuffer
		for (int channel = 0; channel < numRequiredChannels; ++channel)
		{
			for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
			{
				float sampleToCopy = -1.f * buffer.getSample(channel, sample);			
				tempBuffer.setSample(1 - channel, sample, sampleToCopy);             
			}
		}

		juce::dsp::AudioBlock<float> audioBlock(tempBuffer);
		juce::dsp::ProcessContextReplacing<float> context(audioBlock);

		bandpassFilter.process(context);
		
		for (int channel = 0; channel < numRequiredChannels; ++channel)
			buffer.addFrom(channel, 0, tempBuffer.getReadPointer(channel), buffer.getNumSamples());
		
		
	}

	void setBypassed(bool bypass)
	{
		isBypassed = bypass;
	}

private:
	
	using filter = juce::dsp::LinkwitzRileyFilter<float>;
	enum processors {lowCut,highCut};
	juce::dsp::ProcessorChain<filter,filter> bandpassFilter;

	juce::dsp::ProcessSpec processSpec;
	
	 
	const int numRequiredChannels = 2;
	bool isBypassed = true;
};
