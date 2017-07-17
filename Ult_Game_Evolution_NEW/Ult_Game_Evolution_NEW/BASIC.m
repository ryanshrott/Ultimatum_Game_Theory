load FinalBasic.txt;
GiveB  = FinalBasic(:,1);
AcceptB = FinalBasic(:,2);
WealthB = FinalBasic(:,3);

% Set colour map
colormap(jet);
% Make 3D plot with filled circles coloured in the scheme of the 
% measurements
scatter3(GiveB, AcceptB, WealthB, 40, WealthB, 'filled');
title('Basic Model w Declining (50/50)');
xlabel('Give');
ylabel('Min Accept')
% Set the azimuth and latitude to look directly above
view(0,90);
colorbar; % Throw in the colour bar.