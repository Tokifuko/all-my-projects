load('data_120115_3.mat','ForceArray','PressArray','LengthArray','ValveInPowerArray','ValveOutPowerArray','ValveInCountArray','ValveOutCountArray');
%% Кое-какая нормализация
LengthArray=LengthArray+3000;
PressArray=PressArray-100000;
ForceArray=ForceArray-1500000;

ValveInPowerArray=ValveInPowerArray.*50;
ValveOutPowerArray=ValveOutPowerArray.*50;
ForceArray=ForceArray.*0.002;
PressArray=PressArray.*0.01;
%% обрабатываем
f1=ForceArray;
p1=PressArray;
l1=LengthArray;
v1=ValveInPowerArray;
v2=ValveOutPowerArray;

f2=my_mean(ForceArray,2);
p2=my_mean(PressArray,2);
l2=my_mean(LengthArray,2);

%% получаем дополнительные данные
vin1=ValveInPowerArray;
vout1=ValveOutPowerArray;

bvin1=ValveInPowerArray>0;
bvout1 =ValveOutPowerArray>0;
s1=CalcSpeedFromLength(l1,2);
%% темп
d=2;
s2= zeros(1, d);
s2=[s2 s1(1:(end-d))];
Xin=[f1;p1;bvin1;bvout1;s2];
Z=[vin1;vout1] ;
%% подготовка данных для обучения нейросети
% hard=40;
% l4=GetVectorFromArray(l1,hard);
% f4=GetVectorFromArray(f1,hard);
% p4=GetVectorFromArray(p1,hard);
% s4=GetVectorFromArray(s1,hard);
% v1_4=GetVectorFromArray(v1,hard);
% v2_4=GetVectorFromArray(v2,hard);
% vpi2=GetVectorFromArray(bvin1,hard);
% vpo2=GetVectorFromArray(bvout1,hard);
% 
% Xin= [l4;f4;p4;s4;vpi2;vpo2];
% Z=[v1_4(hard,:); v2_4(hard,:)];

 %% пробуем нейросеть
nero_input=Xin;
nero_output=Z;
nero_input=con2seq(nero_input);
nero_output=con2seq(nero_output);
% net.trainParam.epochs
a=narxnet(1:2,1:2,10);
[Xs,Xi,Ai,Ts] = preparets(a,nero_input,{},nero_output);
pool = parpool;
a=train(a,Xs,Ts,Xi,Ai,'useParallel','yes','useGPU','yes','showResources','yes');
% a=newlind(nero_input,nero_output);
% view (a);

%% подготавливаем данные для графиков
nero_input=Xin;
Z_calc=sim(a,nero_input);

% v1_pl=v1;
% v2_pl=v2;
% v1_pl(1:10)=[];
% v2_pl(1:10)=[];

%% Строим графики

st=6400;
en=6500;
hold on
axis auto
xlim([st,en])

plot(Z_calc(1,:),'m');
plot(Z_calc(2,:),'k');
plot(Z(1,:),'r');
plot(Z(2,:),'b');


