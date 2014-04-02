function [ direct, scatterd ] = illumination(full, pattern1, pattern2)
%ILLUMINATION Summary of this function goes here
%   Detailed explanation goes here
    [x, y] =size(pattern1);
    direct = pattern1;
    scatterd = pattern2;
    for i=1:1:x
        for j=1:1:y
            l_plus = 0;
            l_minus = 0;
            if (pattern1(i, j) > pattern2(i,j))
                l_plus = pattern1(i,j);
                l_minus = pattern2(i,j);
            else
                l_plus = pattern2(i,j);
                l_minus = pattern1(i,j);
            end
            
            direct(i,j) = 2*l_minus;
            scatterd(i,j) = l_plus - l_minus;
            
        end
    end


end

