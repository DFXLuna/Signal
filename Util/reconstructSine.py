import numpy as np
import wave
import struct
import matplotlib.pyplot as plt

frame_rate = 48000.0
infile = "77.78_sin.wav"
numSamples = 48000 #1 second of audio
wav_file = wave.open(infile, 'r')
data = wav_file.readframes(numSamples)
wav_file.close()

data = struct.unpack('{n}h'.format(n = numSamples), data)
data = np.array(data)
data_fft = np.fft.fft(data)
data_ifft = np.fft.ifft( data_fft )

# write to file
comptype = "NONE"
compname = "not compressed"
numChannels = 1
sampwidth = 2
amplitude = 1

outfile = "77.78_reconstruct_sin.wav"

wav_file = wave.open( outfile, 'w' )
wav_file.setparams( ( numChannels, sampwidth, int(frame_rate), numSamples, comptype, compname ) )

for i in range( 0, 10 ):
    for s in data_ifft:
        wav_file.writeframes( struct.pack('h', int(s * amplitude) ) )