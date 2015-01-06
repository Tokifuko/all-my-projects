function y = DelElementFromArray_shift( x,delete_count )
%   удал€ет из массива указанное количество элементов измен€€ значение
%   только одного элемента, предшествующего удал€емому
len_old=length(x);
%%x=cell2mat(x);
a=len_old/delete_count;  
indx=a:a:len_old;
indx=floor(indx);
x(indx-1)=(x(indx-1)+x(indx))/2;
x(indx)=[];
y=x;
end