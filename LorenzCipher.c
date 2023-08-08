#include <stdio.h>


// wheel settings for the Lorenz cipher
char chi1[41] = {1,1,1,1,1,0,0,0,1,0,1,0,1,1,0,0,0,1,1,1,1,0,0,0,1,0,1,1,1,0,1,0,0,0,1,0,0,0,1,1,1};
char chi2[31] = {1,1,0,0,0,0,1,1,0,1,0,1,1,1,0,1,1,0,1,0,1,1,0,1,1,0,0,1,0,0,0};
char chi3[29] = {1,0,0,0,1,0,0,1,1,1,1,0,0,1,1,0,0,0,1,1,1,0,1,1,1,1,0,1,0};
char chi4[26] = {1,1,1,1,0,0,0,1,1,0,1,0,0,0,1,0,0,0,1,1,1,0,1,0,0,1};
char chi5[23] = {1,1,0,1,1,1,1,0,0,0,0,0,0,1,0,1,0,0,0,1,1,1,0};

char psi1[43] = {1,0,1,1,0,0,0,1,1,0,1,0,0,1,0,1,0,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,0};
char psi2[47] = {1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,0,1,0,1,0,1,0,1,0,1,1,0,0,0,1,0,1,0,1,0,1,0,1,1,1,0};
char psi3[51] = {1,0,1,0,0,0,0,1,0,0,1,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,0,1};
char psi4[53] = {0,1,0,1,0,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,1,0,0,1,1,0,1,1,0,1,0,1,0,0,1,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,0,1};
char psi5[59] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,0,1,0,0,1,1,0,1,0,1,0,0,1,0,0,1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,1,0};
char mu1[61] = {0,1,0,1,1,1,1,1,1,0,1,1,0,1,0,1,1,0,0,1,0,0,0,1,1,1,0,1,1,1,1,0,0,0,1,0,0,1,0,0,1,1,1,0,0,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,0};
char mu2[37] = {0,1,1,1,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,0,1,1,1,1,1,1,1,1,1};
    
    // wheel rotation (shift register operation)
void move_chi_pos(int chi_pos[5]){
    chi_pos[0] = (chi_pos[0] + 1) % 41;
    chi_pos[1] = (chi_pos[1] + 1) % 31;
    chi_pos[2] = (chi_pos[2] + 1) % 29;
    chi_pos[3] = (chi_pos[3] + 1) % 26;
    chi_pos[4] = (chi_pos[4] + 1) % 23;
    }
void move_psi_pos(int psi_pos[5]){
    psi_pos[0] = (psi_pos[0] + 1) % 43;
    psi_pos[1] = (psi_pos[1] + 1) % 47;
    psi_pos[2] = (psi_pos[2] + 1) % 51;
    psi_pos[3] = (psi_pos[3] + 1) % 53;
    psi_pos[4] = (psi_pos[4] + 1) % 59;
    }
    
void move_mu_pos1(int *mu_pos1){
    *mu_pos1 = (*mu_pos1 + 1) % 61;
    }
    
void move_mu_pos2(int *mu_pos2){
    *mu_pos2 = (*mu_pos2 + 1) % 37;
    }



// utility functions
void print_chi(int chi_pos[5]) {
    printf("%i ", chi1[chi_pos[0]]);
    printf("%i ", chi2[chi_pos[1]]);
    printf("%i ", chi3[chi_pos[2]]);
    printf("%i ", chi4[chi_pos[3]]);
    printf("%i ", chi5[chi_pos[4]]); printf("| "); }
    
void print_psi(int psi_pos[5]) {
    printf("%i ", psi1[psi_pos[0]]);
    printf("%i ", psi2[psi_pos[1]]);
    printf("%i ", psi3[psi_pos[2]]);
    printf("%i ", psi4[psi_pos[3]]);
    printf("%i ", psi5[psi_pos[4]]); printf("| "); }

void print_mu(int mu_pos[2]) {
    printf("%i ", mu1[mu_pos[0]]);
    printf("%i ", mu2[mu_pos[1]]);
    printf("| ");
    }

int main()
{   
    char K[5];
    char clock_mu_wheel;
    char clock_psi_wheel;
    
    // Starting positions of wheels
    int chi_pos[5] = {0,0,0,0,0};
    int psi_pos[5] = {0,0,0,0,0};
    int mu_pos[2] = {0,0};
    
    for(int t=0; t<10; t++) {
    // 1. Encrypting each 5-bit word at time t
    // K_t = chi_t^i \xor psi_{t_chi}^i
    K[0] = chi1[chi_pos[0]] ^ psi1[psi_pos[0]];
    K[1] = chi2[chi_pos[1]] ^ psi2[psi_pos[1]];
    K[2] = chi3[chi_pos[2]] ^ psi3[psi_pos[2]];
    K[3] = chi4[chi_pos[3]] ^ psi4[psi_pos[3]];
    K[4] = chi5[chi_pos[4]] ^ psi5[psi_pos[4]];
    print_chi(chi_pos);
    print_psi(psi_pos);
    print_mu(mu_pos);
    clock_mu_wheel = 0;
    clock_psi_wheel = 0;
    
    // 2. clock ticked as t = t+1
    // move all chi wheels
    move_chi_pos(chi_pos);
    // move first mu wheel
    move_mu_pos1(&mu_pos[0]);
    // 3. check for mu wheel rotation
    if(mu1[mu_pos[0]] == 1)
    clock_mu_wheel = 1;
    // move mu wheels
    if(clock_mu_wheel == 1) {
    move_mu_pos2(&mu_pos[1]);
    }
    
    // 4. check for psi wheel rotation
    if(mu2[mu_pos[1]] == 1)
    clock_psi_wheel = 1;
    // move psi wheels
    if(clock_psi_wheel == 1)
    move_psi_pos(psi_pos);
    // 5. output K_t
    for(int i=0; i<5; i++)
    printf("%i ",K[i]);
    printf("\n");
    }
    }