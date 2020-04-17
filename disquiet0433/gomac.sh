#!/bin/sh

cmake . -GXcode -Bbuild || exit 2
xcodebuild build -configuration Release -project build/disquiet0433.xcodeproj -target run_dq

