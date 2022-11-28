/*

Longest common subsequence:
Ls = ("AXYT", "AYZX")

Complessita bruteforce O(n*2^n) dove 2^n sono le sottostringhe 
e per ognuna di esse si itera sull'altra stringa di size n

Si risolve con un approccio di DP, dove la ricorsione è:

DP(i,j) = max{1+DP(i+1,j+1), DP(i,j+1), DP(i+1,j)}

*/ 


int main(){

}