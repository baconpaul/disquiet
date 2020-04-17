#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <cmath>

#include "dq0433.h"

void testSinOutput()
{
    auto b = std::make_unique<float[]>( 3 * SAMPLERATE );
    for( int i=0; i<3*SAMPLERATE; ++i )
    {
        b[i] = std::sin( 1.0 / SAMPLERATE * i * 2.0 * 3.141 * 440.0 );
    }
    writeWav( "sin.wav", b.get(), 3 * SAMPLERATE );
}

struct algo_Sin
{
    float t;
    void restart() { t=0; }
    bool hasNext() { return t < 3; }
    float next() {
        auto res = std::sin( t * 2.0 * 3.1415 * 440.0 );
        t += SAMPLERATE_INV;
        return res;
    }
};

struct algo_CombOnSweep
{
    InterpDelay id;
    float tap = SAMPLERATE / 440.0;
    float t;

    float restart() { t = 0; std::cout << "TAP=" << tap << std::endl; }
    bool hasNext() { return t < 3; }
    float next() {
        t += SAMPLERATE_INV;
        float v = std::sin( t * ( 220.0 * t ) * 2.0 * 3.14159 );
        id.push(v);

        float p = id.value(tap);
        
        return  0.5 * ( v + p );;
    }
};
    
struct algo_Chirp
{
    InterpDelay id;
    
    float t;
    float tap0 = SAMPLERATE / 440.0;
    float priorsample = 0;
    
    float restart() { t = 0; priorsample = 0; }
    bool hasNext() { return t < 3; }
    float next() {
        t += SAMPLERATE_INV;
        if( t < SAMPLERATE_INV * tap0 )
        {
            float v = 2.0 * rand() / RAND_MAX - 1.0;
            id.push(v);
            return v;
        }
        float tap = tap0 * ( 1 + sqrt( t ) );
        float p = id.value(tap);
        float o = ( 0.9 * p + 0.1 * priorsample ) * 0.997;
        priorsample = p;
        id.push(o);
        
        return o;
    }
};

int main( int argc, char **argv )
{
    std::cout << "\n\n\n+---------------------------------\n|  DQ0433 - feedback experiments \n+---------------------------------\n" << std::endl;

    auto r = RunAndWrite( std::make_shared<algo_CombOnSweep>(), "con.wav" );
    r.render();
}


