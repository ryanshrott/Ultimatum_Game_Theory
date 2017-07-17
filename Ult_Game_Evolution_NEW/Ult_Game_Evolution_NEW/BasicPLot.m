clear; clf; 
fid = fopen('FinalBasic.txt', 'r');
Data = fscanf(fid, '%d', [3, inf]);
fclose(fid);

whos Data;