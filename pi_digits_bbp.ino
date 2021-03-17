#include <fp64lib.h>

int64_t n, k, ky, k1, k4, k5, k6, expon;
unsigned int fin;
float64_t sum1, sum2, sum3, sum4, pi_digits;

void setup() {

  Serial.begin(115200);
  n=0;
  delay(2000);

  Serial.print("3.");
}

/* Iterative Function to calculate (x^y) mod m  in O(log y) */
int64_t mod_power(int64_t x, int64_t y, int64_t m)
{
    int64_t res = 1;     // Initialize result
    if(m==1){return 0;}
  
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y%2==1){
            res = (res*x)%m;}
        y = y/2;
        x = (x*x)%m;  // Change x to x^2 mod m
    }
    return res;
}

float64_t sum_calc(int64_t expon, int64_t k, float64_t suum)
{
   float64_t summ;
   summ=fp64_add(suum,fp64_div(fp64_int64_to_float64(mod_power(16,expon,k)),fp64_int64_to_float64(k)));
   
   while (fp64_compare(summ , fp64_sd(1.0))==1){ //greater than
        summ = fp64_sub(summ , fp64_sd(1.0));}
   return summ;
}

//void printval(long digits){
//char buf[5];
//sprintf(buf, "%04X", digits>>16);
//Serial.print(buf);
//sprintf(buf, "%04X", digits);
//Serial.println(buf);
//    //Serial.println(digits, HEX);
//}

void loop() {

  sum1 = fp64_sd(0.0);
  sum2 = fp64_sd(0.0);
  sum3 = fp64_sd(0.0);
  sum4 = fp64_sd(0.0);
  
for (int64_t k=0; k<=n; k++){
    ky=k<<3;
    expon = n-k;

    sum1 = sum_calc(expon, ky+1, sum1);
    sum2 = sum_calc(expon, ky+4, sum2);
    sum3 = sum_calc(expon, ky+5, sum3);
    sum4 = sum_calc(expon, ky+6, sum4);

}
  
  pi_digits = fp64_sub(fp64_sub(fp64_sub((fp64_mul(sum1,fp64_sd(4.0))),(fp64_add(sum2,sum2))),sum3),sum4);

  while (fp64_compare(pi_digits , fp64_sd(1.0))==1){
      pi_digits = fp64_sub(pi_digits , fp64_sd(1.0));}
      
  while (fp64_compare(pi_digits , fp64_sd(0.0))==-1){ //less than
      pi_digits = fp64_add(pi_digits , fp64_sd(1.0));}


  fin = fp64_to_int16(fp64_mul(pi_digits , fp64_sd(65536.0)));
  if (n<20){
    fin = fin>>12;
    Serial.print(fin, HEX);
  }
  else if (n<192){
    fin = fin>>8;
    if (fin<16){Serial.print("0");}
    Serial.print(fin, HEX);
    n++;
  }
  else{ // if (n<1008){
    //fin = fp64_float64_to_long(fp64_mul(pi_digits , fp64_sd(65536.0)));
    if (fin<16){Serial.print("000");}
    else if (fin<256){Serial.print("00");}
    else if (fin<4096){Serial.print("0");}
    Serial.print(fin, HEX);
    n++;
    n++;
    n++;
  }
//    else {
//    fin = fp64_float64_to_long(fp64_mul(pi_digits , fp64_sd(1048576.0)));
//    if (fin<16){Serial.print("0000");}
//    else if (fin<256){Serial.print("000");}
//    else if (fin<4096){Serial.print("00");}
//    else if (fin<65536){Serial.print("0");}
//    Serial.print(fin, HEX);
//    n++;
//    n++;
//    n++;
//    n++;
//  }

//printval(fp64_float64_to_long(fp64_mul(pi_digits , fp64_sd(4294967296.0))));

 if((n>0) & ((n+1)%64==0)){Serial.println();}
 
 n++;
}
