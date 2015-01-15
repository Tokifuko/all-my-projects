function res = my_mean( x ,deep)
% Функция для каждого элемента высчитывает среднее
%   среднее считается для самого элемента и +-deep элементов
y=x;
len=length(x);
for index=1:len
    st=(index-deep);
    en=(index+deep);
    if (st<1) st=1;end      %чтобы не выйти за границы массива
    if (en>len) en=len; end
    y(index)=mean(x(st:en));
end
res=y;
end

