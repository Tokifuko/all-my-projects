function cur_size=StoreVector( Force,Press,Length,ValveInPower,ValveOutPower,ValveInCount,ValveOutCount)
global ForceArray;
global PressArray;
global LengthArray;
global ValveInPowerArray;
global ValveOutPowerArray;
global ValveInCountArray;
global ValveOutCountArray;

Force=Force';
Press=Press';
Length=Length';
ValveInPower=ValveInPower';
ValveOutPower=ValveOutPower';
ValveInCount=ValveInCount';
ValveOutCount=ValveOutCount';

ForceArray=[ForceArray,Force];
PressArray=[PressArray,Press];
LengthArray= [LengthArray, Length];
ValveInPowerArray=[ValveInPowerArray, ValveInPower];
ValveOutPowerArray=[ValveOutPowerArray, ValveOutPower];
ValveInCountArray= [ValveInCountArray, ValveInCount];
ValveOutCountArray= [ValveOutCountArray, ValveOutCount];
temp = size(LengthArray);
cur_size=temp(2);
end

