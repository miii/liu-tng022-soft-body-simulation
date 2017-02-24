function [fp1, fp2] = calcMSDForce2DNeighbors(fi, i1, i2, p, v, ks, kd, r)
%[fp1, fp2] = calcMSDForce2D(j, p, v, ks, kd, r)
%   Calculate MSD forces for x and y components
%
%   fp1 is a 1x2 vector with x and y force for mass 1
%   fp2 is a 1x2 vector with x and y force for mass 2
%   
%   fi = Frame index, should be last frame if no force has affected the mass in the current frame
%   j = Mass index
%   p = Mass positions
%   v = Mass velocities
%   ks = Spring constant
%   kd = Damper constant
%   r = Rest length of spring
    
    % Find position for mass 1 and mass 2
    p1 = p(fi, i1, :);
    p2 = p(fi, i2, :);
    
    % Find velocity for mass 1 and mass 2
    v1 = v(fi, i1, :);
    v2 = v(fi, i2, :);
    
    % Find angle between p1 and p2
    dy = p2(2) - p1(2);
    dx = p2(1) - p1(1);
    angle = atan(dy / dx);
    
    % Get euclidean distance and velocity of masses
    euclDist = sqrt((p1(1) - p2(1))^2 + (p1(2) - p2(2))^2);
    euclVel = sqrt((v1(1) - v2(1))^2 + (v1(2) - v2(2))^2);
    
    % Spring force
    fspring = ks * (euclDist - r);
    
    % Damper force will be in the opposite direction of spring force
    fdamper = kd * euclVel;
    
    % Find direction of damper force
    dir = (v2 - v1) ./ abs(v2 - v1);
    % If division by zero above
    dir(isnan(dir)) = 0;
    
    % For proper angles since atan will not take direction into consideration
    if dx < 0
       angle = angle + pi; 
    end
    
    % Calculate force for both components (x and y)
    fp1(1) = fspring * cos(angle) + fdamper * dir(1);
    fp1(2) = fspring * sin(angle) + fdamper * dir(2);
    
    % Mass 2 will have opposite force
    fp2 = -fp1;

end

