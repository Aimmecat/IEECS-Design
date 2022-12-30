import math
import lib601.sm as sm
from soar.io import io
import lib601.gfx as gfx
import lib601.util as util
import lib601.sonarDist as sonarDist

######################################################################
#
#            Brain SM
#
######################################################################

desiredRight = 0.4
forwardVelocity = 0.1
T = 0.1

class Sensor(sm.SM):
    def getNextValues(self, state, inp):
        v = sonarDist.getDistanceRight(inp.sonars)
        print 'Dist from robot center to wall on right', v
        return (state, v)

# inp is the distance to the right
class WallFollower(sm.SM):
    startState = (0.4,0,0.5,-0.1)
    k1 = 30
    k2 = -27.771
    def getNextValues(self, state, inp):
        dis_now = state[2] + T * forwardVelocity * math.sin(state[0])
        angle_now = state[0] + state[1] * T
        error = desiredRight - dis_now
        vr_now = self.k1 * error + self.k2 * state[3]
        newstate = (angle_now,vr_now,inp,error)
        return (newstate,io.Action(fvel = forwardVelocity,rvel = vr_now))


sensorMachine = Sensor()
sensorMachine.name = 'sensor'
mySM = sm.Cascade(sensorMachine, WallFollower())

######################################################################
#
#            Running the robot
#
######################################################################

def setup():
    robot.gfx = gfx.RobotGraphics(drawSlimeTrail=False)
    robot.gfx.addStaticPlotSMProbe(y=('rightDistance', 'sensor',
                                      'output', lambda x:x))
    robot.behavior = mySM
    robot.behavior.start(traceTasks = robot.gfx.tasks())

def step():
    robot.behavior.step(io.SensorInput()).execute()
    io.done(robot.behavior.isDone())

def brainStop():
    pass
