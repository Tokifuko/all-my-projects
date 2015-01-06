a={1, 5, 2, 12,10,1,11,12,8,2,10,12,13,11,12,12,11,12};

a=cell2mat(a);
a=double(a);
hold on;

add_namber=12;
len=length(a);
res=myresample(a,len+add_namber,'shift');
plot(res);
 
b =myresample(a,len+add_namber,'noshift');
plot(b,'g');
plot(a,'r');



