function AddValue( point)
global points;
points=[points point];
if (length(points))>50
     points(1)=[];
end
