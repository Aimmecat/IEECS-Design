import math
import lib601.util as util
import lib601.sm as sm
import lib601.gfx as gfx
from soar.io import io

class MySMClass(sm.SM):
    #定义了一个父类SM里好像必须得赋值的初始状态 但对后面程序没有影响
    startState = 'Go_Straight'
    def __init__(self):
        self.state = 'Go_Straight'  #真正的初始状态
        self.Sonars_inp = []        #用于储存八个声呐的列表 便于调用

        self.fvel_speed = 0.30      #基准初速度 后面只是在这个基础上调节百分比实现增加减速度
        self.rvel_speed = 0.30      #基准角速度 后面只是在这个基础上调节百分比实现增加减速度
        self.fvel_percent = 1.00    #初速度百分比
        self.rvel_percent = 0.50    #角速度百分比

        self.now = 0.00             #此刻车离墙距离
        self.last = 0.00            #上一时刻车离墙距离
        self.allow_error = 1e-4     #最大允许调节误差

        #用于判断角落的左右转
        self.block_flag = False  #声呐5 4 判断最前方是否有障碍
        #根据声呐1 8 判断左右转
        self.left_flag = False   
        self.right_flag = False

        #绕墙转180
        self.left_turn_flag = False #这一时刻1 8 声呐判断是否有墙
        self.right_turn_flag = False
        
        self.left_turn_flag_last = False    #上一时刻1 8 声呐判断是否有墙
        self.right_turn_flag_last = False
        #一个简单的思路 如果检测到上一时刻有墙但是这一时刻有墙了 说明产生了一次跳变 也就是我们要走外角了
        #于是用下面两个标志是不是真的转完这个外角了
        self.left_turn_flag_ing = False
        self.right_turn_flag_ing = False

    def Go_And_Turn_Left(self):
        self.fvel_speed = 0.50
        self.rvel_speed = 0.30
    def Go_And_Turn_Right(self):
        self.fvel_speed = 0.50
        self.rvel_speed = -0.30
    def Go_Straight(self):
        self.fvel_speed = 0.50
        self.rvel_speed = 0.00
    def Turn_Left(self):
        self.fvel_speed = 0.00
        self.rvel_speed = 1.00
    def Turn_Right(self):
        self.fvel_speed = 0.00
        self.rvel_speed = -1.00
    def Stop(self):
        self.fvel_speed = 0.00
        self.rvel_speed = 0.00
    def RT_Left(self):
        self.fvel_speed = 0.10
        self.rvel_speed = 1.00
    def RT_Right(self):
        self.fvel_speed = 0.10
        self.rvel_speed = -1.00
##'''
##    函数名：Safe_Boundart()
##    输入参数:self,min_bound,max_bound
##    参数说明：max_bound ————车离边界最远距离
##              min_bound ————车离边界最近距离
##    返回值：None
##    功能：使小车在贴墙的情况下能维持在最远距离和最近距离间
##    说明：此函数中分段处理离墙距离 因为我们在车运动过程中记录的值很难是当前车和墙的垂直距离 所以当偏差大时我们可以直接用粗糙的边界条件 如果大于某个数就左转或右转 小于就对应右转或左转
##          但当偏离不多的时候我们就要想办法让车和墙垂直 而不是一直走一个s 虽然尽管这个S可能幅度很小 在Straight_Way()里处理
##'''
    def Safe_Boundart(self,min_bound = 0.3,max_bound = 0.4):
        left_dis = self.Sonars_inp[0]                           #左侧声呐当前距离
        right_dis = self.Sonars_inp[7]                          #右侧声呐当前距离
        min_left_dis = min(self.Sonars_inp[0:4])                #靠左侧的声呐中的最小距离
        min_right_dis = min(self.Sonars_inp[4:8])               #靠右侧的声呐中的最小距离
        if left_dis < right_dis:                                #如果左侧距离小于右侧 判断右侧更接近墙
            if min_left_dis < min_bound:                        #根据我们设定的边界左右转 实际上最终测试发现上下边界差设的越小越好 但最好稍微留一点点差距
                self.state = 'Go_And_Turn_Right'
            elif min_left_dis > max_bound:
                self.state = 'Go_And_Turn_Left'
            else:
                self.Straight_Way()                             #前面两个if 和elif 主要用于离我们设定的线差很多的时候走 这里是适用于距离较小时微小操作
        elif right_dis < left_dis:
            if min_right_dis < min_bound:
                self.state = 'Go_And_Turn_Left'
            elif min_right_dis > max_bound:
                self.state = 'Go_And_Turn_Right'
            else:
                self.Straight_Way()
        else:
            pass


