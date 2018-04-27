import sys
import librosa
import numpy as np

y, sr = librosa.core.load( sys.argv[1], sr = None )
stft = librosa.core.stft( y )
np.savetxt( sys.argv[2], stft.view( np.float64 ) )