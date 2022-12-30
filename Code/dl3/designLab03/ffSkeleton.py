
#coding = utf-8
import lib601.sm as sm
import lib601.util as util
'''
¹ş¹ş¹ş¿ÉÒÔ×¢ÊÍÀ­
'''
class FollowFigure(sm.SM):
    startState = 0
    def __init__(self, way_list = []):
        self.way_list = way_list
    def getNextValues(self,state,inp):
        now_point = inp.odometry.point()
        if self.way_list[state].isNear(now_point,0.05):
            state += 1
            if state > len(self.way_list) - 1:
                state = 0
        return state,self.way_list[state]