##'''
##    函数名：Straight_Way()
##    输入参数:无
##    参数说明:无
##    返回值：None
##    功能：补充Safe_Boundart() 前者在误差范围大的时候起作用 后者在误差很小时起作用
##    说明：原理很简单 当离我们设定的中心偏差不很大的时候 我们只需要连续监视1 或 8声呐 显然 我们继续利用简单的继承方法记录当前时刻和上一时刻同一个声呐值然后做差 如果差大于某个很小的阈值
##          说明车在远离 反之 就在靠近  
##'''   
    def Straight_Way(self):
        now_left = self.Sonars_inp[0]
        now_right = self.Sonars_inp[7]
        if now_left < now_right:
            self.now = now_left
            error_k = self.last - self.now
        else:
            self.now = now_right
            error_k = self.now - self.last
        if error_k > self.allow_error:
            self.state = 'Go_And_Turn_Right'
        elif error_k < - self.allow_error:
            self.state = 'Go_And_Turn_Left'
        else:
            self.state = 'Go_Straight'
        self.last = self.now
##'''
##    函数名：Block_Turn()
##    输入参数:dis
##    参数说明:dis:声呐4 5离前方最小判断转弯距离
##    返回值：None
##    功能：当小车运动到墙角的时候就进去该函数 判断距离小于dis后就进行左右转
##    说明：当声呐4 5判断前面有障碍物后进入判断左右侧哪里声呐值更大 更大就说明更可能可走 我们就转向那一边
##'''     
    def Block_Turn(self,dis = 0.47):        
        if self.Sonars_inp[3] < dis and self.Sonars_inp[4] < dis:
            self.block_flag = True
        else:
            self.block_flag = False
        
        if self.block_flag:
            if self.Sonars_inp[0] < self.Sonars_inp[7]:
                self.right_flag  = True
            elif self.Sonars_inp[0] > self.Sonars_inp[7]:
                self.left_flag = True
            else:
                self.state = 'Turn_Left'
        if self.left_flag:
            if min(self.Sonars_inp[4:7]) < dis:
                self.state = 'Turn_Left'
            else:
                self.left_flag = False
                self.state = 'Go_Straight'
        if self.right_flag:
            if min(self.Sonars_inp[1:4]) < dis:
                self.state = 'Turn_Right'
            else:
                self.right_flag = False
                self.state = 'Go_Straight'
##'''
##    函数名：Adjust_Speed_Percent()
##    输入参数:min_bound，max_bound
##    参数说明:max_bound：离边界最大距离（沿墙走）
##             min_bound: 离边界最小距离（沿墙走）
##    返回值：None
##    功能：因为我们是定义基本运动状态（直行前行后退等等） 而不是根据小车运动到比如说墙角、外角这样定义状态的 我认为前者是更有普适性的 因为我们只需要考虑不同的情况如何拼接基本状态
##          如果单独定义每一个状态我觉得可能……可能以后我们要讨论一下这个问题吧 这次是按基本运动状态拼接的
##          因为是基于基本状态拼接的 所以出于不同状态的时候我们就不动前面基本状态里定义的设定速度和角速度 而改变一个乘上的百分比 在这个函数里我们就在不同基本状态里改变这个百分比
##          因为我们最后只能return一次
##'''     
    def Adjust_Speed_Percent(self,min_bound = 0.3,max_bound = 0.4):
        middle_bound = (min_bound + max_bound)/2
        min_dis = min(self.Sonars_inp[0:8])
        if self.state in ['Turn_Left' ,'Turn_Right']:
            self.rvel_percent = 1.00
        elif self.state in ['Go_And_Turn_Left','Go_And_Turn_Right']:
            self.rvel_percent =  5 * abs(min_dis - middle_bound) +0.05
            if  self.rvel_percent > 1:
                self.rvel_percent = 1
        else:
            self.rvel_percent = 0.50
##'''
##    函数名：Empty_Turn()
##    输入参数:无
##    参数说明:
##    返回值：None
##    功能：判断转180度
##    说明：我们用声呐1 8 记录小车左右侧是否有墙并设定一个阈值(现在就是函数中的0.7 我们应该在设置函数的时候加一个参变量 方便调参)然后连续记录 比如说转外角的时候
##          小车右侧的声呐一定有一个从检测到一个小距离到一个大距离的跳变 我们只需要连续记录当前时刻并更新到过去时刻 一直判断 如果某一时刻这一刻声呐检测到无效距离(比如右侧无墙)但上一时刻
##          是有墙的 那说明产生了一个跳变 也就是说我们记录到这个跳变的时候就要进行外角转弯了
##'''     
    def Empty_Turn(self):
            if self.Sonars_inp[7] < 0.7:
                self.right_turn_flag = False
            else:
                self.right_turn_flag = True

            if self.Sonars_inp[0] < 0.7:
                self.left_turn_flag = False
            else:
                self.left_turn_flag = True

            if self.right_turn_flag_last == False and self.right_turn_flag ==True:
                self.right_turn_flag_ing = True

            if self.left_turn_flag_last == False and self.left_turn_flag ==True:
                self.left_turn_flag_ing = True
  
            self.right_turn_flag_last = self.right_turn_flag
            self.left_turn_flag_last = self.left_turn_flag
            
