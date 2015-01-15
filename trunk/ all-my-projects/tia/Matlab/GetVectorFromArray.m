function y = GetVectorFromArray( x,deep )
% GetVector делает из одномерного массива - двумерный,
% дублируя данные со сдвигом
for index=1:deep
  y(index,:)=x(index:(length(x)-deep+index));  
end
end

