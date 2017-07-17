load FinalEvolution.txt;
GiveE  = FinalEvolution(:,1);
AcceptE = FinalEvolution(:,2);
WealthE = FinalEvolution(:,3);

% Set colour map
colormap(jet);
% Make 3D plot with filled circles coloured in the scheme of the 
% measurements
scatter3(GiveE, AcceptE, WealthE, 40, WealthE, 'filled');
title('Evolution Model with Declining(50/50)');
xlabel('Give');
ylabel('Min Accept')
% Set the azimuth and latitude to look directly above
view(0,90);
colorbar; % Throw in the colour bar.