import distSkeleton as dist

#10.1.1
foo = dist.DDist({'hi':0.6,'med':0.3,'lo':0.1})

#10.1.2
def PTgD(diseaseValue):
    if diseaseValue == 'disease':
        return dist.DDist({'posTest':0.98,'negTest':0.02})
    elif diseaseValue == 'noDisease':
        return dist.DDist({'posTest':0.05,'negTest':0.95})
    else:
        pass

#10.1.6
def PTgD(diseaseValue):
    if diseaseValue == 'disease':
        return dist.DDist({'posTest':0.9,'negTest':0.1})
    elif diseaseValue == 'nodisease':
        return dist.DDist({'posTest':0.5,'negTest':0.5})
    else:
        pass
    
desease = dist.DDist({'disease':0.1,'nodisease':0.9})

def JDist(PA,PBgA):
    dists = {}
    for i in PA.support():
        for j in PBgA(i).support():
            dists.update({(str(i),str(j)):PA.prob(i) * PBgA(i).prob(j)})
    return dist.DDist(dists)


#10.1.7
