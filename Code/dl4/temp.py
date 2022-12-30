import lib601.sm as sm

def accumulator(init):
    return sm.ParallelAdd(sm.Wire(),sm.FeedbackAdd(sm.R(0),sm.Gain(1))).transduce(init)

def accumulatorDelay(init):
    return sm.FeedbackAdd(sm.R(0),sm.Gain(1)).transduce(init)

def accumulatorDelayScaled(s,init):
    return sm.Cascade(sm.Gain(s),sm.FeedbackAdd(sm.R(0),sm.Gain(1))).transduce(init)

def plant(T, initD):
    return sm.Cascade(sm.Cascade(sm.Gain(-T),sm.R(0)),sm.FeedbackAdd(sm.Wire(),sm.R(initD)))

def controller(k):
    return sm.Gain(k)

def sensor(initD):
    return sm.R(initD)

def wallFinderSystem(T, initD, k):
    return sm.FeedbackSubtract(sm.Cascade(controller(k),plant(T,initD)),sensor(initD))

new = wallFinderSystem(0.1,1.5,-1)
new.transduce([0.7,0.7,0.7,0.7,0.7,0.7,0.7,0.7,0.7,0.7,0.7,0.7,0.7],verbose = True)
