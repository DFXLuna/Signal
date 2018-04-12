import numpy as np
import wave
import struct
import matplotlib.pyplot as plt

frame_rate = 48000.0
infile = "41.2_sin.wav"
numSamples = 48000 #1 second of audio
wav_file = wave.open(infile, 'r')
data = wav_file.readframes(numSamples)
wav_file.close()

data = struct.unpack('{n}h'.format(n = numSamples), data)
data = np.array(data)
data_fft = np.abs(np.fft.fft(data))

# np.savetxt("harm1.txt", data_fft)
print("The frequency is {} Hz".format(np.argmax(data_fft)))
