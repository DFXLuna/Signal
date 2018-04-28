import sys
import librosa
import numpy as np

y, sr = librosa.core.load( sys.argv[1], sr = None )
stft = librosa.core.stft( y )
# yo check this wack shit
out = np.empty( [stft.shape[0], stft.shape[1] * 2] )
for i in range( 0, stft.shape[0]):
    for j in range( 0, stft.shape[1] ):
        out[i,j] = np.real( stft[i,j] )
        out[i,j+stft.shape[1]] = np.imag( stft[i,j] )
np.savetxt( sys.argv[2], out )