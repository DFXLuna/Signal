import numpy as np
import wave
import struct
import matplotlib.pyplot as plt

# Create sine wave
freq = 82.41
numSamples = 48000 * 4

samplingRate = 48000.0 # Also the frame rate
amplitude = 16000

file = str(freq) + "_sin.wav"

sine_wave = [ np.sin( 2 * np.pi* freq * ( x / samplingRate ) ) for x in range( numSamples ) ]

# write to file
comptype = "NONE"
compname = "not compressed"
numChannels = 1
sampwidth = 2

wav_file = wave.open( file, 'w' )
wav_file.setparams( ( numChannels, sampwidth, int(samplingRate), numSamples, comptype, compname ) )

for s in sine_wave:
    wav_file.writeframes( struct.pack('h', int(s * amplitude) ) )