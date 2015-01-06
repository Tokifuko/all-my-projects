function y = DelElementFromArray_no_shift( x,delete_count )
%   удал€ет из массива указанное количество элементов не измен€€ значение
%   остальных элементов
len_old=length(x);
%%x=cell2mat(x);
a=len_old/delete_count;  
indx=a:a:len_old;
indx=floor(indx);
%x(indx-1)=(x(indx-1)+x(indx))/2;
x(indx)=[];
y=x;
end
