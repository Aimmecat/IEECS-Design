import lib601.dist as dist
import lib601.sm as sm
import lib601.ssm as ssm
import lib601.util as util

class StateEstimator(sm.SM):
    def __init__(self, model):
        self.model = model
        self.startState = model.startDistribution
        
    def bayesPobabilityGelper(self,state,observation):
        dicts = {}
        totalsum = 0.0
        for element in state.d.keys():
            dicts[element] = state.prob(element) * self.model.observationDistribution(element).prob(observation)
            totalsum += dicts[element]
        for element in state.d.keys():
            dicts[element] /= totalsum
        return dist.DDist(dicts)

    def totalPobabilityHelper(self,state,i):
        dicts = {}
        for element in state.d.keys():
            for states in state.d.keys():
                dist.incrDictEntry(dicts,states,state.prob(element)*self.model.transitionDistribution(i)(element).prob(states))    
        return dist.DDist(dicts)
    
    def getNextValues(self, state, inp):
        (o, i) = inp
##        sGo = dist.bayesEvidence(state, self.model.observationDistribution, o)
        sGo = self.bayesPobabilityGelper(state,o)
##        dSPrime = dist.totalProbability(sGo,self.model.transitionDistribution(i))
        dSPrime = self.totalPobabilityHelper(sGo,i)
        
        return (dSPrime, dSPrime)

# Test

transitionTable = \
   {'good': dist.DDist({'good' : 0.7, 'bad' : 0.3}),
    'bad' : dist.DDist({'good' : 0.1, 'bad' : 0.9})}
observationTable = \
   {'good': dist.DDist({'perfect' : 0.8, 'smudged' : 0.1, 'black' : 0.1}),
    'bad': dist.DDist({'perfect' : 0.1, 'smudged' : 0.7, 'black' : 0.2})}

copyMachine = \
 ssm.StochasticSM(dist.DDist({'good' : 0.9, 'bad' : 0.1}),
                # Input is irrelevant; same dist no matter what
                lambda i: lambda s: transitionTable[s],
                lambda s: observationTable[s])
obs = [('perfect', None), ('smudged', None), ('perfect', None)]

cmse = StateEstimator(copyMachine)

print cmse.transduce(obs, verbose = True)


