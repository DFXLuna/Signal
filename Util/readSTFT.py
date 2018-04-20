import librosa
import numpy as np
import sys

data = np.loadtxt( sys.argv[1] )
wav = librosa.core.istft( data )

librosa.output.write_wav( sys.argv[2], wav, 48000 )