import lib601.search as search
import lib601.sm as sm

# Indices into the state tuple.
(farmer, goat, wolf, cabbage) = range(4)
initstate  = ('L','L','L','L')
goalstate = ('R','R','R''R')


class FarmerGoatWolfCabbage(sm.SM):
   startState = initstate
   legalInputs = ('takeNone','takeGoat','takeWolf','takeCabbage')
   illegalstate = [('R','L','L','L'),('R','L','L','R'),('L','R','R','R'),('L','R','R','L') ,('R','L','R','L'),('L','R','L','R') ]

   def islegalInputs(self,action):
      if action in self.legalInputs:
         return True
      return False
   
   def issuitablestate(self,state):
      if state in self.illegalstate:
         return False
      return True
   
   def crossriver(self,location):
      if location == 'L':
         return 'R'
      return 'L'
   
   def getNextValues(self, state, action):
      if self.islegalInputs(action):
         if action == 'takeNone':
            newstate = (self.crossriver(state[0]),state[1],state[2],state[3])
         elif action == 'takeGoat':
            newstate = (self.crossriver(state[0]),self.crossriver(state[1]),state[2],state[3])
         elif action == 'takeWolf':
            newstate = (self.crossriver(state[0]),state[1],self.crossriver(state[2]),state[3])
         elif action == 'takeCabbage':
            newstate = (self.crossriver(state[0]),state[1],state[2],self.crossriver(state[3]))
         if self.issuitablestate(newstate):
            return (newstate,newstate)
         else:
            return (state,state)
      else:
         return (state,state)
      
   def done(self, state):
      if cmp(state,goalstate) == 0:
         return True
      return False

sm = FarmerGoatWolfCabbage()
print "The initstate is ('L','L','L','L')"
print "The action is ['takeGoat'],the next state is"
print sm.transduce(['takeGoat'])
print "The action is ['takeNone','takeGoat'],the next state is"
print sm.transduce(['takeNone','takeGoat'])
print "The action is ['takeGoat','takeNone','takeNone'],the next state is"
print sm.transduce(['takeGoat','takeNone','takeNone'])
