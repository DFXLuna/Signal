import librosa
import librosa.display
import matplotlib.pyplot as plt
import numpy as np
import sys

# 1. Get the file path to the included audio example
filename = "77.78_sin.wav"

# 2. Load the audio as a waveform `y`
#    Store the sampling rate as `sr`
y, sr = librosa.load(filename, sr=None)

# Compute chroma features from the harmonic signal
data = np.abs(librosa.feature.chroma_stft(y=y, sr=sr))
librosa.display.specshow( data, y_axis='chroma' )
plt.colorbar()
plt.title('Chromagram')
plt.show()
# y_hat = librosa.core.istft( data )
# librosa.output.write_wav( "ChromaOut.wav", y_hat, sr = sr)