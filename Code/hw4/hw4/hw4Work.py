import operator
import lib601.util as util

#-----------------------------------------------------------------------------

class DDist:
    """
    Discrete distribution represented as a dictionary.  Can be
    sparse, in the sense that elements that are not explicitly
    contained in the dictionary are assumed to have zero probability.
    """
    def __init__(self, dictionary):
        self.d = dictionary
        """ Dictionary whose keys are elements of the domain and values
        are their probabilities. """

    def dictCopy(self):
        """
        @returns: A copy of the dictionary for this distribution.
        """
        return self.d.copy()

    def prob(self, elt):
        """
        @param elt: an element of the domain of this distribution
        (does not need to be explicitly represented in the dictionary;
        in fact, for any element not in the dictionary, we return
        probability 0 without error.)
        @returns: the probability associated with C{elt}
        """
        if self.d.has_key(elt):
            return self.d[elt]
        else:
            return 0

    def support(self):
        """
        @returns: A list (in arbitrary order) of the elements of this
        distribution with non-zero probabability.
        """
        return [k for k in self.d.keys() if self.prob(k) > 0]

    def __repr__(self):
        if len(self.d.items()) == 0:
            return "Empty DDist"
        else:
            dictRepr = reduce(operator.add,
                              [util.prettyString(k)+": "+\
                               util.prettyString(p)+", " \
                               for (k, p) in self.d.items()])
            return "DDist(" + dictRepr[:-2] + ")"
    __str__ = __repr__

#-----------------------------------------------------------------------------

def incrDictEntry(d, k, v):
    """
    If dictionary C{d} has key C{k}, then increment C{d[k]} by C{v}.
    Else set C{d[k] = v}.
    
    @param d: dictionary
    @param k: legal dictionary key (doesn't have to be in C{d})
    @param v: numeric value
    """
    if d.has_key(k):
        d[k] += v
    else:
        d[k] = v


#-----------------------------------------------------------------------------

def squareDist(lo, hi, loLimit = None, hiLimit = None):
    dicts = {}
    if hi < loLimit:
        return DDist({loLimit:1.0})
    probality = 1.0/(hi - lo)
    temp_sum = probality
    for i in range(lo,hi):
        if i < loLimit:
            temp_sum += probality
        else:
            dicts[i] = temp_sum
            temp_sum = probality
    return DDist(dicts)

def triangleDist(peak, halfWidth, loLimit = None, hiLimit = None):
    dicts = {}
    probality = 1.0 / halfWidth**2
    temp_sum = 0.0
    for i in range(peak - halfWidth + 1,peak + halfWidth):
        if i < loLimit:
            temp_sum += probality * (halfWidth - abs(i - peak))
        else:
            dicts[i] = temp_sum + probality * (halfWidth - abs(i - peak))
            temp_sum = 0.0
    return DDist(dicts)


class MixtureDist:
    def __init__(self, d1, d2, p):
        self.p = p
        self.d1 = d1
        self.d2 = d2
        
    def prob(self, elt):
        sum_p = 0.0
        if elt in self.d1.d.keys():
            sum_p += self.d1.d[elt] * self.p
        if elt in self.d2.d.keys():
            sum_p += self.d2.d[elt] *(1 - self.p)
        return sum_p

    def support(self):
        lists = []
        for i in self.d1.d.keys():
            if not i in lists:
                lists.append(i)
        for i in self.d2.d.keys():
            if not i in lists:
                lists.append(i)
        return lists

    def __str__(self):
        result = 'MixtureDist({'
        elts = self.support()
        for x in elts[:-1]:
            result += str(x) + ' : ' + str(self.prob(x)) + ', '
        result += str(elts[-1]) + ' : ' + str(self.prob(elts[-1])) + '})'
        return result
    
    __repr__ = __str__

#-----------------------------------------------------------------------------
# If you want to plot your distributions for debugging, put this file
# in a directory that contains lib601, and where that lib601 contains
# sig.pyc.  Uncomment all of the following.  Then you can plot a
# distribution with something like:
# plotIntDist(MixtureDist(squareDist(2, 6), squareDist(4, 8), 0.5), 10)

# import lib601.sig as sig

# class IntDistSignal(sig.Signal):
#     def __init__(self, d):
#         self.dist = d
#     def sample(self, n):
#         return self.dist.prob(n)
# def plotIntDist(d, n):
#     IntDistSignal(d).plot(end = n, yOrigin = 0)

