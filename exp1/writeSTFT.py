import sys
import librosa
import librosa.display
import dataSize
import numpy as np
import matplotlib.pyplot as plt

y, sr = librosa.load(sys.argv[1], sr=None)
data = np.abs( librosa.core.stft(y) )
np.savetxt( "./stft/harm5.stft", data )