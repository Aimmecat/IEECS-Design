import lib601.poly as poly
import lib601.sig
from lib601.sig import *

## You can evaluate expressions that use any of the classes or
## functions from the sig module (Signals class, etc.).  You do not
## need to prefix them with "sig."

#4.1.1
step1 =Rn(ScaledSignal(StepSignal(),3),3)
step2 = Rn(ScaledSignal(StepSignal(),-3),7)
stepUpDown = step1 + step2
stepUpDownPoly = polyR(ScaledSignal(UnitSampleSignal(),1),poly.Polynomial([5,0,3,0,1,0]))

testSignal = [step1,step2,stepUpDown,stepUpDownPoly]
testName =  ['step1','step2','stepUpDown','stepUpDownPoly']
for i in range(len(testSignal)):
    testSignal[i].plot(-10,10,newWindow = testName[i])













































step1 = ScaledSignal(Rn(StepSignal(),3),3)
step1.plot(-5,5)


