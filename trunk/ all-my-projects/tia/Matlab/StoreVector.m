function cur_size=StoreVector( Force,Press,Speed,ValveInPower,ValveOutPower,ValveInCount,ValveOutCount)
global VectorArray;
Force=Force';
Press=Press';
Speed=Speed';
ValveInPower=ValveInPower';
ValveOutPower=ValveOutPower';
ValveInCount=ValveInCount';
ValveOutCount=ValveOutCount';
VectorArray=[[VectorArray] [ Force;Press;Speed;ValveInPower;ValveOutPower;ValveInCount;;ValveOutCount]];
temp = size(VectorArray);
cur_size=temp(2);
end

