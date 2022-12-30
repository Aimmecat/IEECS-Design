# -*- coding: cp936 -*-
import lib601.sm as sm
import lib601.util as util
import math

# Use this line for running in idle
##import lib601.io as io
# Use this line for testing in soar
from soar.io import io

class DynamicMoveToPoint(sm.SM):
    rotationalGain = 1.0
    forwardGain = 1.0
    dispEps = 0.01
    angleEps = 0.01
    startState = 'Prepare'
    #state:设定角度，当前角度，设定距离，当前距离，状态标志
    def __init__(self):
        self.fvel = 0
        self.rvel = 0
##    def getNextValues(self, state, inp):
##        currentTheta = inp[1].odometry.theta
##        currentPoint = inp[1].odometry.point()
##        targetPoint = inp[0]
##        thetaDesired = \
##                             util.fixAnglePlusMinusPi(currentPoint.angleTo(targetPoint))
##        distDesired = currentPoint.distance(targetPoint)
####        self.rvel = self.rotationalGains * \
####                           util.fixAnglePlusMinusPi(thetaDesired - currentTheta)
##        print util.fixAnglePlusMinusPi(thetaDesired - currentTheta)
##        return (state,  io.Action(fvel = self.forwardGain*distDesired,rvel = util.fixAnglePlusMinusPi(thetaDesired - currentTheta)))
    def getNextValues(self, state, inp):
        currentTheta = inp[1].odometry.theta
        currentPos = inp[1].odometry.point()
        if state == 'Prepare':
            thetaDesired = \
                             util.fixAnglePlusMinusPi(currentPos.angleTo(inp[0]))
            startPos = currentPos
            self.distDesired = startPos.distance(inp[0])
            print thetaDesired
            print self.distDesired
        else:
            (thetaDesired,thetaLast,startPos, lastPos) = state
        newState = (thetaDesired, currentTheta,startPos, currentPos)

        self.rvel = self.rotationalGain *\
                           util.fixAnglePlusMinusPi(thetaDesired - currentTheta)
        
        self.fvel = self.forwardGain * \
                            self.distDesired - startPos.distance(currentPos)
            
##        print 'DynamicMoveToPoint', 'state=', state, 'inp=', inp

        if abs(self.rvel) > 1e-2:
            return (newState,  io.Action(rvel = self.rvel))
        elif abs(self.rvel) < 1e-2 and abs(self.fvel) > 1e-2:
            return (newState,  io.Action(fvel = self.fvel))
        else:
            newState = 'Prepare'
            return (newState,  io.Action())
    
