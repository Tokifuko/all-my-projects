% ����������     0 � ������ ������
%                1- ����������� ����� ����
function res= SaveVectorStorage(path, filename  )
%��������� ������������ ����
if (exist(path,'dir')~=7) 
    res=1;
    return;
end;

if (strcmp(filename,'')) 
    filename='noname.mat'; 
end;

global VectorArray;
old_dir=cd(path);
save(filename,'VectorArray');
cd(old_dir);
res=0;
end

