load('data_120115_3.mat','ForceArray','PressArray','LengthArray');

p1=ForceArray;

p2=my_mean(ForceArray,2);

FilterObj=my_filter;
p3=filter (FilterObj, ForceArray);
shift_len=12;
p3(1:shift_len)=[];

st=5450;
en=5550;
hold on
axis auto
xlim([st,en])

plot(p1,'r');
plot(p2);
plot(p3,'k');
