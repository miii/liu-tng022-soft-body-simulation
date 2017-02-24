function [outpos, outvel] = createMSDVector2D(masses, velocity, mass, ks, kd, r, h, samples)
%[outpos, outvel] = createMSDVector2D(masses, velocity, mass, k, d, r, h, samples)
%   Simulates a 2D mass-spring-damper system using vectors.
%
%   outpos contains simulated positions of all masses
%   outvel contains simulated velocities of all masses
%
%   masses = 2D vector with masses start positions
%   velocity = 2D vector with masses start velocity
%   mass = Mass
%   ks = Spring constant
%   kd = Damper constant
%   r = Rest length of spring
%   h = Step size
%   samples = Number of samples

    % Kill if wrong input data
    if ~isequal(size(masses), size(velocity))
        error('Masses and velocity vector must have same dimension')
        return
    end
    
    % Store initial states in output vectors
    outpos(1, :, :) = masses;
    outvel(1, :, :) = velocity;
    
    % Get number of masses (m)
    [m n] = size(masses);
    
    for i = 2:samples
        
        for j = 1:(m-1)
           
            % Calculate MSD forces for x and y components
            % fp1 is a 1x2 vector with x and y force for mass 1
            % fp2 is a 1x2 vector with x and y force for mass 2
            [fp1 fp2] = calcMSDForce2D(j, outpos((i - 1), :, :), outvel((i - 1), :, :), ks, kd, r);
            
            % Get current velocity of both masses
            rsvel1 = reshape(outvel((i - 1), j, :), [1 2]);
            rsvel2 = reshape(outvel((i - 1), (j + 1), :), [1 2]);
            
            % Get current position of both masses
            rspos1 = reshape(outpos((i - 1), j, :), [1 2]);
            rspos2 = reshape(outpos((i - 1), (j + 1), :), [1 2]);
            
            % Check if the mass is already moved by another spring in the same frame
            % If yes, use the current velocity and position instead of last sample
            [n nn nnn] = size(outvel);
            if n == i
                cvel1 = reshape(outvel(i, j, :), [1 2]);
                cpos1 = reshape(outpos(i, j, :), [1 2]);
                
                rsvel1 = cvel1;
                rspos1 = cpos1;
            end
            
            % Euler for velocity
            vel1 = rsvel1 + h * fp1 / m;
            vel2 = rsvel2 + h * fp2 / m;
            
            % Euler for position
            pos1 = rspos1 + h * vel1;
            pos2 = rspos2 + h * vel2;
            
            % Store new calculated velocity
            outvel(i, j, :) = vel1;
            outvel(i, (j + 1), :) = vel2;
            
            % Store new calculated positon
            outpos(i, j, :) = pos1;
            outpos(i, (j + 1), :) = pos2;
            
        end
        
    end

end

