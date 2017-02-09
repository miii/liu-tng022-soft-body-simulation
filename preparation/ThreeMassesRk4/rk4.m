function [position, velocity] = rk4(i,j, mass, h, force, velocity, position)
%RK4
k1 = (force/mass);
k2 = (force/mass) + 0.5*k1*h;
k3 = (force/mass) + 0.5*k2*h;
k4 = (force/mass) + h*k3;

velocity(i+1,j) = velocity(i,j) + (h/6)*(k1+2*k2+2*k3+k4);

kv1 = velocity(i,j);
kv2 = velocity(i,j) + 0.5*kv1*h;
kv3 = velocity(i,j) + 0.5*kv2*h;
kv4 = velocity(i,j) + h*kv3;

position(i+1,j) = position(i,j) + (h/6)*(kv1+2*kv2+2*kv3+kv4);

end