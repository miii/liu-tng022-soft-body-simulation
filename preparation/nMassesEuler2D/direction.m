function dir = direction( x, i, n )
% The function returns the direction between two adjacent values in vector
% x
% Vector x consists of i samples with n values per sample

dir = zeros(1,n-1);
for k = 1:n-1
    absx = abs(x(i,k)-x(i,k+1));
    dir(k) = (x(i,k)-x(i,k+1))/absx;
end
end

