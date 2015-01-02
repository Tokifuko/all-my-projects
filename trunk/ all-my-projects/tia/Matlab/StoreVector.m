function cur_size=StoreVector( Force,Press,Speed,Length,ValveInPower,ValveOutPower,ValveInCount,ValveOutCount)
global VectorArray;
global ForceArray;
global PressArray;
global SpeedArray;
global LengthArray;
global ValveInPowerArray;
global ValveOutPowerArray;
global ValveInCountArray;
global ValveOutCountArray;

Force=Force';
Press=Press';
Speed=Speed';
Length=Length';
ValveInPower=ValveInPower';
ValveOutPower=ValveOutPower';
ValveInCount=ValveInCount';
ValveOutCount=ValveOutCount';
ForceArray=Force;
PressArray= Press;
SpeedArray= Speed;
LengthArray= Length;
ValveInPowerArray= ValveInPower;
ValveOutPowerArray=ValveOutPower;
ValveInCountArray= ValveInCount;
ValveOutCountArray= ValveOutCount;
temp = size(LengthArray);
cur_size=temp(2);
end

