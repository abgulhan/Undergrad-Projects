#include <iostream>
#include <math.h>
#include <ctime>
#include <chrono>

using namespace std;

int getLength(long long int value) { ///calculate binary length of a decimal number
    if(value == 0)
        return 0;
    if(value<0)
        value = -value; ///remove sign bit from value
    else{
        unsigned long long int bits, var = value;
        for(bits = 0; var != 0; ++bits)
            var >>= 1;
        return bits;
    }
}
int getMask(long long N){///generate a mask for getting lower n bits
    if(N==0){
        return 0;
    }
    long long int mask = 0b1;  ///generate a mask to get lower n bits of a number
    for (long long int i = 0; i<N-1; i++){
        mask = 1+ (mask<<1);
	}
	return mask;
}

long long karat_multiply(long long x, long long y) {
    long long int N = max(getLength(x),getLength(y));
	/// if the max length is one bit directly multiply it
	if (N<=1)
		return x * y;

	///divide max length in half and round up
	long long int Nhalf = ceil((float)N/2);

    long long int mask = getMask(Nhalf);///mask for getting lower Nhalf bits

	long long xL = x>>Nhalf; ///get upper N - Nhalf bits
	long long xR = x&mask; ///get lower Nhalf bits
	long long yL = y>>Nhalf; ///get upper N - Nhalf bits
	long long yR = y&mask; ///get lower Nhalf bits
	long long P1 = karat_multiply(xL,yL);
	long long P2 = karat_multiply(xR,yR);
	long long P3 = karat_multiply(xL+xR, yL+yR);


    return (P1<<(Nhalf<<1)) + ((P3-P1-P2)<<Nhalf) + P2;

}

long long classic_multiply(long long x, long long y) {
    long long int N = max(getLength(x),getLength(y));
	/// if the max length is one bit directly multiply it
	if (N<=1)
		return x * y;

	///divide max length in half and round up
	long long int Nhalf = ceil((float)N/2);

    long long int mask = getMask(Nhalf);///mask for getting lower Nhalf bits

	long long xL = x>>Nhalf; ///get upper N - Nhalf bits
	long long xR = x&mask; ///get lower Nhalf bits
	long long yL = y>>Nhalf; ///get upper N - Nhalf bits
	long long yR = y&mask; ///get lower Nhalf bits

    long long a = classic_multiply(xL,yL);
    long long b = classic_multiply(xL,yR);
    long long c = classic_multiply(xR,yL);
    long long d = classic_multiply(xR,yR);

    return (a<<(Nhalf<<1)) + ((b+c)<<Nhalf) + d;

}



int main() {

	long long a;
	long long b;
    double karat_time;
    double classic_time;
    long long karat_result;
    long long classic_result;

    cout << "input first operand: ";
    cin >> a;
    cout << "input second operand: ";
    cin >> b;



    auto begin1 = chrono::high_resolution_clock::now();
    auto end1 = chrono::high_resolution_clock::now();
    auto begin2 = chrono::high_resolution_clock::now();
    auto end2 = chrono::high_resolution_clock::now();
    uint32_t iterations = 1000;

    begin2 = chrono::high_resolution_clock::now();
    for(uint32_t i = 0; i < iterations; ++i)
    {
        classic_result = classic_multiply(a,b);
    }

    end2 = chrono::high_resolution_clock::now();

    begin1 = chrono::high_resolution_clock::now();
    for(uint32_t i = 0; i < iterations; ++i)
    {
        karat_result = karat_multiply(a,b);
    }
    end1 = chrono::high_resolution_clock::now();

    ///getting average time
    karat_time = chrono::duration_cast<chrono::nanoseconds>(end1-begin1).count()/iterations;
    classic_time = chrono::duration_cast<chrono::nanoseconds>(end2-begin2).count()/iterations;


    cout << endl;

	cout << "Karatsuba result = " <<karat_result << endl;
	cout << "Classic result = " <<classic_result << endl;

	cout << "Karatsuba time = " <<karat_time <<"ns" <<endl;
	cout << "Classic time = " <<classic_time << "ns"<< endl;

	return 0;
}
