function abs_v = abs_val( x, i, n )
% the function returns the absoulute value between two adjacent values in
% vector x
% Vector x consists of i samples with n values per sample
abs_v = zeros(1,n-1);
min = 0.1;
max = 1;
for k = 1:n-1
    abs_v(k) = abs(x(i,k)-x(i,k+1));
end
end

