function PlotSpectr(hAxes,Fd,points);
if (strcmp(get(hAxes,'BeingDeleted'),'on' )) 
    return
end
%% ������������ ������������� �������
FftL=1024;% ���������� ����� ����� �������
FftS=abs(fft(points,FftL));% ��������� �������������� ����� �������
FftS=2*FftS./FftL;% ���������� ������� �� ���������
FftS(1)=FftS(1)/2;% ���������� ���������� ������������ � �������
F=0:Fd/FftL:Fd/2-Fd/FftL;% ������ ������ ������������ ������� �����
%% ���������� �������
plot(hAxes,F,FftS(1:length(F)));% ���������� ������� ����� �������
end

