%% подготовка данных для обучения нейросети
f4=GetVectorFromArray(f1,40);
p4=GetVectorFromArray(p1,40);
v1_4=GetVectorFromArray(v1,40);
v2_4=GetVectorFromArray(v2,40);

Xin= [f4;p4];
Z=[v1_4(20,:); v2_4(20,:)];
 %% пробуем нейросеть
nero_input=Xin;
nero_output=Z;

% net.trainParam.epochs
a=fitnet(30);
a=train(a,nero_input,nero_output);
% a=newlind(nero_input,nero_output);
view (a);

%% подготавливаем данные для графиков
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


