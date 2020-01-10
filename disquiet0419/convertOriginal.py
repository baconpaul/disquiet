import os
dir = "/Users/paul/Desktop/0419 Dischoir audio tracks"
for file in os.listdir( dir ):
    cmd = "sox \"{0}/{1}\" -b 16 -e signed-integer -r 48000 \"samples/{1}\"".format( dir, file );
    print( cmd );
    os.system(cmd);
