import matplotlib.pyplot as plt
import numpy as np
import sys

data = np.loadtxt( sys.argv[1] )
plt.plot( data )
plt.ylabel("Fitness(-1 * mean squared error)")
plt.xlabel("Generations")
plt.show()