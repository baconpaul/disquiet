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

/*
** Take a noise signal and simply spike up and down the feedback
*/
struct algo_NoiseIntoDroppingFeedback
{
    float t;
    float restart() { t = 0; }
    bool hasNext() { return t < 3; }
    float next() {
    }
};

int main( int argc, char **argv )
{
    std::cout << "\n\n\n+---------------------------------\n|  DQ0433 - feedback experiments \n+---------------------------------\n" << std::endl;

    auto r = RunAndWrite( std::make_shared<algo_Sin>(), "sinrw.wav" );
    r.render();
}


