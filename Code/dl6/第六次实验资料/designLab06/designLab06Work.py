import lib601.sf as sf
import lib601.optimize as optimize
import operator

def delayPlusPropModel(k1 , k2):
    T = 0.1
    V = 0.1
    
    # Controller:  your code here
    controller = sf.FeedforwardAdd(sf.Gain(k1),sf.Cascade(sf.R(),sf.Gain(k2)))
    # The plant is like the one for the proportional controller.  Use
    # your definition from last week.
    plant1 = sf.Cascade(sf.Cascade(sf.R(),sf.Gain(T)),sf.FeedbackAdd(sf.Gain(1),sf.R()))
    plant2 = sf.Cascade(sf.Cascade(sf.R(),sf.Gain(V*T)),sf.FeedbackAdd(sf.Gain(1),sf.R()))
    # Combine the three parts
    sys = sf.FeedbackSubtract(sf.Cascade(controller,sf.Cascade(plant1,plant2)),sf.Gain(1))
    return sys


def testbestx(xMin,xMax,numSteps):
    def search1(x):
        return x*x-x
    def search2(x):
        return x*x*x*x*x-7*x*x*x+6*x*x+2
    return optimize.optOverLine(search2,xMin,xMax,numSteps)

# You might want to define, and then use this function to find a good
# value for k2.

# Given k1, return the value of k2 for which the system converges most
# quickly, within the range k2Min, k2Max.  Should call optimize.optOverLine.


def bestk2(k1, k2Min, k2Max, numSteps):
    def search2(k2):
        return abs(delayPlusPropModel(k1,k2).dominantPole())
    return optimize.optOverLine(search2,k2Min,k2Max,numSteps)


def anglePlusPropModel(k3, k4):
    T = 0.1
    V = 0.1

    # plant 1 is as before
    plant1 = sf.Cascade(sf.Gain(k3),sf.FeedbackSubtract(sf.Cascade(sf.Cascade(sf.R(),sf.Gain(T)),sf.FeedbackAdd(sf.Gain(1),sf.R())),sf.Gain(k4)))
    # plant2 is as before
    plant2 =  sf.Cascade(sf.Cascade(sf.R(),sf.Gain(V*T)),sf.FeedbackAdd(sf.Gain(1),sf.R()))
    # The complete system
    sys = sf.FeedbackSubtract(sf.Cascade(plant1,plant2),sf.Gain(1))
    return sys


# Given k3, return the value of k4 for which the system converges most
# quickly, within the range k4Min, k4Max.  Should call optimize.optOverLine.


def bestk4(k3, k4Min, k4Max, numSteps):
    def search4(k4):
        return abs(anglePlusPropModel(k3,k4).dominantPole())
    return optimize.optOverLine(search4,k4Min,k4Max,numSteps)

