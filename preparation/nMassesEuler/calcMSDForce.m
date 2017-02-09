function [force] = calcMSDForce(z, k, d, i, v, r, abs_v, dir)
%CALCULATEMSDFORCE Summary of this function goes here
%   Detailed explanation goes here
%   z = index of abs_val and dir vector
%   k = spring constant
%   d = damper constant
%   i = index
%   v = velocity
%   r = rest length of the spring
%   abs_v = vector containing the absolute value of two adjacent
%   dir = vector containing the direction between two adjacent
    
    spring = k*(abs_v(z)-r)*dir(1);
    damper = d*(v(i,1)-v(i,2));
    
    force = spring + damper;

end

