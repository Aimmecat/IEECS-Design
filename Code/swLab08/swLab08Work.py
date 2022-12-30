import lib601.le as le
import lib601.circ as circ

ce = le.EquationSet()
ce.addEquation(le.Equation([1],['e3'],10))
ce.addEquation(le.Equation([1],['e0'],0))
ce.addEquation(le.Equation([1,-1,-100],['e3','e1','i2'],0))
ce.addEquation(le.Equation([1,-1,-100],['e3','e2','i3'],0))
ce.addEquation(le.Equation([1,-1,-100],['e1','e2','i6'],0))
ce.addEquation(le.Equation([1,-1,-10],['e1','e0','i4'],0))
ce.addEquation(le.Equation([1,-1,-100],['e2','e0','i5'],0))
ce.addEquation(le.Equation([1,1,1],['i1','i2','i3'],0))
ce.addEquation(le.Equation([1,-1,-1],['i5','i3','i6'],0))
ce.addEquation(le.Equation([1,-1,-1],['i2','i4','i6'],0))
print ce.solve()

ce1 = circ.Circuit([
    circ.VSrc(10,'e3','e0'),
    circ.Resistor(100,'e3','e1'),
    circ.Resistor(100,'e1','e2'),
    circ.Resistor(100,'e3','e2'),
    circ.Resistor(100,'e2','e0'),
    circ.Resistor(10,'e1','e0')
    ])
print ce1.solve('e0')
