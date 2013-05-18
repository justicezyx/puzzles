#include <iostream>

/**
 * Fast integer square root based on math formula to compute square root.
 */
unsigned int isqrt3(unsigned int n)
{
   unsigned int root = 0, bit, trial;
   bit = (n >= 0x10000) ? 1<<30 : 1<<14;
   do
   {
      trial = root+bit;
      std::cout<<"trail: "<<trial<<std::endl;

      if (n >= trial)
      {
         n -= trial;
         root = trial+bit;
         std::cout<<"n: "<<n<<" root: "<<root<<std::endl;
      }
      root >>= 1;
      bit >>= 2;
      std::cout<<"root: "<<root<<" bit: "<<bit<<std::endl;
      
   } while (bit);
   return root;
}

int main() {
    std::cout<<isqrt3(10)<<std::endl;;
}
