import librosa
import librosa.display
import matplotlib.pyplot as plt
import numpy as np
import sys

# 1. Get the file path to the included audio example
filename = "./freq/Harm5.wav"

# 2. Load the audio as a waveform `y`
#    Store the sampling rate as `sr`
y, sr = librosa.load(filename, sr=None)
data = librosa.core.stft( y )

print( "min: " + str( np.abs( np.min( data ) ) ) )
print( "max: " + str( np.abs( np.max( data ) ) ) )
# Compute chroma features from the harmonic signal
# data = np.abs(librosa.feature.chroma_stft(y=y, sr=sr))
# librosa.display.specshow( data, y_axis='chroma' )
# plt.colorbar()
# plt.title('Chromagram')
# plt.show()
# y_hat = librosa.core.istft( data )
# librosa.output.write_wav( "ChromaOut.wav", y_hat, sr = sr)