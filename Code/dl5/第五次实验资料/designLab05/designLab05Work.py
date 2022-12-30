import lib601.sig as sig
import lib601.ts as ts
import lib601.poly as poly
import lib601.sf as sf
import lib601.optimize as optimize
def controller(k):
   return sf.Gain(k)
   
def plant1(T):
   return sf.Cascade(sf.Cascade(sf.R(),sf.Gain(T)),sf.FeedbackAdd(sf.Gain(1),sf.R()))

def plant2(T, V):
   return sf.Cascade(sf.Cascade(sf.R(),sf.Gain(V*T)),sf.FeedbackAdd(sf.Gain(1),sf.R()))

def wallFollowerModel(k, T, V):
   return sf.FeedbackSubtract(sf.Cascade(controller(k),sf.Cascade(plant1(T),plant2(T,V))),sf.Gain(1))

def bestk(T,V,kMin, kMax, numSteps):
    def search(k):
        return abs(wallFollowerModel(k,T,V).dominantPole())
    return optimize.optOverLine(search,kMin,kMax,numSteps)


