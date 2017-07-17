clear; clf; 
basic = fopen('C:\Users\Ryan\Documents\Game Theory\Ult_Game_Evolution_NEW\Ult_Game_Evolution_NEW\FinalBasic.txt', 'r');
Data = fscanf(basic, '%d', [3, inf]);
fclose(basic);

whos Data;