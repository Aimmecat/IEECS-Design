import lib601.util as util
import lib601.dist as dist
import lib601.distPlot as distPlot
import lib601.sm as sm
import lib601.ssm as ssm
import lib601.sonarDist as sonarDist
import lib601.move as move
import lib601.seGraphics as seGraphics
import lib601.idealReadings as idealReadings

# For testing your preprocessor
class SensorInput:
    def __init__(self, sonars, odometry):
        self.sonars = sonars
        self.odometry = odometry

preProcessTestData = [SensorInput([0.8, 1.0], util.Pose(1.0, 0.5, 0.0)),
                       SensorInput([0.25, 1.2], util.Pose(2.4, 0.5, 0.0)),
                       SensorInput([0.16, 0.2], util.Pose(7.3, 0.5, 0.0))]
testIdealReadings = ( 5, 1, 1, 5, 1, 1, 1, 5, 1, 5 )
testIdealReadings100 = ( 50, 10, 10, 50, 10, 10, 10, 50, 10, 50 )


class PreProcess(sm.SM):
    
    def __init__(self, numObservations, stateWidth):
        self.startState = (None, None)
        self.numObservations = numObservations
        self.stateWidth = stateWidth

    def getNextValues(self, state, inp):
        (lastUpdatePose, lastUpdateSonar) = state
        currentPose = inp.odometry
        currentSonar = idealReadings.discreteSonar(inp.sonars[0],
                                                   self.numObservations)
        # Handle the first step
        if lastUpdatePose == None:
            return ((currentPose, currentSonar), None)
        else:
            action = discreteAction(lastUpdatePose, currentPose, self.stateWidth)
            print (lastUpdateSonar, action)
            return ((currentPose, currentSonar), (lastUpdateSonar, action))

# Only works when headed to the right
def discreteAction(oldPose, newPose, stateWidth):
    return int(round(oldPose.distance(newPose) / stateWidth))

def makeRobotNavModel(ideal, xMin, xMax, numStates, numObservations):
    
    startDistribution = dist.squareDist(xMin, xMax)

    def observationModel(ix):
        # ix is a discrete location of the robot
        # return a distribution over observations in that state
        DeltaDist = dist.DeltaDist(numObservations)
        TriangleDist = dist.triangleDist(ideal[min(ix, numStates - 1)], int(numObservations / 50) + 2)
        SquareDist = dist.squareDist(0, numObservations)
        return dist.MixtureDist(TriangleDist,dist.MixtureDist(DeltaDist, SquareDist, 0.5),0.85)
    
    def transitionModel(a):
        # a is a discrete action
        # returns a conditional probability distribution on the next state
        # given the previous state
        def transitionGivenI(oldState):
            newState = a + oldState
            TriangleDist_1 = dist.triangleDist(newState, int(numObservations / 50) + 1)
            TriangleDist_2 = dist.triangleDist(newState, int(numObservations / 50) + 2)
            return dist.MixtureDist(TriangleDist_1, TriangleDist_2, 0.7)
        return transitionGivenI  

    return ssm.StochasticSM(startDistribution, transitionModel, observationModel)

model = makeRobotNavModel(testIdealReadings, 0.0, 10.0, 10, 10)
##print model.observationDistribution(7)
##print model.transitionDistribution(2)(5)

##model100 = makeRobotNavModel(testIdealReadings100, 0.0, 10.0, 10, 100)

##distPlot.plot(model.observationDistribution(7))
##distPlot.plot(model100.observationDistribution(7))
##distPlot.plot(model.transitionDistribution(2)(5))

# Main procedure
def makeLineLocalizer(numObservations, numStates, ideal, xMin, xMax, robotY):
    Preprocessor_and_Estimator = sm.Cascade(PreProcess(numObservations, abs(xMax - xMin)/numStates), seGraphics.StateEstimator(makeRobotNavModel(ideal, xMin, xMax, numStates, numObservations)))
    Move = move.MoveToFixedPose(util.Pose(xMax, robotY, 0.0), maxVel = 0.5)
    Middle = sm.Parallel(Preprocessor_and_Estimator, Move)
    return sm.Cascade(Middle,sm.Select(1))



##PreProcessor = PreProcess(10, 1.0)
##Estimator = seGraphics.StateEstimator(makeRobotNavModel(testIdealReadings, 0.0, 10.0, 10, 10))
##ppEst = sm.Cascade(PreProcessor, Estimator)
##ppEst.transduce(preProcessTestData)


