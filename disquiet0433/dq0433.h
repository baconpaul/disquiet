// -*-c++-*-
#include <sndfile.h>
#include <memory>
#include <vector>

const static int SAMPLERATE = 48000;
const static float SAMPLERATE_INV = 1.0f / SAMPLERATE;


/*
** Quite a lot of this code is borrowed from the flanger I wrote this week in surge
*/

struct InterpDelay {
    // OK so lets say we want lowest tunable frequency to be 23.5hz at 96k
    // 96000/23.5 = 4084
    // And lets future proof a bit and make it a power of 2 so we can use & properly
    static const int DELAY_SIZE=8192, DELAY_SIZE_MASK = DELAY_SIZE - 1;
    float line[DELAY_SIZE];
    int k = 0;
    InterpDelay() { reset(); }
    void reset() { memset( line, 0, DELAY_SIZE * sizeof( float ) ); k = 0; }
    float value( float delayBy ) {
        // so if delayBy is 19.2
        int itap = (int) delayBy; // this is 19
        float fractap = delayBy - itap; // this is .2
        int k0 = ( k + DELAY_SIZE - itap - 1 ) & DELAY_SIZE_MASK; // this is 20 back
        int k1 = ( k + DELAY_SIZE - itap     ) & DELAY_SIZE_MASK; // this is 19 back
        // std::cout << "KDATUM" << k << "," << delayBy << "," << itap << "," << k0 << "," << k1 << "," << fractap << std::endl;
        // so the result is
        float result = line[k0] * fractap + line[k1] * ( 1.0 - fractap ); // FIXME move to the one mul form
        // std::cout << "id::value " << _D(delayBy) << _D(itap) << _D(fractap) << _D(k) << _D(k0) << _D(k1) << _D(result) << _D(line[k0]) << _D(line[k1]) << std::endl;
        
        return result;
    }

    void push( float nv ) {
        k = ( k + 1 ) & DELAY_SIZE_MASK;
        line[k] = nv;
    }
};

bool writeWav( std::string fname, float *dat, size_t samp )
{
    SF_INFO sfinfo ;
    sfinfo.channels = 1;
    sfinfo.samplerate = SAMPLERATE;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    SNDFILE * outfile = sf_open(fname.c_str(), SFM_WRITE, &sfinfo);
    if( outfile == nullptr )
        return false;
    
    sf_count_t count = sf_write_float(outfile, dat, samp) ;
    sf_write_sync(outfile);
    sf_close(outfile);

    return( count == samp );
}

template< class T >
struct RunAndWrite
{
    std::shared_ptr<T> algo;
    std::string fn;
    
    RunAndWrite( std::shared_ptr<T> algo, std::string fn ) : algo( algo ), fn( fn ) { }

    void render() {
        // This is super inefficient way to collect but that's OK for now
        algo->restart();
        std::vector<float> vec;

        while( algo->hasNext() )
        {
            vec.push_back( algo->next() );
        }

        // Bit of a sketchy assumption here but...
        writeWav( fn, &(vec[0]), vec.size() );
    }
};
