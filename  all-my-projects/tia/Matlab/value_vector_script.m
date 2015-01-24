%пока считаем для впускного клапана
ind=valve_in>0;
nero_input=[press(ind,end) force(ind,end) len_calc(ind,end) speed_a(ind) speed_b(ind)];
% nero_input=[press(ind,:) force(ind,:) len_calc(ind,:) speed_a(ind) speed_b(ind) (speed_a(ind)-speed_b(ind))];
nero_output=valve_in(ind);

%% пробуем неуросеть
nero_input=nero_input';
nero_output=nero_output';


%  pool = parpool;

nero_input = con2seq(nero_input);
nero_output= con2seq(nero_output);

% Vin_neronet = narxnet(1:1,1:2,5);
[Xs,Xi,Ai,Ts] = preparets(Vin_neronet,nero_input,{},nero_output);

% Vin_neronet = train(Vin_neronet,Xs,Ts,Xi,Ai,'useGPU','yes','showResources','yes');

% Vin_neronet=fitnet(50);
% Vin_neronet=train(Vin_neronet,nero_input,nero_output,'useParallel','yes','useGPU','yes','showResources','yes');
% view (Vin_neronet);
[Xs,Xi,Ai,Ts] = preparets(Vin_neronet,nero_input,{},nero_output);
v_calc = Vin_neronet(Xs,Xi,Ai);
 v_calc=cell2mat(v_calc);

% v_calc=sim(Vin_neronet,nero_input);

%% Строим графики
st=200;
en=300;
hold on
axis auto
xlim([st,en])

plot(valve_in(ind),'r');
plot(v_calc,'b');


