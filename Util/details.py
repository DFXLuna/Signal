import librosa
import sys
import dataSize

y, sr = librosa.load(sys.argv[1], sr=None)
#data = np.abs( librosa.core.stft(y) )
print("duration: " + str(librosa.core.get_duration(y, sr = sr)))
print("sampling rate: " + str(sr))
y = librosa.core.stft( y )
dataSize.printDataSize(y)