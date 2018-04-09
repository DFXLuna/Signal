import numpy as np
import wave
import struct
import matplotlib.pyplot as plt

# Create sine wave
freq = 82.41
numSamples = 48000 * 4

samplingRate = 48000.0
amplitude = 8000
harmonic = ( 5 ) + 1 #harmonic is 1 + the desired number of harmonic

file = "./freq/Harm" + str(harmonic - 1) + ".wav"
# create fundamental
sine_wave = [ np.sin( 2 * np.pi* freq * x / samplingRate ) for x in range( numSamples ) ]
sine_wave = np.array(sine_wave)

# create harmonic
harm = np.array( [ np.sin( 2 * np.pi* freq * x * harmonic / samplingRate ) for x in range( numSamples ) ] )
sine_wave += harm   

# write to file
comptype = "NONE"
compname = "not compressed"
numChannels = 1
sampwidth = 2

wav_file = wave.open( file, 'w' )
wav_file.setparams( ( numChannels, sampwidth, int(samplingRate), numSamples, comptype, compname ) )

for s in sine_wave:
    wav_file.writeframes( struct.pack('h', int(s * amplitude) ) )