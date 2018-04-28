import librosa
import numpy as np
import sys

filedata = np.loadtxt( sys.argv[1] )
# reconstruct imaginary components
# imag[i,j] is stored at filedata[i, j+376]
data = np.empty( [1025, 376], np.complex64 )
for i in range( 0, 1025):
    for j in range( 0, 376 ):
        data[i,j] = filedata[i,j] + ( filedata[i,j+376] *1j )

wav = librosa.core.istft( data )
librosa.output.write_wav( sys.argv[2], wav, 48000 )
