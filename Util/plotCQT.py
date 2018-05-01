import librosa
import librosa.display
import matplotlib.pyplot as plt
import numpy as np
import sys

filename = sys.argv[1]
y, sr = librosa.load(filename, sr=None)
CQT = librosa.feature.chroma_cqt(y=y, sr=sr)
STFT = librosa.feature.chroma_stft(y=y, sr=sr,n_fft=4096)

plt.figure()
plt.subplot(2,1,1)
librosa.display.specshow(STFT, y_axis='chroma', x_axis='time')
plt.title('CQT Chromagram')
plt.colorbar()
plt.subplot(2,1,2)
librosa.display.waveplot(y=y, sr=sr)
plt.title('waveform')
plt.tight_layout()
plt.show()
