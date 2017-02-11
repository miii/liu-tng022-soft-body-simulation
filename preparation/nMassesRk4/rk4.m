function [x, v] = rk4(i, m, h, x, v, N, k, d, r)
%
k1x(1:N)= v(i,1:N);
k1v(1:N)= acceleration(i, m, x, v, N, k, d, r);

k2x(1:N)= v(i+1,1:N) + 0.5*h*k1v(1:N);
k2v(1:N)= acceleration(i+1, m, x+0.5*h*k1x, v+0.5*h*k1v, N, k, d, r);

k3x(1:N)= v(i+2,1:N) + 0.5*h*k2v(1:N);
k3v(1:N)= acceleration(i+2, m, x+0.5*h*k2x, v+0.5*h*k2v, N, k, d, r);

k4x(1:N)= v(i+3,1:N) + h*k3v(1:N);
k4v(1:N)= acceleration(i+3, m, x+h*k3x, v+h*k3v, N, k, d, r);

v(i+1,1:N) = v(i,1:N) + (h/6)*(k1v+2*k2v+2*k3v+k4v);
x(i+1,1:N) = x(i,1:N) + (h/6)*(k1x+2*k2x+2*k3x+k4x);

end

