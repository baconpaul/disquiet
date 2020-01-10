import math
import numpy as np
import librosa
import os


def pitchAndStdDevForFile(fn):
    y, sr = librosa.load(fn, sr=48000)

    pitches, magnitudes = librosa.core.piptrack(y=y, sr=sr, fmin=75, fmax=2000)
    sh = np.shape(magnitudes)[1]

    af = 0
    fobs = 0

    for t in range(sh):
        index = magnitudes[:, t].argmax()
        if(magnitudes[index, t] > 5):
            af = af + pitches[index, t]
            fobs = fobs + 1

    if(fobs == 0):
        return (0, 0)
    avg = af / fobs

    var = 0
    for t in range(sh):
        index = magnitudes[:, t].argmax()
        if(magnitudes[index, t] > 5):
            p = pitches[index, t]
            var = var + (p - avg) * (p - avg)

    var = var / (fobs - 1)
    stddev = math.sqrt(var)

    return (avg, stddev)


for fn in os.listdir("samples/"):
    a, v = pitchAndStdDevForFile("samples/" + fn)
    print(fn, a, v)
