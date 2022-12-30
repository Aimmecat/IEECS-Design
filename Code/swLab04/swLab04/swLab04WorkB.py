import lib601.poly as poly
import swLab04SignalDefinitions
reload(swLab04SignalDefinitions) # so changes you make in swLab04SignalDefinitions.py will be reloaded
from swLab04SignalDefinitions import *

##4.1.2
test_Step = StepSignal()
##test.plot(-5,5)

##4.1.3
test_Sum = SummedSignal(StepSignal(),StepSignal())
test_Sca  = ScaledSignal(StepSignal(),-1)
##test_Sum.plot(-5,5)
##test_Sca.plot(-5,5)

#4.1.4
test_R = R(StepSignal())
test_Rn = Rn(StepSignal(),3)
##test_R.plot(-5,5)
##test_Rn.plot(-5,5)

#4.1.5
stepUpDownPoly = polyR(ScaledSignal(UnitSampleSignal(),1),poly.Polynomial([5,0,3,0,1,0]))
##stepUpDownPoly.plot(-10,10)

#This is TestFun#
testlist = [test_Step,test_Sum,test_Sca,test_R,test_Rn,stepUpDownPoly]
testlistname = ['test_Step','test_Sum','test_Sca','test_R','test_Rn','stepUpDownPoly']
for i in range(len(testlist)):
    testlist[i].plot(-10,10,newWindow = testlistname[i])
