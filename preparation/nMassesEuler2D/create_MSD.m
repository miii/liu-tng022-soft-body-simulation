function [ x, v ] = create_MSD( x, v, samples, n, m, k, d, r, h )
% The function creates the values of vectors x and v using Euler approximation
% The function uses two other functions: abs_val and direction
% 
% Parameter explanation:
% x = displacement
% v = velocity
% samples = number of samples
% n = number of masses
% m = mass
% k = spring constants
% d = damper constant
% r = rest length of the spring
% h = step length for Euler approximation


% n has to be greater than 2
if n<3
    disp('n has to be greater than 2')
    return
else

    % f is a vector containing the forces of the masses
    f = zeros(1,n);

    for i=1:samples
        % abs_v is a vector containing the absolute value of two adjacent
        % values in vector x
        abs_v = abs_val(x, i, n);
        % dir is a vector containing the direction between two adjacent
        % values in vector x
        dir = direction(x, i, n);

        % Calculate the force for each mass
        
        f(1) = -1 * calcMSDForce(1, k, d, i, v, r, abs_v, dir);
        % f(1) = -(k*(abs_v(1)-r)*dir(1) + d*(v(i,1)-v(i,2)));
        for z=2:n-1
            f(z) = calcMSDForce(z-1, k, d, i, v, r, abs_v, dir) - calcMSDForce(z, k, d, i, v, r, abs_v, dir);
            %f(z) = k*(abs_v(z-1)-r)*dir(z-1) + d*(v(i,z-1)-v(i,z)) -(k*(abs_v(z)-r)*dir(z) + d*(v(i,z)-v(i,z+1)));
        end
        %f(n) = k*(abs_v(n-1)-r)*dir(n-1) + d*(v(i,n-1)-v(i,n));
        f(n) = calcMSDForce(n-1, k, d, i, v, r, abs_v, dir);

        % Euler approximation
        %v(i,1:n) = motion(v(i,1:n), x(i,1:n), r);
        v(i+1,1:n) = v(i,1:n) + h*f(1:n)/m;
        x(i+1,1:n) = x(i,1:n) + h*v(i+1,1:n);

    end
end

end

