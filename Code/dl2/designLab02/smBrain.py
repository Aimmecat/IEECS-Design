import math
import lib601.util as util
import lib601.sm as sm
import lib601.gfx as gfx
from soar.io import io

class MySMClass(sm.SM):
    #������һ������SM��������ø�ֵ�ĳ�ʼ״̬ ���Ժ������û��Ӱ��
    startState = 'Go_Straight'
    def __init__(self):
        self.state = 'Go_Straight'  #�����ĳ�ʼ״̬
        self.Sonars_inp = []        #���ڴ���˸����ŵ��б� ���ڵ���

        self.fvel_speed = 0.30      #��׼���ٶ� ����ֻ������������ϵ��ڰٷֱ�ʵ�����Ӽ��ٶ�
        self.rvel_speed = 0.30      #��׼���ٶ� ����ֻ������������ϵ��ڰٷֱ�ʵ�����Ӽ��ٶ�
        self.fvel_percent = 1.00    #���ٶȰٷֱ�
        self.rvel_percent = 0.50    #���ٶȰٷֱ�

        self.now = 0.00             #�˿̳���ǽ����
        self.last = 0.00            #��һʱ�̳���ǽ����
        self.allow_error = 1e-4     #�������������

        #�����жϽ��������ת
        self.block_flag = False  #����5 4 �ж���ǰ���Ƿ����ϰ�
        #��������1 8 �ж�����ת
        self.left_flag = False   
        self.right_flag = False

        #��ǽת180
        self.left_turn_flag = False #��һʱ��1 8 �����ж��Ƿ���ǽ
        self.right_turn_flag = False
        
        self.left_turn_flag_last = False    #��һʱ��1 8 �����ж��Ƿ���ǽ
        self.right_turn_flag_last = False
        #һ���򵥵�˼· �����⵽��һʱ����ǽ������һʱ����ǽ�� ˵��������һ������ Ҳ��������Ҫ�������
        #����������������־�ǲ������ת����������
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
##    ��������Safe_Boundart()
##    �������:self,min_bound,max_bound
##    ����˵����max_bound ������������߽���Զ����
##              min_bound ������������߽��������
##    ����ֵ��None
##    ���ܣ�ʹС������ǽ���������ά������Զ�������������
##    ˵�����˺����зֶδ�����ǽ���� ��Ϊ�����ڳ��˶������м�¼��ֵ�����ǵ�ǰ����ǽ�Ĵ�ֱ���� ���Ե�ƫ���ʱ���ǿ���ֱ���ôֲڵı߽����� �������ĳ��������ת����ת С�ھͶ�Ӧ��ת����ת
##          ����ƫ�벻���ʱ�����Ǿ�Ҫ��취�ó���ǽ��ֱ ������һֱ��һ��s ��Ȼ�������S���ܷ��Ⱥ�С ��Straight_Way()�ﴦ��
##'''
    def Safe_Boundart(self,min_bound = 0.3,max_bound = 0.4):
        left_dis = self.Sonars_inp[0]                           #������ŵ�ǰ����
        right_dis = self.Sonars_inp[7]                          #�Ҳ����ŵ�ǰ����
        min_left_dis = min(self.Sonars_inp[0:4])                #�����������е���С����
        min_right_dis = min(self.Sonars_inp[4:8])               #���Ҳ�������е���С����
        if left_dis < right_dis:                                #���������С���Ҳ� �ж��Ҳ���ӽ�ǽ
            if min_left_dis < min_bound:                        #���������趨�ı߽�����ת ʵ�������ղ��Է������±߽�����ԽСԽ�� �������΢��һ�����
                self.state = 'Go_And_Turn_Right'
            elif min_left_dis > max_bound:
                self.state = 'Go_And_Turn_Left'
            else:
                self.Straight_Way()                             #ǰ������if ��elif ��Ҫ�����������趨���߲�ܶ��ʱ���� �����������ھ����Сʱ΢С����
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
##    ��������Straight_Way()
##    �������:��
##    ����˵��:��
##    ����ֵ��None
##    ���ܣ�����Safe_Boundart() ǰ������Χ���ʱ�������� ����������Сʱ������
##    ˵����ԭ��ܼ� ���������趨������ƫ��ܴ��ʱ�� ����ֻ��Ҫ��������1 �� 8���� ��Ȼ ���Ǽ������ü򵥵ļ̳з�����¼��ǰʱ�̺���һʱ��ͬһ������ֵȻ������ ��������ĳ����С����ֵ
##          ˵������Զ�� ��֮ ���ڿ���  
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
##    ��������Block_Turn()
##    �������:dis
##    ����˵��:dis:����4 5��ǰ����С�ж�ת�����
##    ����ֵ��None
##    ���ܣ���С���˶���ǽ�ǵ�ʱ��ͽ�ȥ�ú��� �жϾ���С��dis��ͽ�������ת
##    ˵����������4 5�ж�ǰ�����ϰ��������ж����Ҳ���������ֵ���� �����˵�������ܿ��� ���Ǿ�ת����һ��
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
##    ��������Adjust_Speed_Percent()
##    �������:min_bound��max_bound
##    ����˵��:max_bound����߽������루��ǽ�ߣ�
##             min_bound: ��߽���С���루��ǽ�ߣ�
##    ����ֵ��None
##    ���ܣ���Ϊ�����Ƕ�������˶�״̬��ֱ��ǰ�к��˵ȵȣ� �����Ǹ���С���˶�������˵ǽ�ǡ������������״̬�� ����Ϊǰ���Ǹ��������Ե� ��Ϊ����ֻ��Ҫ���ǲ�ͬ��������ƴ�ӻ���״̬
##          �����������ÿһ��״̬�Ҿ��ÿ��ܡ��������Ժ�����Ҫ����һ���������� ����ǰ������˶�״̬ƴ�ӵ�
##          ��Ϊ�ǻ��ڻ���״̬ƴ�ӵ� ���Գ��ڲ�ͬ״̬��ʱ�����ǾͲ���ǰ�����״̬�ﶨ����趨�ٶȺͽ��ٶ� ���ı�һ�����ϵİٷֱ� ��������������Ǿ��ڲ�ͬ����״̬��ı�����ٷֱ�
##          ��Ϊ�������ֻ��returnһ��
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
##    ��������Empty_Turn()
##    �������:��
##    ����˵��:
##    ����ֵ��None
##    ���ܣ��ж�ת180��
##    ˵��������������1 8 ��¼С�����Ҳ��Ƿ���ǽ���趨һ����ֵ(���ھ��Ǻ����е�0.7 ����Ӧ�������ú�����ʱ���һ���α��� �������)Ȼ��������¼ ����˵ת��ǵ�ʱ��
##          С���Ҳ������һ����һ���Ӽ�⵽һ��С���뵽һ������������ ����ֻ��Ҫ������¼��ǰʱ�̲����µ���ȥʱ�� һֱ�ж� ���ĳһʱ����һ�����ż�⵽��Ч����(�����Ҳ���ǽ)����һʱ��
##          ����ǽ�� ��˵��������һ������ Ҳ����˵���Ǽ�¼����������ʱ���Ҫ�������ת����
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
##    ��������Collect_Sonars()
##    �������:inp
##    ����˵��:inp:���ű���
##    ����ֵ��None
##    ���ܣ��ռ�����ֵ��һ���б��б���
##'''      
    def Collect_Sonars(self,inp):
        self.Sonars_inp = [inp.sonars[0],inp.sonars[1],inp.sonars[2],inp.sonars[3],inp.sonars[4],inp.sonars[5],inp.sonars[6],inp.sonars[7]]
##'''
##    ��������Set_State()
##    �������:inp
##    ����˵��:inp:���ű���
##    ����ֵ��None
##    ���ܣ��жϲ�����״̬
##    ˵������û�з�װ�� ���������Set_State()ֻӦ�ø��������ж�ִ�ж�Ӧ����µĺ�������  ����ת180�ȵķ�������ͦ�ڵ� ��̫�� ���������� ��������дһ��
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
##    ��������getNextValues()
##    �������:state inp
##    ����˵��:inp:���ű��� state С��״̬
##    ����ֵ��None
##    ���ܣ����ݸ���һ��ִ��
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
