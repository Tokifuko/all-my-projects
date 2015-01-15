function [y1,y2,y3] = GetAdaptArray( x,mean_deep )
% фильтрует входящий сигнал, сдвигает фильтрованый влево чтобы
% компенсировать отставание, а также обрезает остальные справа, чтобы 
% была одинаковая размерность
%   x- входной сигнал
%   y1 - копия входного сигнала
%   y2 - усреднение по соседним элементам
%   y3 - фильтрованый через my_filter
y1=x;
y2=my_mean(x,mean_deep);
FilterObj=my_filter;
y3=filter (FilterObj, x);

shift_len=12;
y1((end-shift_len+1):end)=[];
y2((end-shift_len+1):end)=[];
y3(1:shift_len)=[];

end

