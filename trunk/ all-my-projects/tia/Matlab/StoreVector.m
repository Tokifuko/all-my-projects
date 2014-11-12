function cur_size=StoreVector( Force,Press,Speed)
global VectorArray;
VectorArray=[[VectorArray] [ Force;Press;Speed]];
temp = size(VectorArray);
cur_size=temp(2);
end

