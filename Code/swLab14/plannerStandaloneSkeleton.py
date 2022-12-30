import math
import lib601.ucSearch as ucSearch
import lib601.util as util
import lib601.basicGridMap as basicGridMap
import lib601.gridMap as gridMap
import lib601.sm as sm



######################################################################
###         Picking worlds
######################################################################

mapTestWorld = ['mapTestWorld.py', 0.2, util.Point(2.0, 5.5),
                util.Pose(2.0, 0.5, 0.0)]
bigPlanWorld = ['bigPlanWorld.py', 0.25, util.Point(3.0, 1.0),
                util.Pose(1.0, 1.0, 0.0)]


class GridDynamics(sm.SM):
    
    legalInputs = [(1,0) , (-1,0) , (0,-1) , (0,1), (1,1) , (-1,-1) , (1,-1) , (-1,1)]
    
    def __init__(self, theMap):
        self.map = theMap

    def Judge_Moving_Diagonally(self,theMap, currentState, action):
        return (theMap.robotCanOccupy((currentState[0] + action[0] , currentState[1])) or theMap.robotCanOccupy((currentState[0] , currentState[1] + action[1]))) \
             and theMap.robotCanOccupy((currentState[0] + action[0] , currentState[1] + action[1]))

    def Judge_Moving_Straignt(self, theMap, currentState, action):
        return theMap.robotCanOccupy((currentState[0] + action[0], currentState[1] + action[1]))
    
    def getNextValues(self, state, inp):
        if inp in self.legalInputs:
            if inp[0] and inp[1]:
                if self.Judge_Moving_Diagonally(self.map, state, inp):
                    newState = (state[0] + inp[0], state[1] + inp[1])
                    cost = self.map.xStep * (2 ** 0.5)
                else:
                    newState = state
                    cost = 0
            else:
                if self.Judge_Moving_Straignt(self.map, state, inp):
                    newState = (state[0] + inp[0], state[1] + inp[1])
                    cost = self.map.xStep
                else:
                     newState = state
                     cost = 0
        else:
            newState = state
            cost = 0
        return (newState, cost)


#test 1 
class TestGridMap(gridMap.GridMap):
    def __init__(self, gridSquareSize):
        gridMap.GridMap.__init__(self, 0, gridSquareSize * 5,
                               0, gridSquareSize * 5, gridSquareSize, 100)

    def makeStartingGrid(self):
        grid = util.make2DArray(5, 5, False)
        for i in range(5):
            grid[i][0] = True
            grid[i][4] = True
        for j in range(5):
            grid[0][j] = True
            grid[4][j] = True
        grid[3][3] = True
        return grid

    def robotCanOccupy(self, (xIndex, yIndex)):
        return not self.grid[xIndex][yIndex]

#test 2
##class TestGridMap(gridMap.GridMap):
##    def __init__(self, gridSquareSize):
##        (self.xN, self.yN) = (5, 5)
##        self.xStep = gridSquareSize
##        self.yStep = gridSquareSize
##        self.xMin = self.yMin = 0.0
##        self.xMax = self.yMax = gridSquareSize * 5
##        self.grid = util.make2DArray(5, 5, False)
##        for i in range(5):
##            self.grid[i][0] = True
##            self.grid[i][4] = True
##        for j in range(5):
##            self.grid[0][j] = True
##            self.grid[4][j] = True
##        self.grid[3][3] = True
##    def robotCanOccupy(self, (xIndex, yIndex)):
##        return not self.grid[xIndex][yIndex]




def testGridDynamics():
    gm = TestGridMap(0.15)
    print 'For TestGridMap(0.15):'
    r = GridDynamics(gm)
    print 'legalInputs', util.prettyString(r.legalInputs)
    ans1 = [r.getNextValues((1,1), a) for a in r.legalInputs]
    print 'starting from (1,1)', util.prettyString(ans1)
    ans2 = [r.getNextValues((2,3), a) for a in r.legalInputs]
    print 'starting from (2,3)', util.prettyString(ans2)
    ans3 = [r.getNextValues((3, 2), a) for a in r.legalInputs]
    print 'starting from (3,2)', util.prettyString(ans3)
    gm2 = TestGridMap(0.4)
    print 'For TestGridMap(0.4):'
    r2 = GridDynamics(gm2)
    ans4 = [r2.getNextValues((2,3), a) for a in r2.legalInputs]
    print 'starting from (2,3)', util.prettyString(ans4)

##testGridDynamics()

def planner(initialPose, goalPoint, worldPath, gridSquareSize):
    gm = basicGridMap.BasicGridMap(worldPath, gridSquareSize)
    smToSearch = GridDynamics(gm)
    def g(s):
        gm.drawSquare(s, 'gray')
        return (gm.pointToIndices(goalPoint)[0] == s[0] and gm.pointToIndices(goalPoint)[1] == s[1])
    def heuristic(newS):
##        return 0
        return abs(newS[0] - gm.pointToIndices(goalPoint)[0]) + (newS[1] - gm.pointToIndices(goalPoint)[1])
    Way = ucSearch.smSearch(smToSearch, gm.pointToIndices(initialPose.point()), g, heuristic)
    Way_list = []
    for i in Way:
        Way_list.append(i[1])
    gm.drawPath(Way_list)


def testPlanner(world):
    (worldPath, gridSquareSize, goalPoint, initialPose) = world
    planner(initialPose, goalPoint, worldPath, gridSquareSize)

##testPlanner(mapTestWorld)
testPlanner(bigPlanWorld)    
