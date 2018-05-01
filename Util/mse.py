import sys
import numpy as np

filedata1 = np.loadtxt( sys.argv[1] )
# reconstruct imaginary components
# imag[i,j] is stored at filedata[i, j+376]
data1 = np.empty( [1025, 376], np.complex64 )
for i in range( 0, 1025):
    for j in range( 0, 376 ):
        data1[i,j] = filedata1[i,j] + ( filedata1[i,j+376] *1j )

filedata2 = np.loadtxt( sys.argv[2] )
data2 = np.empty( [1025, 376], np.complex64 )
for i in range( 0, 1025):
    for j in range( 0, 376 ):
        data2[i,j] = filedata2[i,j] + ( filedata2[i,j+376] *1j )

print("MSE: " + str(np.abs((data1 - data2) ** 2).mean(axis=None)))