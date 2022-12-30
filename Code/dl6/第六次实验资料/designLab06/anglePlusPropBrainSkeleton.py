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
# No additional delay.
# Output is a sequence of (distance, angle) pairs
class Sensor(sm.SM):
   def getNextValues(self, state, inp):
       v = sonarDist.getDistanceRightAndAngle(inp.sonars)
       print 'Dist from robot center to wall on right', v[0]
       if not v[1]:
           print '******  Angle reading not valid  ******'
       return (state, v)


# inp is a tuple (distanceRight, angle)
class WallFollower(sm.SM):
   # state: angle_last do_last
    startState = (0.5,0.4)
    k3 = 30
    k4 = 3.464
    def getNextValues(self, state, inp):
      dis_now = state[0] + math.sin(state[1])*forwardVelocity*T
      error = desiredRight - dis_now
      v_r = self.k3 * error - self.k4 * state[1]
      if not inp[1]:
         newstate = (inp[0],state[1])
      else:
         newstate = inp
      return (newstate,io.Action(fvel = forwardVelocity,rvel = v_r))
      
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
                                      'output', lambda x:x[0]))
    robot.behavior = mySM
    robot.behavior.start(traceTasks = robot.gfx.tasks())

def step():
    robot.behavior.step(io.SensorInput()).execute()

def brainStop():
    pass
