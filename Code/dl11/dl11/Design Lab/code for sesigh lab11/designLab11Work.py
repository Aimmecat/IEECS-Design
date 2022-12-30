import lib601.dist as dist
import lib601.coloredHall as coloredHall
import lib601.util as util
from lib601.coloredHall import *
import math as m

standardHallway = ['white', 'white', 'green', 'white', 'white']
alternating = ['white', 'green'] * 6
sterile = ['white'] * 16
testHallway = ['chocolate', 'white', 'green', 'white', 'white',
               'green', 'green', 'white',  
               'green', 'white', 'green', 'chocolate']
possibleColors = ['black', 'white', 'red', 'green', 'blue']
maxAction = 5
actions = [str(x) for x in range(maxAction) + [-x for x in range(1, maxAction)]]

def makePerfect(hallway = standardHallway):
    return makeSim(hallway, actions, perfectObsNoiseModel,
                   standardDynamics, perfectTransNoiseModel,'perfect')

def makeNoisy(hallway = standardHallway):
    return  makeSim(hallway, actions, noisyObsNoiseModel, standardDynamics,
                    noisyTransNoiseModel, 'noisy')

def makeNoisyKnownInitLoc(initLoc, hallway = standardHallway):
    return  makeSim(hallway, actions, noisyObsNoiseModel, standardDynamics,
                    noisyTransNoiseModel, 'known init',
                    initialDist = dist.DDist({initLoc: 1}))
#11.1.1
def whiteEqGreenObsDist(actualColor):
    if actualColor in ['green','white']:
        return dist.DDist({'green':0.5,'white':0.5})
    else:
        return dist.DDist({actualColor:1})

def whiteVsGreenObsDist(actualColor):
    if actualColot == 'green':
        return dist.DDist({'white':1})
    elif actualColot == 'while':
        return dist.DDist({'green':1})
    else:
        return dist.DDist({actualColor:1})

def noisyObs(actualColor):
    Color = possibleColors[:]
    Color_dict = {}
    for element in Color:
        if not element == actualColor:
            Color_dict[element] = 0.2 / (len(Color)-1)
        else:
            Color_dict[element] = 0.8
    return dist.DDist(Color_dict)

##noisyObsModel = makeObservationModel(standardHallway,noisyObs)
##
##w = makeSim(testHallway, actions,
##            whiteEqGreenObsDist,
##            standardDynamics, perfectTransNoiseModel)
##w.run(50)

#11.1.2
def incrDictEntry(d, k, v):
    if d.haskey(k):
        d[k] += v
    else:
        d[k] = v

def standardDynamics(loc, act, hallwayLength):
    return util.clip(loc + act, 0, hallwayLength-1)

def ringDynamics(loc, act, hallwayLength):
    newloc = loc + act
    if 0 <= newloc <= hallwayLength - 1:
        return newloc
    elif newloc < 0:
        return hallwayLength + newloc
    elif newloc > hallwayLength - 1:
        return newloc - hallwayLength - 1

def leftSlipTrans(nominalLoc, hallwayLength):
    if nominalLoc == 0:
        return dist.DDist({nominalLoc: 1.0})
    else:
        return dist.DDist({nominalLoc : 0.9,nominalLoc - 1 : 0.1})

def noisyTrans(nominalLoc, hallwayLength):
    if nominalLoc in [0,hallwayLength-1]:
        return dist.DDist({nominalLoc: 1.0})
    else:
        return dist.DDist({nominalLoc : 0.8,nominalLoc - 1 : 0.1,nominalLoc + 1 : 0.1})

##noisyTransModel = makeTransitionModel(standardDynamics,noisyTrans,5)

##w = makeNoisyKnownInitLoc(7, sterile)
##w.run(50)



#11.6
def sonarHit(distance, sonarPose, robotPose):
    ax = robotPose.x + m.cos(sonarPose.theta) * sonarPose.x - m.sin(sonarPose.theta) * sonarPose.y
    ay = robotPose.y + m.sin(sonarPose.theta) * sonarPose.x + m.cos(sonarPose.theta) * sonarPose.y
    return util.Point(ax, ay)

#11.7
def wall((x1, y1), (x2, y2)):
    return util.LineSeg(util.Point(x1, y1), util.Point(x2, y2))

wallSegs = [wall((0, 2), (8, 2)),wall((1, 1.25), (1.5, 1.25)),wall((2, 1.75), (2.8, 1.75))]
robotPoses = [util.Pose(0.5, 0.5, 0),util.Pose(1.25, 0.5, 0),util.Pose(1.75, 1.0, 0),util.Pose(2.5, 1.0, 0)]

sonarMax = 1.5
numObservations = 10
sonarPose0 = util.Pose(0.08, 0.134, 1.570796)

def discreteSonars(sonarReading):
    if sonarReading > sonarMax:
        return numObservations - 1
    else:
        divide = sonarMax / (numObservations - 1)
        return int( sonarReading / divide )

def idealReadings(wallSegs, robotPoses):
    distance = []
    def onedistance(robotpose,wallseg):
        nowlocation_LineSeg = util.LineSeg(util.Point(robotpose.x, robotpose.y), util.Point(robotpose.x, robotpose.y + sonarMax))
        intersection = nowlocation_LineSeg.intersection(wallseg)
        return intersection
    for i in robotPoses:
        Noneflag = 0
        minrecord = []
        for j in wallSegs:
            temp = onedistance(i, j)
            if temp != False:
                Noneflag = 1
                minrecord.append(abs(temp.y - i.y))
        if Noneflag == 0:
            distance.append(None)
        else:
            distance.append(min(minrecord))
    return distance

##print idealReadings(wallSegs, robotPoses)



















