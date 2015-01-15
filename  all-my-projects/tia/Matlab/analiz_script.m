load('data_120115_3.mat','ForceArray','PressArray','LengthArray','ValveInPowerArray','ValveOutPowerArray','ValveInCountArray','ValveOutCountArray');

%% Кое-какая нормализация
LengthArray=LengthArray+3000;
PressArray=PressArray-100000;
ForceArray=ForceArray-1500000;

ValveInPowerArray=ValveInPowerArray.*50;
ValveOutPowerArray=ValveOutPowerArray.*50;
ForceArray=ForceArray.*0.002;
PressArray=PressArray.*0.01;

%% сдвигаем, чтобы компенсировать отставание даных штангенциркуля
% shift_len=-1;
% if (shift_len>0)
%     ForceArray(1:shift_len)=[];
%     PressArray(1:shift_len)=[];
%     ValveInPowerArray(1:shift_len)=[];
%     ValveOutPowerArray(1:shift_len)=[];
%     LengthArray((end-shift_len+1):end)=[];
% end
% if (shift_len<0)
%     shift_len=shift_len*(-1);
%     ForceArray((end-shift_len+1):end)=[];
%     PressArray((end-shift_len+1):end)=[];
%     ValveInPowerArray((end-shift_len+1):end)=[];
%     ValveOutPowerArray((end-shift_len+1):end)=[];
%     LengthArray(1:shift_len)=[];
% end

%% получаем фильтрованные данные
[f1,f2,f3]=GetAdaptArray(ForceArray,4);
[p1,p2,p3]=GetAdaptArray(PressArray,2);
% [l1,l2,l3]=GetAdaptArray(LengthArray,2);
l1=LengthArray;
v1=ValveInPowerArray;
v2=ValveOutPowerArray;

shift_len=12; % чтоб длинна соответствовала фильтрованным данным
l1((end-shift_len+1):end)=[];
v1((end-shift_len+1):end)=[];
v2((end-shift_len+1):end)=[];

%%  Апроксимируем длину
order=7;
% f4=GetVectorFromArray(f2,3);
% p4=GetVectorFromArray(p2,3);
% Xin= [f4' p4'];
Xin= [f2; p2];
Xin=Xin';
Z=l1';
% Z((end-2+1):end)=[];
poly = polyfitn(Xin,Z,order);
l2 = polyvaln(poly,Xin);

%% пробуем нейросети
% X=force(5,:);
% Y=press(5,:);
% Z=len(5,:);
% 
% X=double(X);
% Y=double(Y);
% Z=double(Z);
% 
% x_t=X(2000:10000);
% y_t=Y(2000:10000);
% z_t=Z(2000:10000);
% nero_input=[[x_t]; [y_t]];
% nero_output=z_t;
% 
% net.trainParam.epochs
% 
% 
% a=fitnet(5);
% a=train(a,nero_input,nero_output);
% % a=newlind(nero_input,nero_output);
% view (a);
% 
% x_t=X(1150:1300);
% y_t=Y(1150:1300);
% nero_input=[[x_t]; [y_t]];
% Z_calc=sim(a,nero_input);
% Error=(Z(1150:1300)-Z_calc).^2;

%% Строим графики
st=6400;
en=6500;
hold on
axis auto
xlim([st,en])

plot(l1,'r');
plot(l2,'b');
plot(v1,'b');
plot(v2,'r');
plot (p2,'m');
plot (f2,'k');