##'''
##    函数名：Collect_Sonars()
##    输入参数:inp
##    参数说明:inp:声呐变量
##    返回值：None
##    功能：收集声呐值到一个列表中保存
##'''      
    def Collect_Sonars(self,inp):
        self.Sonars_inp = [inp.sonars[0],inp.sonars[1],inp.sonars[2],inp.sonars[3],inp.sonars[4],inp.sonars[5],inp.sonars[6],inp.sonars[7]]
##'''
##    函数名：Set_State()
##    输入参数:inp
##    参数说明:inp:声呐变量
##    返回值：None
##    功能：判断并设置状态
##    说明：还没有封装好 理想情况下Set_State()只应该根据条件判断执行对应情况下的函数即可  其中转180度的方法还是挺糙的 不太好 先这样放着 过两天重写一个
##''' 
    def Set_State(self,inp):
        self.Collect_Sonars(inp)
        self.Empty_Turn()
        if (self.Sonars_inp[0] < 1 or self.Sonars_inp[7] < 1) and (self.right_turn_flag_ing == False or self.left_turn_flag_ing == False):
            self.Safe_Boundart(0.32,0.33)
            self.Block_Turn(0.40)
        else:
            if self.right_turn_flag_ing:
                if self.Sonars_inp[5] > 0.7:
                    if min(self.Sonars_inp[6:8]) < 0.3:
                        self.state = 'Go_And_Turn_Left'
                    else:
                        self.state = 'RT_Right'
                else:
                    self.right_turn_flag_ing = False
            elif self.left_turn_flag_ing:
                if self.Sonars_inp[2] > 0.7:
                    if min(self.Sonars_inp[0:2]) < 0.3:
                        self.state = 'Go_And_Turn_Right'
                    else:
                        self.state = 'RT_Left'
                else:
                    self.left_turn_flag_ing = False
            else:
                self.state = 'Go_Straight'
        self.Adjust_Speed_Percent(0.32,0.33)
## '''
##    函数名：getNextValues()
##    输入参数:state inp
##    参数说明:inp:声呐变量 state 小车状态
##    返回值：None
##    功能：传递给下一次执行
##'''        
    def getNextValues(self, state, inp):
        if self.state == 'Go_And_Turn_Left':
            self.Go_And_Turn_Left()
        elif self.state == 'Go_And_Turn_Right':
            self.Go_And_Turn_Right()
        elif self.state == 'Go_Straight':
            self.Go_Straight()
        elif self.state == 'Turn_Left':
            self.Turn_Left()
        elif self.state == 'Turn_Right':
            self.Turn_Right()
        elif self.state == 'Stop':
            self.Stop()
        elif self.state == 'RT_Right':
            self.RT_Right()
        elif self.state == 'RT_Left':
            self.RT_Left()
        else:
            pass
        self.Set_State(inp)
##        print self.state
        print self.left_turn_flag_ing,self.right_turn_flag_ing
        return (self.state, io.Action(fvel = self.fvel_speed * self.fvel_percent, rvel = self.rvel_speed * self.rvel_percent))

mySM = MySMClass()
mySM.name = 'brainSM'

######################################################################
###
###          Brain methods
###
######################################################################

def plotSonar(sonarNum):
    robot.gfx.addDynamicPlotFunction(y=('sonar'+str(sonarNum),
                                        lambda: 
                                        io.SensorInput().sonars[sonarNum]))

# this function is called when the brain is (re)loaded
def setup():
    robot.gfx = gfx.RobotGraphics(drawSlimeTrail=True, # slime trails
                                  sonarMonitor=False) # sonar monitor widget
    
    # set robot's behavior
    robot.behavior = mySM

# this function is called when the start button is pushed
def brainStart():
    robot.behavior.start(traceTasks = robot.gfx.tasks())

# this function is called 10 times per second
def step():
    inp = io.SensorInput()
##    print inp.sonars[3]
    robot.behavior.step(inp).execute()
    io.done(robot.behavior.isDone())

# called when the stop button is pushed
def brainStop():
    pass

# called when brain or world is reloaded (before setup)
def shutdown():
    pass
