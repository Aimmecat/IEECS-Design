import lib601.sf as sf
import lib601.sig as sig
import lib601.ts as ts
import lib601.optimize as optimize
import operator
# 6.01 HomeWork 2 Skeleton File

#Constants relating to some properties of the motor
k_m = 250
k_b = 0.48
k_s = 3
r_m = 4.5


def controllerAndSensorModel(k_c):
    return sf.Cascade(sf.Gain(k_c * k_s),sf.Gain(1))

def integrator(T):
    return sf.Cascade(sf.Cascade(sf.R(),sf.Gain(T)),sf.FeedbackAdd(sf.Gain(1),sf.R()))

def motorModel(T):
    return sf.FeedbackSubtract(sf.Cascade(sf.Cascade(sf.Gain(1.0/r_m),sf.Gain(k_m)),integrator(T)),sf.Gain(k_b))

def plantModel(T):
    return sf.Cascade(motorModel(T),integrator(T))

def lightTrackerModel(T,k_c):
    return sf.FeedbackSubtract(sf.Cascade(controllerAndSensorModel(k_c),plantModel(T)),sf.Gain(1))

def plotOutput(sfModel):
    """Plot the output of the given SF, with a unit-step signal as input"""
    smModel = sfModel.differenceEquation().stateMachine()
    outSig = ts.TransducedSignal(sig.StepSignal(), smModel)
    outSig.plot()

def bestk(T,kMin,kMax,numSetps):
    def search(k_c):
        return abs(lightTrackerModel(T,k_c).dominantPole())
    return optimize.optOverLine(search,kMin,kMax,numSetps)




