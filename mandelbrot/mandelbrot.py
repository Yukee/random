# -*- coding: utf-8 -*-
"""
Created on Thu Oct 24 20:07:24 2013

@author: nicolas
"""

from random import uniform
import numpy as np
from matplotlib.pyplot import *


xmin = -2.
xmax = 0.5
ymin = -1.
ymax = 1.

Ntri = 200000
Ncv = 500
tol = 2.

x_bin = []
y_bin = []
for tri in range(Ntri):
    c = uniform(xmin, xmax) + uniform(ymin, ymax)*1J
    z = 0
    for it in range(Ncv):
        z = z*z + c
        if abs(z) > tol: break
    if abs(z) < tol:
        x_bin.append(float(np.real(c)))
        y_bin.append(float(np.imag(c)))

print(len(x_bin))
hexbin(x_bin,y_bin, gridsize=200)
axis([xmin,xmax,ymin,ymax])
title("Complex plane, Mandelbrot")
show()