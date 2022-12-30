import os
labPath = os.getcwd()
from sys import path
if not labPath in path:
    path.append(labPath)
print 'setting labPath to', labPath

import math
import lib601.util as util
import lib601.sm as sm
import lib601.gfx as gfx
from soar.io import io

# Remember to change the import in dynamicMoveToPointSkeleton in order
# to use it from inside soar
import dynamicMoveToPointSkeleton
reload(dynamicMoveToPointSkeleton)
my_dyn = dynamicMoveToPointSkeleton.DynamicMoveToPoint()

import ffSkeleton
reload(ffSkeleton)


from secretMessage import secret
my_ffs = ffSkeleton.FollowFigure(secret)
# Set to True for verbose output on every step
verbose = False

# Rotated square points
squarePoints = [util.Point(0.5, 0.5), util.Point(0.0, 1.0),
                util.Point(-0.5, 0.5), util.Point(0.0, 0.0)]

class GoalGenerator(sm.SM):
    def getNextValues(self, state, inp):
        return util.Point(-1.0,-0.5),util.Point(-1.0,-0.5)

class Avoid_Pedestrians(sm.SM):
    startState = 0
    def getNextValues(self, state, inp):
        return (state,io.Action())
    
def Avoid(inp):
    if min(inp.sonars[0:8]) < 0.3:
        return True
    return False
        
my_avoid = Avoid_Pedestrians()

# Put your answer to step 1 here
mySM = sm.Switch(Avoid, my_avoid, sm.Cascade(sm.Parallel(my_ffs,sm.Wire()),my_dyn))

######################################################################
###
###          Brain methods
###
######################################################################

def setup():
    robot.gfx = gfx.RobotGraphics(drawSlimeTrail = True)
    robot.behavior = mySM

def brainStart():
    robot.behavior.start(traceTasks = robot.gfx.tasks(),
                         verbose = verbose)

def step():
    robot.behavior.step(io.SensorInput()).execute()
    io.done(robot.behavior.isDone())

def brainStop():
    pass

def shutdown():
    pass
