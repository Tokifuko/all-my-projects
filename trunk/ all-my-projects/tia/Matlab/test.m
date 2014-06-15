function test
hF=GetFigHandle();
for s = (pi*20): -0.2: 0.0
   AddValue(hF,sin(s));
   Repaint(hF);
end 