"""
Class and some supporting functions for representing and manipulating system functions. 
"""

import math
import lib601.poly as poly
import lib601.util as util


class SystemFunction:
    def __init__(self, numeratorPoly, denominatorPoly):
        self.numeratorPoly = numeratorPoly
        self.denominatorPoly = denominatorPoly

    def poles(self):
        polescoeffs = self.denominatorPoly.coeffs[:]
        polesroots = poly.Polynomial(list(reversed(polescoeffs))).roots()    
        return polesroots

    def poleMagnitudes(self):
        poleMagnitudeslist = []
        for index in self.poles():
            poleMagnitudeslist.append(abs(index))
        return poleMagnitudeslist
    
    def dominantPole(self):
        return util.argmax(self.poles(),abs)

    def __str__(self):
        return 'SF(' + self.numeratorPoly.__str__('R') + \
               '/' + self.denominatorPoly.__str__('R') + ')'

    __repr__ = __str__

s1 = SystemFunction(poly.Polynomial([1]),poly.Polynomial([0.63,-1.6,1]))
s2 = SystemFunction(poly.Polynomial([1]),poly.Polynomial([1.1,-1.9,1]))

def Cascade(sf1, sf2):
    return SystemFunction(sf1.numeratorPoly*sf2.numeratorPoly,sf1.denominatorPoly*sf2.denominatorPoly)
    

def FeedbackSubtract(sf1, sf2=None):
    numeratorPoly = sf1.numeratorPoly * sf2.denominatorPoly
    denominatorPoly = sf1.denominatorPoly * sf2.denominatorPoly + sf1.numeratorPoly * sf2.numeratorPoly
    return SystemFunction(numeratorPoly,denominatorPoly)

