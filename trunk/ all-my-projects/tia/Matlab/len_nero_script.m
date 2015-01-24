% получает нейросеть для вычисления длинны

load('data_240115_3.mat','ForceArray','PressArray','LengthArray');

mf=my_mean(ForceArray,0);
mp=my_mean(PressArray,0);
l=LengthArray;


%% пробуем нейросети
nero_input=[mf;mp];
nero_output=l;

len_neuro_net=fitnet(5);
% pool = parpool;
len_neuro_net=train(len_neuro_net,nero_input,nero_output);

l_calc=sim(len_neuro_net,nero_input);


%% Строим графики
st=6400;
en=6500;
hold on
axis auto
xlim([st,en])

plot(l,'r');
plot(l_calc,'m');
